#include "MAX7219_DotMatrix.h"
#include <SPI.h>

// constructor
MAX7219_DotMatrix::MAX7219_DotMatrix(uint8_t pin_clk, uint8_t pin_cs, uint8_t pin_din, uint8_t mr, uint8_t mc) :
    begun(false), draw_mode(true), fill_status(false), offset_x(0), offset_y(0), rotate_state(0)
{
    setPin(pin_clk, pin_cs, pin_din);
    setRowColumn(mr, mc);
}
MAX7219_DotMatrix::MAX7219_DotMatrix(uint8_t mr, uint8_t mc) :
    begun(false), draw_mode(true), fill_status(false), offset_x(0), offset_y(0), rotate_state(0)
{
    setPin(13, 10, 11);
    setRowColumn(mr, mc);
}
// destructor
MAX7219_DotMatrix::~MAX7219_DotMatrix(){
    if(matrix) free(matrix);
    SPI.end();
}


void MAX7219_DotMatrix::setPin(uint8_t p_clk, uint8_t p_cs, uint8_t p_din){
    pin_clk = p_clk;
    pin_cs = p_cs;
    pin_din = p_din;
}

void MAX7219_DotMatrix::setRowColumn(uint8_t r, uint8_t c){
    matrix_row = r;
    matrix_column = c;
    matrix_byte = 8 * matrix_row * matrix_column;
}

// initialize function
bool MAX7219_DotMatrix::begin(void) {

    // If allready initialized, return
    if(begun) return true;

    pinMode(pin_clk, OUTPUT);
    pinMode(pin_cs, OUTPUT);
    pinMode(pin_din, OUTPUT);

    // reserve memory
    matrix = (uint8_t *)calloc(matrix_byte, sizeof(uint8_t));
    if (matrix == NULL) return false;    // if it could not reserve memory

    // original : http://akizukidenshi.com/download/ds/sainsmar/max7219_SPI_20170916.zip
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(0);

    Write_MAX7219Int(0x09, 0x00);   // 00001001 00000000 -> decode mode
    Write_MAX7219Int(0x0a, 0x04);   // 00001010 00000100 -> brightness:5/16
    Write_MAX7219Int(0x0b, 0x07);   // 00001011 00000111 -> Scan Limit
    Write_MAX7219Int(0x0c, 0x01);   // 00001100 00000001 -> Shutdown
    Write_MAX7219Int(0x0f, 0x00);   // 00001111 00000000 -> Display test
    Write_MAX7219Int(0x00, 0x00);   // shift data
    Write_MAX7219Int(0x00, 0x00);   // shift data
    Write_MAX7219Int(0x00, 0x00);   // shift data
    delay(100);

    allOff();
    begun = true;
    return true;
}

// protected function
void MAX7219_DotMatrix::Write_MAX7219(uint8_t addr, uint8_t dat){
    SPI.transfer(addr);
    SPI.transfer(dat);
}
void MAX7219_DotMatrix::Write_MAX7219Int(uint8_t addr, uint8_t dat){
    digitalWrite(pin_cs, 0);
    SPI.transfer(addr);
    SPI.transfer(dat);
    digitalWrite(pin_cs, 1);
}
bool MAX7219_DotMatrix::setBit(int16_t x, int16_t y){

    return setBit(x, y, NULL);
}
bool MAX7219_DotMatrix::setBit(int16_t x, int16_t y, uint8_t *matrix_tmp){

    if(!isWithin(x,y)) return false;
    uint16_t index = convertCoordinateToMatrixIndex(x,y);
    uint8_t bits = convertCoordinateToMatrixBit(x);

    if(draw_mode){
        if(matrix_tmp){
            matrix_tmp[index] |= bits;
        }  else {
            matrix[index] |= bits;
        }
    } else {
        if(matrix_tmp){
            matrix_tmp[index] &= ~bits;
        }  else {
            matrix[index] &= ~bits;
        }
    }

    return true;
}
bool MAX7219_DotMatrix::clearBit(int16_t x, int16_t y){

    return clearBit(x, y, NULL);
}
bool MAX7219_DotMatrix::clearBit(int16_t x, int16_t y, uint8_t *matrix_tmp){

    if(!isWithin(x,y)) return false;
    uint16_t index = convertCoordinateToMatrixIndex(x,y);
    uint8_t bits = convertCoordinateToMatrixBit(x);

    if(draw_mode){
        if(matrix_tmp){
            matrix_tmp[index] &= ~bits;
        }  else {
            matrix[index] &= ~bits;
        }
    } else {
        if(matrix_tmp){
            matrix_tmp[index] |= bits;
        }  else {
            matrix[index] |= bits;
        }

    }

    return true;
}
uint16_t MAX7219_DotMatrix::convertCoordinateToMatrixIndex(uint16_t x, uint16_t y){
    uint16_t upside    = (uint16_t)floor(y/DM_DOT_COUNT);   // count how many rows are on top
    uint16_t leftside  = (uint16_t)floor(x/DM_DOT_COUNT);   // count how many columns are on the left side
    uint8_t  thisblock = y%(int)DM_DOT_COUNT;               // count how many lines are on top in this block
    return upside*DM_DOT_COUNT*matrix_column + leftside*DM_DOT_COUNT + thisblock;
}
uint8_t MAX7219_DotMatrix::convertCoordinateToMatrixBit(uint16_t x, uint16_t y){
    // Oops! we do not need y param! ꉂꉂ ( ˆᴗˆ  )
    return 0b10000000 >> (x%(int)DM_DOT_COUNT);
}
uint8_t MAX7219_DotMatrix::convertCoordinateToMatrixBit(uint16_t x){
    return 0b10000000 >> (x%(int)DM_DOT_COUNT);
}
bool MAX7219_DotMatrix::isWithin(int16_t x, int16_t y){
    return (0 <= x && x < matrix_column * DM_DOT_COUNT && 0<= y && y < matrix_row * DM_DOT_COUNT);
}
bool MAX7219_DotMatrix::closedAreaFill(int16_t center_x, int16_t center_y, uint8_t *matrix_tmp){

    int16_t stack_idx = 0;
    int16_t* stack = (int16_t *)calloc(matrix_byte*DM_DOT_COUNT*2, sizeof(int16_t));
    if (stack == NULL) return false;    // if it could not reserve memory

    // init push
    stack[stack_idx] = center_x;    // idx::0 or odd -> x point
    stack_idx++;
    stack[stack_idx] = center_y;    // idx::even -> y point
    stack_idx++;
    while(stack_idx > 0){
        // recursion
        stack_idx = closedAreaFillLoop(stack_idx, stack, matrix_tmp);
        Serial.print("idx:");
        Serial.println(stack_idx);
    }
    if(stack) free(stack);
    return true;
}

int16_t MAX7219_DotMatrix::closedAreaFillLoop(int16_t idx, int16_t *stack, uint8_t *matrix_tmp){

    idx--;
    int16_t y = stack[idx];
    idx--;
    int16_t x = stack[idx];

    if(!isWithin(x, y)) return idx;

    setBit(x,y);
    setBit(x,y,matrix_tmp);

    // Serial.print("x:");
    // Serial.print(x);
    // Serial.print(", y:");
    // Serial.print(y);
    // Serial.print(", dm:");
    // Serial.print(draw_mode);
    // Serial.print(", gP:");
    // Serial.print(getPoint(x-1, y, matrix_tmp));

    if( getPoint(x-1, y, matrix_tmp) != draw_mode ){
        stack[idx] = x-1;
        idx++;
        stack[idx] = y;
        idx++;
        setBit(x-1, y);
        setBit(x-1, y, matrix_tmp);
    }
    if( getPoint(x, y-1, matrix_tmp) != draw_mode ){
        stack[idx] = x;
        idx++;
        stack[idx] = y-1;
        idx++;
        setBit(x, y-1);
        setBit(x, y-1, matrix_tmp);
    }
    if( getPoint(x+1, y, matrix_tmp) != draw_mode ){
        stack[idx] = x+1;
        idx++;
        stack[idx] = y;
        idx++;
        setBit(x+1, y);
        setBit(x+1, y, matrix_tmp);
    }
    if( getPoint(x, y+1, matrix_tmp) != draw_mode ){
        stack[idx] = x;
        idx++;
        stack[idx] = y+1;
        idx++;
        setBit(x, y+1);
        setBit(x, y+1, matrix_tmp);
    }
    return idx;
}

// public function
void MAX7219_DotMatrix::point(int16_t x, int16_t y) {
    setBit(x, y);
}

void MAX7219_DotMatrix::line(int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
    line(x1, y1, x2, y2, NULL);
}
void MAX7219_DotMatrix::line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t *matrix_tmp) {
    int16_t min_x = (x1 < x2 )? x1:x2;
    int16_t min_y = (y1 < y2 )? y1:y2;

    for(int i = min_x; i <= min_x+abs(x2-x1); i++){

        if(x2-x1 == 0){
            // Avoid dividing by zero
            for(int j = min_y; j <= min_y+abs(y2-y1); j++) if(matrix_tmp) setBit(i, j, matrix_tmp); else setBit(i, j);
            break;
        }else{
            double val_y = (y2-y1)/double(x2-x1)*(i-x1) + y1;
            if(matrix_tmp) setBit(i, (uint16_t)val_y, matrix_tmp); else setBit(i, (uint16_t)val_y );
        }
    }
}

bool MAX7219_DotMatrix::triangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3) {

    line(x1, y1, x2, y2);
    line(x3, y3, x2, y2);
    line(x1, y1, x3, y3);

    // If fill status is not set, return
    if(!fill_status) return true;

    // reserve memory
    uint8_t* matrix_tmp = (uint8_t *)calloc(matrix_byte, sizeof(uint8_t));
    if (matrix_tmp == NULL) return false;    // if it could not reserve memory
    memset(matrix_tmp, (draw_mode)? 0b00000000:0b11111111, matrix_byte);

    line(x1, y1, x2, y2, matrix_tmp);
    line(x3, y3, x2, y2, matrix_tmp);
    line(x1, y1, x3, y3, matrix_tmp);

    double center_x = (x1+x2+x3)/3.0;
    double center_y = (y1+y2+y3)/3.0;

    bool result = closedAreaFill(center_x, center_y, matrix_tmp);
    if(matrix_tmp) free(matrix_tmp);
    return result;
}

void MAX7219_DotMatrix::rect(int16_t x, int16_t y, uint16_t w, uint16_t h) {

    int16_t end_x = x+w;
    int16_t end_y = y+h;

    line(x, y, x, end_y);
    line(x, y, end_x, y);
    line(x, end_y, end_x, end_y);
    line(end_x, y, end_x, end_y);


    if(!fill_status) return;

    // fill
    for(int i = y+1; i < end_y; i++){
        line(x+1, i, end_x-1, i);
    }
}

bool MAX7219_DotMatrix::quad(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, int16_t x4, int16_t y4) {
                            // leftTop, leftBottom, RightBottom, RightTop
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x4, y4);
    line(x1, y1, x4, y4);

    // If fill status is not set, return
    if(!fill_status) return true;

    // reserve memory
    uint8_t* matrix_tmp = (uint8_t *)calloc(matrix_byte, sizeof(uint8_t));
    if (matrix_tmp == NULL) return false;    // if it could not reserve memory
    memset(matrix_tmp, (draw_mode)? 0b00000000:0b11111111, matrix_byte);

    line(x1, y1, x2, y2, matrix_tmp);
    line(x2, y2, x3, y3, matrix_tmp);
    line(x3, y3, x4, y4, matrix_tmp);
    line(x1, y1, x4, y4, matrix_tmp);

    double center_x = (x1+x2+x3+x4)/4.0;
    double center_y = (y1+y2+y3+y4)/4.0;

    bool result = closedAreaFill(center_x, center_y, matrix_tmp);
    if(matrix_tmp) free(matrix_tmp);
    return result;
}

void MAX7219_DotMatrix::ellipse(int16_t x, int16_t y, int16_t w, int16_t h) {

    for(double i = 0; i <= 2* DM_PI; i+= 2* DM_PI/180.0 ){
        double point_x = x + w/2.0*cos(i);
        double point_y = y + h/2.0*sin(i);

        // if fill status is true, draw line.If not, draw point.
        if(fill_status){
            line(x, y, point_x, point_y);
        }else{
            setBit(point_x, point_y);
        }
    }
}

void MAX7219_DotMatrix::fill(void) {
    fill_status = true;
}

void MAX7219_DotMatrix::noFill(void) {
    fill_status = false;
}

void MAX7219_DotMatrix::allOn(void){
    memset(matrix, 0b11111111, matrix_byte);
}

void MAX7219_DotMatrix::allOff(void){
    memset(matrix, 0b00000000, matrix_byte);
}

void MAX7219_DotMatrix::setDrawMode(bool mode){
    draw_mode = mode;
}

void MAX7219_DotMatrix::toggle(int16_t x, int16_t y){
    if(!isWithin(x,y)) return;
    uint16_t idx = convertCoordinateToMatrixIndex(x, y);
    uint8_t bits = convertCoordinateToMatrixBit(x, y);
    matrix[idx] ^= bits;
}

bool MAX7219_DotMatrix::getPoint(int16_t x, int16_t y){
    return getPoint(x, y, NULL);
}
bool MAX7219_DotMatrix::getPoint(int16_t x, int16_t y, uint8_t *matrix_tmp){
    if(!isWithin(x,y)) return false;
    uint16_t idx = convertCoordinateToMatrixIndex(x, y);
    uint16_t bits = convertCoordinateToMatrixBit(x, y);
    uint16_t tmp = (matrix_tmp != NULL)? matrix_tmp[idx] : matrix[idx];
    return (uint16_t)(tmp & bits) > 0;
}

void MAX7219_DotMatrix::draw(void) {

    // vitual function for MAX_7219_DotMatrix_charSet
    scroll();

    if(rotate_state == DM_DIRECTION_0){

        for(uint8_t i = 1; i<=DM_DOT_COUNT; i++){
            digitalWrite(pin_cs, 0);
            for(int16_t count = matrix_byte; count >= 0; count-=8){

                // reverse byte(ex. 11010100 -> 00101011)
                uint8_t original_bits = matrix[count+i-1];
                uint8_t reverse_bits;
                int idx = DM_DOT_COUNT;
                while(idx--){
                    reverse_bits <<= 1;
                    reverse_bits |= (original_bits & 1);
                    original_bits >>= 1;
                }
                Write_MAX7219(DM_DOT_COUNT-i +1, reverse_bits);
            }
            digitalWrite(pin_cs, 1);
        }

    } else if(rotate_state == DM_DIRECTION_180) {

        for(uint8_t i = 1; i<=DM_DOT_COUNT; i++){
            digitalWrite(pin_cs, 0);
            for(int16_t count = 0; count < matrix_byte; count += 8){
                Write_MAX7219(i, matrix[count+i-1]);
            }
            digitalWrite(pin_cs, 1);
        }
    }

    // common
    digitalWrite(pin_cs, 0);
}

bool MAX7219_DotMatrix::setBrightness(uint8_t brightness){
    // only send 0x00-0x0f
    if(brightness > 0x0f) return false;

    Write_MAX7219Int(0x0a, brightness);
    return true;
}

bool MAX7219_DotMatrix::setDirection(uint8_t E_dd){

    if(E_dd > DM_DIRECTION_270) return false;

    rotate_state = E_dd;

    // sorry, we support only 0 and 180 now 。ﾟ(ﾟ∩'▽'∩ﾟ)ﾟ｡
    if(rotate_state == DM_DIRECTION_0 || rotate_state == DM_DIRECTION_270){
        rotate_state = DM_DIRECTION_0;
        return false;
    }

    return true;
}

uint32_t MAX7219_DotMatrix::getMemoryUsage(void){
    return matrix_byte;
}

void  MAX7219_DotMatrix::scroll(void){
    ;
}
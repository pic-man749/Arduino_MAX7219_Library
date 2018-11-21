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

// private function
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

    if(!isWithin(x,y)) return false;
    uint16_t index = convertCoordinateToMatrixIndex(x,y);
    uint8_t bits = convertCoordinateToMatrixBit(x);

    if(draw_mode){
        matrix[index] |= bits;
    } else {
        matrix[index] &= ~bits;
    }

    return true;
}
uint16_t MAX7219_DotMatrix::convertCoordinateToMatrixIndex(uint16_t x, uint16_t y){
    uint16_t upside    = (uint16_t)(y/8.0);   // count how many rows are on top
    uint16_t leftside  = (uint16_t)(x/8.0);   // count how many columns are on the left side
    uint8_t  thisblock = y%8;                 // count how many lines are on top in this block
    return upside*8*matrix_column + leftside*8 + thisblock;
}
uint8_t MAX7219_DotMatrix::convertCoordinateToMatrixBit(uint16_t x, uint16_t y){
    // Oops! we do not need y param! ꉂꉂ ( ˆᴗˆ  )
    return 0b10000000 >> (x%8);
}
uint8_t MAX7219_DotMatrix::convertCoordinateToMatrixBit(uint16_t x){
    return 0b10000000 >> (x%8);
}
bool MAX7219_DotMatrix::isWithin(int16_t x, int16_t y){
    return (0 <= x && x < matrix_column * 8 && 0<= y && y < matrix_row * 8);
}

// public function
void MAX7219_DotMatrix::point(int16_t x, int16_t y) {
    setBit(x, y);
}

void MAX7219_DotMatrix::line(int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
    int16_t min_x = (x1 < x2 )? x1:x2;
    int16_t min_y = (y1 < y2 )? y1:y2;

    for(int i = min_x; i <= min_x+abs(x2-x1); i++){

        if(x2-x1 == 0){
            // Avoid dividing by zero
            for(int j = min_y; j <= min_y+abs(y2-y1); j++) setBit(i, j);
            break;
        }else{
            double val_y = (y2-y1)/double(x2-x1)*(i-x1) + y1;
            if(val_y)
            setBit(i, (uint16_t)val_y );
        }

    }
}

void MAX7219_DotMatrix::triangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3) {

    line(x1, y1, x2, y2);
    line(x3, y3, x2, y2);
    line(x1, y1, x3, y3);

    // If fill status is not set, return
    if(!fill_status) return;

    // Write fill!
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

void MAX7219_DotMatrix::quad(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, int16_t x4, int16_t y4) {
                            // leftTop, leftBottom, RightBottom, RightTop
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x4, y4);
    line(x1, y1, x4, y4);

    // If fill status is not set, return
    if(!fill_status) return;

    // VERY DIFFICULT
}

void MAX7219_DotMatrix::ellipse(int16_t x, int16_t y, int16_t w, int16_t h) {
    ;
}

void MAX7219_DotMatrix::fill(void) {
    fill_status = true;
}

void MAX7219_DotMatrix::noFill(void) {
    fill_status = false;
}

void MAX7219_DotMatrix::translate(int16_t x, int16_t y) {
    ;
}

void MAX7219_DotMatrix::resetMatrix(void) {
    ;
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
    if(!isWithin(x,y)) return false;
    uint16_t idx = convertCoordinateToMatrixIndex(x, y);
    uint8_t bits = convertCoordinateToMatrixBit(x, y);
    uint8_t tmp = matrix[idx];
    return (tmp & bits != 0);
}

void MAX7219_DotMatrix::draw(void) {

    if(rotate_state == DM_DIRECTION_0){

        for(uint8_t i = 1; i<=8; i++){
            digitalWrite(pin_cs, 0);
            for(int16_t count = matrix_byte; count >= 0; count-=8){

                // reverse byte(ex. 11010100 -> 00101011)
                uint8_t original_bits = matrix[count+i-1];
                uint8_t reverse_bits;
                int idx = 8;
                while(idx--){
                    reverse_bits <<= 1;
                    reverse_bits |= (original_bits & 1);
                    original_bits >>= 1;
                }
                Write_MAX7219(8-i +1, reverse_bits);
            }
            digitalWrite(pin_cs, 1);
        }

    } else if(rotate_state == DM_DIRECTION_180) {

        for(uint8_t i = 1; i<=8; i++){
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
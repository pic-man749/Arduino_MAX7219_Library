#include <MAX7219_DotMatrix_charSet.h>

// constructor
MAX7219_DotMatrix_charSet::MAX7219_DotMatrix_charSet(uint8_t pin_clk, uint8_t pin_cs, uint8_t pin_din, uint8_t mr, uint8_t mc) :
    MAX7219_DotMatrix(pin_clk, pin_cs, pin_din, mr, mc)
{
    cursor_x = 0;
    cursor_y = 0;
    margin_left = 0;
    margin_top = 0;
    margin_bottom = 1;
    margin_right = 1;

    scroll_wait_time = 100;
    scroll_timer = 0;
    scroll_point = matrix_column * DM_DOT_COUNT -1;
    char_draw_mode = true;
    scroll_status = false;
}
MAX7219_DotMatrix_charSet::MAX7219_DotMatrix_charSet(uint8_t mr, uint8_t mc) :
    MAX7219_DotMatrix(mr, mc)
{
    cursor_x = 0;
    cursor_y = 0;
    margin_left = 0;
    margin_top = 0;
    margin_bottom = 1;
    margin_right = 1;

    scroll_wait_time = 100;
    scroll_timer = 0;
    scroll_point = matrix_column * DM_DOT_COUNT -1;
    char_draw_mode = true;
    scroll_status = false;

}
MAX7219_DotMatrix_charSet::~MAX7219_DotMatrix_charSet(){
    ;
}

// private functions
bool MAX7219_DotMatrix_charSet::direct(uint8_t idx){

    // if idx value over charSet size, return
    if(idx >= SIZE_OF_CHARSET) return false;

    cursor_x += margin_left;
    cursor_y += margin_top;

    for(int16_t column = 0; column < 5; column++){

        uint8_t tmp = pgm_read_byte(charSet_A01 + idx*5 + column);
        for(uint8_t row = 0; row < 8; row++){

            if( (tmp & (0b10000000 >> row)) > 0 ){
                MAX7219_DotMatrix::setBit(cursor_x+column, cursor_y+row);
            }else{
                if(char_draw_mode) MAX7219_DotMatrix::clearBit(cursor_x+column, cursor_y+row);
            }
        }
    }


    cursor_x += 5;
    // clear
    for(int i = 0; i<margin_right; i++){
        for(int j = 0; j<8; j++){
            MAX7219_DotMatrix::clearBit(cursor_x+i, cursor_y+j);
        }
    }
    cursor_x += margin_right;
    cursor_y -= margin_top;
}

// public function
bool MAX7219_DotMatrix_charSet::printCharDirect(int16_t x, int16_t y, uint8_t idx){

    if(idx >= SIZE_OF_CHARSET) return false;
    setCursor(x, y);
    return direct(idx);
}
bool MAX7219_DotMatrix_charSet::printCharDirect(uint8_t idx){
    if(idx >= SIZE_OF_CHARSET) return false;
    return direct(idx);
}

bool MAX7219_DotMatrix_charSet::printChar(int16_t x, int16_t y, char c){
    setCursor(x, y);
    return printChar(c);
}
bool MAX7219_DotMatrix_charSet::printChar(char c){

    // table
    if('!' <= c && c <= '}'){   // 00100001 ~ 01111111
        direct((char)c-'!');
    } else if(true){            // 未実装

    } else {    // unkown char
        direct(0b11111111);
    }
}
void MAX7219_DotMatrix_charSet::printStr(int16_t x, int16_t y, String str){
    setCursor(x, y);
    printStr(str);
}
void MAX7219_DotMatrix_charSet::printStr(String str){

    uint16_t count = str.length();
    for(uint16_t i = 0; i < count; i++){
        char c = str.charAt(i);
        // Serial.print("i = ");
        // Serial.print(i);
        // Serial.print(", c[0] = ");
        // Serial.println(c, BIN);
        printChar(c);
    }
}

void MAX7219_DotMatrix_charSet::setCursor(int16_t x, int16_t y){
    cursor_x = x;
    cursor_y = y;
}
void MAX7219_DotMatrix_charSet::setMargine(uint8_t side, int16_t value){
    switch(side){
        case DM_MARGINE_LEFT   : margin_left   = value; break;
        case DM_MARGINE_TOP    : margin_top    = value; break;
        case DM_MARGINE_BOTTOM : margin_bottom = value; break;
        case DM_MARGINE_RIGHT  : margin_right  = value; break;
        default: break;
    }
}

void MAX7219_DotMatrix_charSet::setScrollStr(String str){
    scroll_string = str;
    scroll_string_size = str.length();
    scroll_status = true;
}
void MAX7219_DotMatrix_charSet::setScrollStr(String str, uint16_t tim){
    scroll_wait_time = tim;
    setScrollStr(str);
}
void MAX7219_DotMatrix_charSet::scroll(void){

    if(scroll_status){
        if(millis() > scroll_timer + scroll_wait_time){
            scroll_timer = millis();
            printStr(scroll_point, cursor_y, scroll_string);
            scroll_point -= 1;
            Serial.print("scroll_point = ");
            Serial.print(scroll_point);
            Serial.print("scroll_string_size = ");
            Serial.println(-(int32_t)scroll_string_size * (5 + margin_right + margin_left) );
            if(scroll_point < -(int32_t)scroll_string_size * (5 + margin_right + margin_left) ){  // 再考
                scroll_point = matrix_column * DM_DOT_COUNT -1 + margin_right + margin_left;
            }
        }
    }
}

void MAX7219_DotMatrix_charSet::scrollStop(void){
    scroll_status = false;
}

void MAX7219_DotMatrix_charSet::setCharDrawMode(bool mode){
    char_draw_mode = mode;
}

int16_t MAX7219_DotMatrix_charSet::getCursorX(void){
    return cursor_x;
}
int16_t MAX7219_DotMatrix_charSet::getCursorY(void){
    return cursor_y;
}

// char ROM
const PROGMEM uint8_t MAX7219_DotMatrix_charSet::charSet_A01[] = {
    //0010 0001~0010 1111
    0b00000000, 0b00000000, 0b11110010, 0b00000000, 0b00000000,  // !
    0b00000000, 0b11100000, 0b00000000, 0b11100000, 0b00000000,  // "
    0b00101000, 0b11111110, 0b00101000, 0b11111110, 0b00101000,  // #
    0b00100100, 0b01010100, 0b11111110, 0b01010100, 0b01001000,  // $
    0b11000100, 0b11001000, 0b00010000, 0b00100110, 0b01000110,  // %
    0b01101100, 0b10010010, 0b10101010, 0b01000100, 0b00001010,  // &
    0b00000000, 0b10100000, 0b11000000, 0b00000000, 0b00000000,  // '
    0b00000000, 0b00111000, 0b01000100, 0b10000010, 0b00000000,  // (
    0b00000000, 0b10000010, 0b01000100, 0b00111000, 0b00000000,  // )
    0b00101000, 0b00010000, 0b01111100, 0b00010000, 0b00101000,  // *
    0b00010000, 0b00010000, 0b01111100, 0b00010000, 0b00010000,  // +
    0b00000000, 0b00001010, 0b00001100, 0b00000000, 0b00000000,  // ,
    0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00010000,  // -
    0b00000000, 0b00000110, 0b00000110, 0b00000000, 0b00000000,  // .
    0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000,  // /

    // 0011 0000~00111111
    0b01111100, 0b10001010, 0b10010010, 0b10100010, 0b01111100,  // 0
    0b00000000, 0b01000010, 0b11111110, 0b00000010, 0b00000000,  // 1
    0b01000010, 0b10000110, 0b10001010, 0b10010010, 0b01100010,  // 2
    0b10000100, 0b10000010, 0b10100010, 0b11010010, 0b10001100,  // 3
    0b00011000, 0b00101000, 0b01001000, 0b11111110, 0b00001000,  // 4
    0b11100100, 0b10100010, 0b10100010, 0b10100010, 0b10011100,  // 5
    0b00111100, 0b01010010, 0b10010010, 0b10010010, 0b00001100,  // 6
    0b10000000, 0b10001110, 0b10010000, 0b10100000, 0b11000000,  // 7
    0b01101100, 0b10010010, 0b10010010, 0b10010010, 0b01101100,  // 8
    0b01100000, 0b10010010, 0b10010010, 0b10010100, 0b01111000,  // 9
    0b00000000, 0b01101100, 0b01101100, 0b00000000, 0b00000000,  // :
    0b00000000, 0b01101010, 0b01101100, 0b00000000, 0b00000000,  // ;
    0b00010000, 0b00101000, 0b01000100, 0b10000010, 0b00000000,  // <
    0b00101000, 0b00101000, 0b00101000, 0b00101000, 0b00101000,  // =
    0b00000000, 0b10000010, 0b01000100, 0b00101000, 0b00010000,  // >
    0b01000000, 0b10000000, 0b10001010, 0b10010000, 0b01100000,  // ?

    // 0100 0000~0100 1111
    0b01001100, 0b10010010, 0b10011110, 0b10000010, 0b01111100,  // @
    0b01111110, 0b10001000, 0b10001000, 0b10001000, 0b01111110,  // A
    0b11111110, 0b10010010, 0b10010010, 0b10010010, 0b01101100,  // B
    0b01111100, 0b10000010, 0b10000010, 0b10000010, 0b01000100,  // C
    0b11111110, 0b10000010, 0b10000010, 0b01000100, 0b00111000,  // D
    0b11111110, 0b10010010, 0b10010010, 0b10010010, 0b10000010,  // E
    0b11111110, 0b10010000, 0b10010000, 0b10010000, 0b10000000,  // F
    0b01111100, 0b10000010, 0b10010010, 0b10010010, 0b01011110,  // G
    0b11111110, 0b00010000, 0b00010000, 0b00010000, 0b11111110,  // H
    0b00000000, 0b10000010, 0b11111110, 0b10000010, 0b00000000,  // I
    0b00000100, 0b00000010, 0b10000010, 0b11111100, 0b10000000,  // J
    0b11111110, 0b00010000, 0b00101000, 0b01000100, 0b10000010,  // K
    0b11111110, 0b00000010, 0b00000010, 0b00000010, 0b00000010,  // L
    0b11111110, 0b01000000, 0b00110000, 0b01000000, 0b11111110,  // M
    0b11111110, 0b00100000, 0b00010000, 0b00001000, 0b11111110,  // N
    0b01111100, 0b10000010, 0b10000010, 0b10000010, 0b01111100,  // O

    // 0101 0000~0101 1111
    0b11111110, 0b10010000, 0b10010000, 0b10010000, 0b01100000,  // P
    0b01111100, 0b10000010, 0b10001010, 0b10000100, 0b01111010,  // Q
    0b11111110, 0b10010000, 0b10011000, 0b10010100, 0b01100010,  // R
    0b01100010, 0b10010010, 0b10010010, 0b10010010, 0b10001100,  // S
    0b10000000, 0b10000000, 0b11111110, 0b10000000, 0b10000000,  // T
    0b11111100, 0b00000010, 0b00000010, 0b00000010, 0b11111100,  // U
    0b11111000, 0b00000100, 0b00000010, 0b00000100, 0b11111000,  // V
    0b11111100, 0b00000010, 0b00011100, 0b00000010, 0b11111100,  // W
    0b11000110, 0b00101000, 0b00010000, 0b00101000, 0b11000110,  // X
    0b11100000, 0b00010000, 0b00001110, 0b00010000, 0b11100000,  // Y
    0b10000110, 0b10001010, 0b10010010, 0b10100010, 0b11000010,  // Z
    0b00000000, 0b11111110, 0b10000010, 0b10000010, 0b00000000,  // [
    0b10101000, 0b01101000, 0b00111110, 0b01101000, 0b10101000,  // \(not "\", this is yen mark)
    0b00000000, 0b10000010, 0b10000010, 0b11111110, 0b00000000,  // ]
    0b00100000, 0b01000000, 0b10000000, 0b01000000, 0b00100000,  // ^
    0b00000010, 0b00000010, 0b00000010, 0b00000010, 0b00000010,  // _

    // 0110 0000~0110 1111
    0b00000000, 0b10000000, 0b01000000, 0b00100000, 0b00000000,  // `
    0b00000100, 0b00101010, 0b00101010, 0b00101010, 0b00011110,  // a
    0b11111110, 0b00010010, 0b00100010, 0b00100010, 0b00011100,  // b
    0b00011100, 0b00100010, 0b00100010, 0b00100010, 0b00000100,  // c
    0b00011100, 0b00100010, 0b00100010, 0b00010010, 0b11111110,  // d
    0b00011100, 0b00101010, 0b00101010, 0b00101010, 0b00011000,  // e
    0b00010000, 0b01111110, 0b10010000, 0b10000000, 0b01000000,  // f
    0b00110000, 0b01001010, 0b01001010, 0b01001010, 0b01111100,  // g
    0b11111110, 0b00010000, 0b00100000, 0b00100000, 0b00011110,  // h
    0b00000000, 0b00100010, 0b10111110, 0b00000010, 0b00000000,  // i
    0b00000100, 0b00000010, 0b00100010, 0b10111100, 0b00000000,  // j
    0b11111110, 0b00001000, 0b00010100, 0b00100010, 0b00000000,  // k
    0b00000000, 0b10000010, 0b11111110, 0b00000010, 0b00000000,  // l
    0b00111110, 0b00100000, 0b00011000, 0b00100000, 0b00011110,  // m
    0b00111110, 0b00010000, 0b00100000, 0b00100000, 0b00011110,  // n
    0b00011100, 0b00100010, 0b00100010, 0b00100010, 0b00011100,  // o

    // 0111 0000~0111 1111
    0b00111110, 0b00101000, 0b00101000, 0b00101000, 0b00010000,  // p
    0b00010000, 0b00101000, 0b00101000, 0b00011000, 0b00111110,  // q
    0b00111110, 0b00010000, 0b00100000, 0b00100000, 0b00010000,  // r
    0b00010010, 0b00101010, 0b00101010, 0b00101010, 0b00000100,  // s
    0b00100000, 0b11111100, 0b00100010, 0b00000010, 0b00000100,  // t
    0b00111100, 0b00000010, 0b00000010, 0b00000100, 0b00111110,  // u
    0b00111000, 0b00000100, 0b00000010, 0b00000100, 0b00111000,  // v
    0b00111100, 0b00000010, 0b00001100, 0b00000010, 0b00111100,  // w
    0b00100010, 0b00010100, 0b00001000, 0b00010100, 0b00100010,  // x
    0b00110000, 0b00001010, 0b00001010, 0b00001010, 0b00111100,  // y
    0b00100010, 0b00100110, 0b00101010, 0b00110010, 0b00100010,  // z
    0b00000000, 0b00010000, 0b01101100, 0b10000010, 0b00000000,  //
    0b00000000, 0b00000000, 0b11111110, 0b00000000, 0b00000000,  // |
    0b00000000, 0b10000010, 0b01101100, 0b00010000, 0b00000000,  // }
    0b00010000, 0b00010000, 0b01010100, 0b00111000, 0b00010000,  // ->
    0b00010000, 0b00111000, 0b01010100, 0b00010000, 0b00010000,  // <-

    // 1010 0001~1010 1111
    0b00001110, 0b00001010, 0b00001110, 0b00000000, 0b00000000,  // 。
    0b00000000, 0b00000000, 0b11110000, 0b10000000, 0b10000000,  // 「
    0b00000010, 0b00000010, 0b00011110, 0b00000000, 0b00000000,  // 」
    0b00001000, 0b00000100, 0b00000010, 0b00000000, 0b00000000,  // 、
    0b00000000, 0b00011000, 0b00011000, 0b00000000, 0b00000000,  // ・
    0b01010000, 0b01010000, 0b01010010, 0b01010100, 0b01111000,  // ｦ
    0b00100000, 0b00100010, 0b00101100, 0b00101000, 0b00110000,  // ｧ
    0b00000100, 0b00001000, 0b00011110, 0b00100000, 0b00000000,  // ｨ
    0b00011000, 0b00010000, 0b00110010, 0b00010010, 0b00011100,  // ｩ
    0b00100010, 0b00100010, 0b00111110, 0b00100010, 0b00100010,  // ｪ
    0b00010010, 0b00010100, 0b00011000, 0b00111110, 0b00010000,  // ｫ
    0b00010000, 0b00111110, 0b00010000, 0b00010100, 0b00011000,  // ｬ
    0b00000010, 0b00010010, 0b00010010, 0b00011110, 0b00000010,  // ｭ
    0b00101010, 0b00101010, 0b00101010, 0b00111110, 0b00000000,  // ｮ
    0b00011000, 0b00000000, 0b00011010, 0b00000010, 0b00011100,  // ｯ

    // 1011 0000~1011 1111
    0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00010000,  // -
    0b10000000, 0b10000010, 0b10111100, 0b10010000, 0b11100000,  // ｱ
    0b00001000, 0b00010000, 0b00111110, 0b01000000, 0b10000000,  // ｲ
    0b01110000, 0b01000000, 0b11000010, 0b01000100, 0b01111000,  // ｳ
    0b01000010, 0b01000010, 0b01111110, 0b01000010, 0b01000010,  // ｴ
    0b01000100, 0b01001000, 0b01010000, 0b11111110, 0b01000000,  // ｵ
    0b01000010, 0b11111100, 0b01000000, 0b01000010, 0b01111100,  // ｶ
    0b01010000, 0b01010000, 0b11111110, 0b01010000, 0b01010000,  // ｷ
    0b00010000, 0b01100010, 0b01000010, 0b01000100, 0b01111000,  // ｸ
    0b00100000, 0b11000000, 0b01000010, 0b01111100, 0b01000000,  // ｹ
    0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01111110,  // ｺ
    0b01000000, 0b11110010, 0b01000100, 0b11111000, 0b01000000,  // ｻ
    0b01010010, 0b01010010, 0b00000010, 0b00000100, 0b00111000,  // ｼ
    0b01000010, 0b01000100, 0b01001000, 0b01010100, 0b01100010,  // ｽ
    0b01000000, 0b11111100, 0b01000010, 0b01010010, 0b01100010,  // ｾ
    0b01100000, 0b00010010, 0b00000010, 0b00000100, 0b01110000,  // ｿ

    // 1100 0000~1100 1111
    0b00010000, 0b01100010, 0b01010010, 0b01001100, 0b01111000,  // ﾀ
    0b01010000, 0b01010010, 0b01111100, 0b10010000, 0b00010000,  // ﾁ
    0b01110000, 0b00000000, 0b01110010, 0b00000100, 0b01111000,  // ﾂ
    0b00100000, 0b10100010, 0b10111100, 0b10100000, 0b00100000,  // ﾃ
    0b00000000, 0b11111110, 0b00010000, 0b00001000, 0b00000000,  // ﾄ
    0b00100010, 0b00100100, 0b11111000, 0b00100000, 0b00100000,  // ﾅ
    0b00000010, 0b01000010, 0b01000010, 0b01000010, 0b00000010,  // ﾆ
    0b01000010, 0b01010100, 0b01001000, 0b01010100, 0b01100000,  // ﾇ
    0b01000100, 0b01001000, 0b11011110, 0b01101000, 0b01000100,  // ﾈ
    0b00000000, 0b00000010, 0b00000100, 0b11111000, 0b00000000,  // ﾉ
    0b00011110, 0b00000000, 0b01000000, 0b00100000, 0b00011110,  // ﾊ
    0b11111100, 0b00100010, 0b00100010, 0b00100010, 0b00100010,  // ﾋ
    0b01000000, 0b01000010, 0b01000010, 0b01000100, 0b01111000,  // ﾌ
    0b00100000, 0b01000000, 0b00100000, 0b00010000, 0b00001100,  // ﾍ
    0b01001100, 0b01000000, 0b11111110, 0b01000000, 0b01001100,  // ﾎ
    0b01000000, 0b01001000, 0b01000100, 0b01001010, 0b01110000,  // ﾏ

    // 1101 0000~1101 1111
    0b00000000, 0b01010100, 0b01010100, 0b01010100, 0b00000010,  // ﾐ
    0b00011100, 0b00100100, 0b01000100, 0b00000100, 0b00001110,  // ﾑ
    0b00000010, 0b00010100, 0b00001000, 0b00010100, 0b01100000,  // ﾒ
    0b01010000, 0b01111100, 0b01010010, 0b01010010, 0b01010010,  // ﾓ
    0b00100000, 0b11111110, 0b00100000, 0b00101000, 0b00110000,  // ﾔ
    0b00000010, 0b01000010, 0b01000010, 0b01111110, 0b00000010,  // ﾕ
    0b01010010, 0b01010010, 0b01010010, 0b01010010, 0b01111110,  // ﾖ
    0b00100000, 0b10100000, 0b10100010, 0b10100100, 0b00111000,  // ﾗ
    0b11110000, 0b00000010, 0b00000100, 0b11111000, 0b00000000,  // ﾘ
    0b00111110, 0b00000000, 0b01111110, 0b00000010, 0b00001100,  // ﾙ
    0b01111110, 0b00000010, 0b00000100, 0b00001000, 0b00010000,  // ﾚ
    0b01111110, 0b01000010, 0b01000010, 0b01000010, 0b01111110,  // ﾛ
    0b01110000, 0b01000000, 0b01000010, 0b01000100, 0b01111000,  // ﾜ
    0b01000010, 0b01000010, 0b00000010, 0b00000100, 0b00011000,  // ﾝ
    0b01000000, 0b00100000, 0b10000000, 0b01000000, 0b00000000,  // ゛
    0b11100000, 0b10100000, 0b11100000, 0b00000000, 0b00000000,  // ゜

    // 1110 0000~1110 1111
    0b00011100, 0b00100010, 0b00010010, 0b00001100, 0b00110010,  // α
    0b00000100, 0b10101010, 0b00101010, 0b10101010, 0b00011110,  // ä
    0b01111111, 0b10101000, 0b10101000, 0b10101000, 0b01010000,  // β
    0b00010100, 0b00101010, 0b00101010, 0b00100010, 0b00000100,  // ε
    0b11111111, 0b00001000, 0b00001000, 0b00010000, 0b11111000,  // μ
    0b00011100, 0b00100010, 0b00110010, 0b00101010, 0b00100100,  // σ
    0b00111111, 0b01001000, 0b10001000, 0b10001000, 0b01110000,  // ρ
    0b01110000, 0b10001001, 0b10001001, 0b10001001, 0b11111110,  // g
    0b00000100, 0b00000010, 0b00111100, 0b00100000, 0b00100000,  // √
    0b00100000, 0b00100000, 0b00000000, 0b01110000, 0b00000000,  // -1
    0b00000010, 0b00000001, 0b00100001, 0b10111110, 0b00000000,  // j(short)
    0b01010000, 0b00100000, 0b01010000, 0b00000000, 0b00000000,  // x
    0b00011000, 0b00100100, 0b01111110, 0b00100100, 0b00001000,  //
    0b00101000, 0b11111110, 0b00101010, 0b00000010, 0b00000010,  //
    0b00111110, 0b10010000, 0b10100000, 0b10100000, 0b00011110,  //
    0b00011100, 0b10100010, 0b00100010, 0b10100010, 0b00011100,  // Õ

    // 1111 0000~1111 1111
    0b11111111, 0b01001000, 0b10001000, 0b10001000, 0b01110000,  // p
    0b01110000, 0b10001000, 0b10001000, 0b01001000, 0b11111111,  // q
    0b00111100, 0b01010010, 0b01010010, 0b01010010, 0b00111100,  // θ
    0b00001100, 0b00010100, 0b00001000, 0b00010100, 0b00011000,  // ∞
    0b00011010, 0b00100110, 0b00100000, 0b00100110, 0b00011010,  // Ω
    0b00111110, 0b10000001, 0b00000001, 0b10000010, 0b00111111,  // ü
    0b11000110, 0b10101010, 0b10010010, 0b10000010, 0b10000010,  // Σ
    0b00100010, 0b00111100, 0b00100000, 0b00111110, 0b00100010,  // π
    0b10100010, 0b10010100, 0b10001000, 0b10010100, 0b10100010,  // -x
    0b11110000, 0b00001001, 0b00001001, 0b00001001, 0b11111110,  // y
    0b00101000, 0b00101000, 0b00111110, 0b00101000, 0b01001000,  // 千
    0b00100010, 0b00111100, 0b00101000, 0b00101000, 0b00101110,  // 万
    0b00111110, 0b00101000, 0b00111000, 0b00101000, 0b00111110,  // 円
    0b00010000, 0b00010000, 0b01010100, 0b00010000, 0b00010000,  // ÷
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,  // ' '
    0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111   // ■
};

const uint8_t MAX7219_DotMatrix_charSet::SIZE_OF_CHARSET = sizeof(charSet_A01) / sizeof(uint8_t) / 5.0;

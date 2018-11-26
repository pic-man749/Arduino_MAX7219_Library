#include <avr/pgmspace.h>
#include <MAX7219_DotMatrix.h>

class MAX7219_DotMatrix_charSet : public MAX7219_DotMatrix{

    private:
        const PROGMEM  dataType  prog_uchar[][5] = {
            {0b01111110, 0b10001000, 0b10001000, 0b10001000, 0b01111110},  // A
            {0b11111110, 0b10010010, 0b10010010, 0b10010010, 0b01101100},  // B
            {0b01111100, 0b10000010, 0b10000010, 0b10000010, 0b01000100},  // C
            {0b11111110, 0b10000010, 0b10000010, 0b01000100, 0b00111000},  // D
            {0b11111110, 0b10010010, 0b10010010, 0b10010010, 0b10000010},  // E
            {0b11111110, 0b10010000, 0b10010000, 0b10010000, 0b10000000},  // F
            {0b01111100, 0b10000010, 0b10010010, 0b10010010, 0b01011110},  // G
            {0b11111110, 0b00010000, 0b00010000, 0b00010000, 0b11111110},  // H
            {0b00000000, 0b10000010, 0b11111110, 0b10000010, 0b00000000},  // I
            {0b00000100, 0b00000010, 0b10000010, 0b11111100, 0b10000000},  // J
            {0b11111110, 0b00010000, 0b00101000, 0b01000100, 0b10000010},  // K
            {0b11111110, 0b00000010, 0b00000010, 0b00000010, 0b00000010},  // L
            {0b11111110, 0b01000000, 0b00110000, 0b11111110, 0b11111110},  // M
            {0b11111110, 0b00100000, 0b00010000, 0b00001000, 0b11111110},  // N
            {0b01111100, 0b10000010, 0b10000010, 0b10000010, 0b01111100},  // O
            {0b11111110, 0b01001000, 0b01001000, 0b01001000, 0b01100000},  // P
            {0b01111100, 0b10000010, 0b10001010, 0b10000100, 0b01000010},  // Q
            {0b11111110, 0b10010000, 0b10011000, 0b10010100, 0b01100010},  // R
            {0b01100010, 0b10010010, 0b10010010, 0b10010010, 0b10001100},  // S
            {0b10000000, 0b10000000, 0b11111110, 0b10000000, 0b10000000},  // T
            {0b11111100, 0b00000010, 0b00000010, 0b00000010, 0b11111100},  // U
            {0b11111000, 0b00000100, 0b00000010, 0b00000100, 0b11111000},  // V
            {0b11111100, 0b00000010, 0b00011100, 0b00000010, 0b11111100},  // W
            {0b11000110, 0b00101000, 0b00010000, 0b00101000, 0b11000110},  // X
            {0b11100000, 0b00010000, 0b00001110, 0b00010000, 0b11100000},  // Y
            {0b10000110, 0b10001010, 0b10010010, 0b10100010, 0b11000010},  // Z

            {0b00000100, 0b00101010, 0b00101010, 0b00101010, 0b00011110},  // a
            {0b11111110, 0b00010010, 0b00100010, 0b00100010, 0b00011100},  // b
            {0b00011100, 0b00100010, 0b00100010, 0b00100010, 0b00000100},  // c
            {0b00011100, 0b00100010, 0b00100010, 0b00010010, 0b11111110},  // d
            {0b00011100, 0b00101010, 0b00101010, 0b00101010, 0b00011000},  // e
            {0b00010000, 0b01111110, 0b10010000, 0b10000000, 0b01000000},  // f
            {0b00110000, 0b01001010, 0b01001010, 0b01001010, 0b01111100},  // g
            {0b11111110, 0b00010000, 0b00100000, 0b00100000, 0b00011110},  // h
            {0b00000000, 0b00100010, 0b10111110, 0b00000010, 0b00000000},  // i
            {0b00000100, 0b00000010, 0b00100010, 0b10111100, 0b00000000},  // j
            {0b11111110, 0b00001000, 0b00010100, 0b00100010, 0b00000000},  // k
            {0b00000000, 0b10000010, 0b11111110, 0b00000010, 0b00000000},  // l
            {0b00111110, 0b00011000, 0b00100000, 0b00011110, 0b00000000},  // m
            {0b00111110, 0b00010000, 0b00100000, 0b00100000, 0b00011110},  // n
            {0b00011100, 0b00100010, 0b00100010, 0b00100010, 0b00011100},  // o
            {0b00111110, 0b00101000, 0b00101000, 0b00101000, 0b00010000},  // p
            {0b00111110, 0b00010000, 0b00101000, 0b00101000, 0b00111110},  // q
            {0b00111110, 0b00010000, 0b00100000, 0b00100000, 0b00010000},  // r
            {0b00010010, 0b00101010, 0b00101010, 0b00101010, 0b00000100},  // s
            {0b00100000, 0b11111100, 0b00100010, 0b00000010, 0b00000100},  // t
            {0b00111100, 0b00000010, 0b00000010, 0b00000100, 0b00111110},  // u
            {0b00111000, 0b00000100, 0b00000010, 0b00000100, 0b00111000},  // v
            {0b00111100, 0b00000010, 0b00001100, 0b00000010, 0b00111100},  // w
            {0b00100010, 0b00010100, 0b00001000, 0b00010100, 0b00100010},  // x
            {0b00110000, 0b00001010, 0b00001010, 0b00001010, 0b00111100},  // y
            {0b00100010, 0b00100110, 0b00101010, 0b00110010, 0b00100010},  // z

            {0b0, 0b0, 0b0, 0b0, 0b0},  // ｦ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ｱ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ｲ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ｳ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ｴ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ｵ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ｶ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ｷ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ｸ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ｹ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ｺ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ｻ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ｼ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ｽ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ｾ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ｿ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾀ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾁ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾂ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾃ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾄ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾅ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾆ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾇ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾈ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾉ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾊ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾋ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾌ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾍ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾎ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾏ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾐ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾑ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾒ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾓ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾔ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾕ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾖ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾗ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾘ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾙ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾚ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾛ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾜ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ﾝ
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ゛
            {0b0, 0b0, 0b0, 0b0, 0b0},  // ゜
        };

    public:

};
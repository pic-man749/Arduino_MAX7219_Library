#include "Arduino_MAX7219_Library.h"

// constructor
MAX7219_DotMatrix::MAX7219_DotMatrix(uint8_t pin_clk, uint8_t pin_cs, uint8_t pin_din, uint8_t matrix_count) :
    begun(false), draw_mode(true), fill_status(false), offset_x(0), offset_y(0)
{
    setPin(pin_clk, pin_cs, pin_din);
    setMatrixCount(matrix_count);
}

// initialize function
void MAX7219_DotMatrix::setPin(uint8_t p_clk, uint8_t p_cs, uint8_t p_din){
    pin_clk = p_clk;
    pin_cs = p_cs;
    pin_din = p_din;
}

void MAX7219_DotMatrix::setMatrixCount(uint8_t mc){
    matrix_count = mc;
}

void MAX7219_DotMatrix::begin(void) {
    pinMode(pin_clk, OUTPUT);
    pinMode(pin_cs, OUTPUT);
    pinMode(pin_din, OUTPUT);
    digitalWrite(pin_clk, LOW);
    digitalWrite(pin_cs, LOW);
    digitalWrite(pin_din, LOW);

    begun = true;
}

// public function
void point(uint16_t x, uint16_t y) {
    ;
}

void line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    ;
}

void triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3) {
    ;
}

void rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    ;
}

void quad(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t x4, uint16_t y4) {
    ;
}

void ellipse(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    ;
}

void fill(void) {
    ;
}

void noFill(void) {
    ;
}

void translate(uint16_t x, uint16_t y) {
    ;
}

void resetMatrix(void) {
    ;
}

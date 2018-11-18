#include "Arduino_MAX7219_Library.h"
#include <SPI.h>

// constructor
MAX7219_DotMatrix::MAX7219_DotMatrix(uint8_t pin_clk, uint8_t pin_cs, uint8_t pin_din, uint8_t matrix_row, uint8_t matrix_column) :
    begun(false), draw_mode(true), fill_status(false), offset_x(0), offset_y(0)
{
    setPin(pin_clk, pin_cs, pin_din);
    setMatrixCount(matrix_row, matrix_column);
}
MAX7219_DotMatrix::MAX7219_DotMatrix(uint8_t matrix_row, uint8_t matrix_column) :
    begun(false), draw_mode(true), fill_status(false), offset_x(0), offset_y(0)
{
    setPin(13, 10, 11);
    setMatrixCount(matrix_row, matrix_column);
}

MAX7219_DotMatrix::~MAX7219_DotMatrix(){
    if(matrix) free(matrix);
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

void MAX7219_DotMatrix::setRowColumn(uint8_t r, uint8_t c){
    matrix_row = r;
    matrix_column = c;
    matrix_byte = 8 * matrix_row * matrix_column;
}

void MAX7219_DotMatrix::begin(void) {
    pinMode(pin_clk, OUTPUT);
    pinMode(pin_cs, OUTPUT);
    pinMode(pin_din, OUTPUT);

    // reserve memory
    matrix = (uint8_t *)calloc(sizeof(uint8_t) * matrix_byte);
    if (matrix == NULL) exit(0);    // if it could not reserve memory, exit(0)

    // original : http://akizukidenshi.com/download/ds/sainsmar/max7219_SPI_20170916.zip
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(0);

    Write_MAX7219Int(0x09, 0x00);
    Write_MAX7219Int(0x0a, 0x04);
    Write_MAX7219Int(0x0b, 0x07);
    Write_MAX7219Int(0x0c, 0x01);
    Write_MAX7219Int(0x0f, 0x00);
    Write_MAX7219Int(0x00, 0x00);//shift data
    Write_MAX7219Int(0x00, 0x00);//shift data
    Write_MAX7219Int(0x00, 0x00);//shift data
    delay(100);

    begun = true;
}

// private function
void MAX7219_DotMatrix::Write_MAX7219(char addr, char dat){
    SPI.transfer(addr);
    SPI.transfer(dat);
}
void MAX7219_DotMatrix::Write_MAX7219Int(char addr, char dat){
    digitalWrite(pin_cs, 0);
    SPI.transfer(addr);
    SPI.transfer(dat);
    digitalWrite(pin_cs, 1);
}

// public function
void MAX7219_DotMatrix::point(uint16_t x, uint16_t y) {
    ;
}

void MAX7219_DotMatrix::line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    ;
}

void MAX7219_DotMatrix::triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3) {
    ;
}

void MAX7219_DotMatrix::rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    ;
}

void MAX7219_DotMatrix::quad(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t x4, uint16_t y4) {
    ;
}

void MAX7219_DotMatrix::ellipse(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    ;
}

void MAX7219_DotMatrix::fill(void) {
    ;
}

void MAX7219_DotMatrix::noFill(void) {
    ;
}

void MAX7219_DotMatrix::translate(uint16_t x, uint16_t y) {
    ;
}

void MAX7219_DotMatrix::resetMatrix(void) {
    ;
}

void allOn(void){
    ;
}

void allOff(void){
    ;
}

void setDrawMode(mode){
    ;
}


void MAX7219_DotMatrix::draw(void) {
    for(uint16_t count = matrix_byte - 1; count > 0; count++){
        for(uint8_t addr = 1; addr <= 8; addr++){
            Write_MAX7219(addr, matrix[count]);
        }
    }
    digitalWrite(pin_cs, 0);
}
// Arduino
#ifndef ARDUINO_MAX7219_H
#define ARDUINO_MAX7219_H

#if (ARDUINO >= 100)
    #include <Arduino.h>
#else
    #include <WProgram.h>
    #include <pins_arduino.h>
#endif

// constants

// main
class MAX7219_DotMatrix {

    public:
        // constructor
        MAX7219_DotMatrix(uint8_t pin_clk, uint8_t pin_cs, uint8_t pin_din, uint8_t matrix_count);

        // public functions
        void begin(void);
        void point(uint16_t x, uint16_t y);
        void line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
        void triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3);
        void rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
        void quad(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t x4, uint16_t y4);
        void ellipse(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
        void fill(void);
        void noFill(void);
        void translate(uint16_t x, uint16_t y);
        void resetMatrix(void);

    private:
        // private var
        boolean begun, fill_status, draw_mode;
        uint8_t pin_clk, pin_cs, pin_din, matrix_count;
        uint16_t offset_x, offset_y;

        // private functions
        void setPin(uint8_t pin_clk, uint8_t pin_cs, uint8_t pin_din);
        void setMatrixCount(uint8_t matrix_count);

};

#endif
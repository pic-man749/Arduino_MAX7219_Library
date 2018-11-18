// Arduino
#ifndef MAX7219_DotMatrix_H
#define MAX7219_DotMatrix_H

#if (ARDUINO >= 100)
    #include <Arduino.h>
#else
    #include <WProgram.h>
    #include <pins_arduino.h>
#endif

// constants
// single  : 0bXXXXXXXX XXXXXXXX
//             |||||||| ||||||||
//             |||||||| ||||++++- D12~15 : unused
//             |||||||| ++++----- D8~11  : address
//             ++++++++---------- D0~D7  : data
// send data from MSB, last LED

// main
class MAX7219_DotMatrix {

    private:
        // private var
        bool begun, fill_status, draw_mode;
        uint8_t pin_clk, pin_cs, pin_din, matrix_row, matrix_column;
        uint16_t offset_x, offset_y;
        uint32_t matrix_byte;
        uint8_t* matrix;
        /*  matrix[] example:
            If you create 2*4 matrix, matrix number define ...
            ┌─┬─┬─┬─┐
            │1 │2 │3 │4 │
            ├─┼─┼─┼─┤
            │5 │6 │7 │8 │
            └─┴─┴─┴─┘
            And LeftTop matrix's LED is point(0,0).
            If you enlarge the figure above it looks like the figure below
            ┌────────┬───   ...   ───┐
            │(0,0)      (7,0)│(8,0)          (31,0)│
            │                │                     │
            │       1        │     2   ...   4     │
            │                │                     │
            │(0,7)      (7,7)│(8,7)          (31,7)│
            ├────────┼         ...         ┤
            │(0,8)      (7,8)│(8,8)          (31,8)│
            │                │                     │
            │       5        │     6   ...   8     │
            │                │                     │
            │(0,15)    (7,15)│(8,15)        (31,15)│
            └────────┴───   ...     ──┘
            Then, matrix array lined up like this:
            matrix[] ={ MSB (0 ,0 ) ... (7 ,0) LSB  // --- start of matrix 1---
                            (0 ,1 ) ... (7 ,1)      // 1 line 1byte(uint8_t)
                                    ...
                            (0 ,7 ) ... (7 ,7)      // ____ end of matrix 1 ___
                            (8 ,0 ) ... (15 ,7)     // ---start of matrix 2---
                                    ...
                            (8 ,7 ) ... (15 ,7)     // ____ end of matrix 2 ___
                                    ...
                                    ...
                                    ...
                            (24 ,8) ... (31 ,15)    // ____ end of matrix 8 ___
                       }
            1 bit correspond to LED status(0->off, 1->on).
        */

        // private functions
        void setPin(uint8_t pin_clk, uint8_t pin_cs, uint8_t pin_din);
        void setRowColumn(uint8_t r, uint8_t c);
        void Write_MAX7219(uint8_t addr, uint8_t dat);
        void Write_MAX7219Int(uint8_t addr, uint8_t dat);
        void setBit(uint16_t index, uint8_t bit);
        uint16_t convertCoordinateToMatrixIndex(uint16_t x, uint16_t y);
        uint8_t  convertCoordinateToMatrixBit(uint16_t x, uint16_t y);
        uint8_t  convertCoordinateToMatrixBit(uint16_t x);

    public:
        // constructor
        MAX7219_DotMatrix(uint8_t pin_clk, uint8_t pin_cs, uint8_t pin_din, uint8_t matrix_row, uint8_t matrix_column);
        MAX7219_DotMatrix(uint8_t matrix_row, uint8_t matrix_column);
        ~MAX7219_DotMatrix();

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
        void allOn(void);
        void allOff(void);
        void setDrawMode(bool mode);
        void toggle(uint16_t x, uint16_t y);
        bool getPoint(uint16_t x, uint16_t y);
        void draw(void);
};

#endif
// Arduino
#ifndef MAX7219_DotMatrix_H
#define MAX7219_DotMatrix_H

#if (ARDUINO >= 100)
    #include <Arduino.h>
#else
    #include <WProgram.h>
    #include <pins_arduino.h>
#endif

#define DM_DIRECTION_0   0
#define DM_DIRECTION_90  1
#define DM_DIRECTION_180 2
#define DM_DIRECTION_270 3
#define DM_DOT_COUNT 8.0
#define DM_ON true
#define DM_OFF false
#define DM_PI 3.141592653589793

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
        uint8_t pin_clk, pin_cs, pin_din, matrix_row, matrix_column, rotate_state;
        uint16_t offset_x, offset_y;
        uint32_t matrix_byte;
        uint8_t* matrix;
        /*  matrix[] example:
            If you create 2*4 matrix, matrix number define ...
                        ┌─┬─┬─┬─┐
             Arduino ===│1 │2 │3 │4 │->to No.5
                        ├─┼─┼─┼─┤
             from N0.4->│5 │6 │7 │8 │
                        └─┴─┴─┴─┘
            And LeftTop matrix's LED is point(0,0).
            If you enlarge the figure above it looks like the figure below
                            ┌────────┬───   ...   ───┐
                      ┌─> │(0,0)      (7,0)│(8,0)          (31,0)│─┐
               Arduino├─> │                │                     │─┤
                 SPI  ┼─> │       1        │     2   ...   4     │─┼> connect No.5 DotMatrix DataIn
                PORTs ├─> │                │                     │─┤
                      └─> │(0,7)      (7,7)│(8,7)          (31,7)│─┘
                            ├────────┼         ...         ┤
                          ->│(0,8)      (7,8)│(8,8)          (31,8)│
                          ->│                │                     │
                 from No.4->│       5        │     6   ...   8     │  (end)
                          ->│                │                     │
                          ->│(0,15)    (7,15)│(8,15)        (31,15)│
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
        bool setBit(int16_t x, int16_t y);
        bool setBit(int16_t x, int16_t y, uint8_t matrix_tmp[]);
        uint16_t convertCoordinateToMatrixIndex(uint16_t x, uint16_t y);
        uint8_t  convertCoordinateToMatrixBit(uint16_t x, uint16_t y);
        uint8_t  convertCoordinateToMatrixBit(uint16_t x);
        bool isWithin(int16_t x, int16_t y);
        bool closedAreaFill(int16_t center_x, int16_t center_y, uint8_t *matrix_tmp);
        int16_t closedAreaFillLoop(int16_t idx, int16_t *stack, uint8_t *matrix_tmp);

    public:

        // constructor
        MAX7219_DotMatrix(uint8_t pin_clk, uint8_t pin_cs, uint8_t pin_din, uint8_t matrix_row, uint8_t matrix_column);
        MAX7219_DotMatrix(uint8_t matrix_row, uint8_t matrix_column);
        ~MAX7219_DotMatrix();

        // public functions
        bool begin(void);
        void point(int16_t x, int16_t y);
        void line(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
        void line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t *matrix_tmp);
        bool triangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3);
        void rect(int16_t x, int16_t y, uint16_t w, uint16_t h);
        bool quad(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, int16_t x4, int16_t y4);
        void ellipse(int16_t x, int16_t y, int16_t w, int16_t h);
        void fill(void);
        void noFill(void);
        void allOn(void);
        void allOff(void);
        void setDrawMode(bool mode);
        void toggle(int16_t x, int16_t y);
        bool getPoint(int16_t x, int16_t y);
        bool getPoint(int16_t x, int16_t y, uint8_t *matrix_tmp);
        void draw(void);
        bool setBrightness(uint8_t brightness);
        bool setDirection(uint8_t E_dd);
};

#endif

/*
    TODO:
        * 回転モードの実装
        * 文字の実装
            * 背景塗りつぶし設定
        * 座標変換のサポート（負の値入ってきたとき死ぬ）
        * matrix[]の書き換えするときに範囲外チェックしてない
        * SPI.begin()のデバイスによっての個別設定

        * draw_mode = falseででない getPoint()の返り値がおかしい

*/

#include <avr/pgmspace.h>
#include <MAX7219_DotMatrix.h>

#define DM_MARGINE_LEFT     0
#define DM_MARGINE_TOP      1
#define DM_MARGINE_BOTTOM   2
#define DM_MARGINE_RIGHT    3


class MAX7219_DotMatrix_charSet : public MAX7219_DotMatrix{

    private:
        static const PROGMEM uint8_t charSet_A01[];
        uint8_t margin_left, margin_top, margin_bottom, margin_right;
        uint16_t cursor_x, cursor_y;

        // methods
        bool direct(uint16_t x, int16_t y, uint8_t idx);

    public:
        // constructor
        MAX7219_DotMatrix_charSet(uint8_t pin_clk, uint8_t pin_cs, uint8_t pin_din, uint8_t mr, uint8_t mc);
        MAX7219_DotMatrix_charSet(uint8_t mr, uint8_t mc);
        ~MAX7219_DotMatrix_charSet();

        static const uint8_t SIZE_OF_CHARSET;

        bool printCharDirect(uint16_t x, int16_t y, uint8_t idx);
        void printChar(uint16_t x, int16_t y, uint32_t c);
        void setMargine(uint8_t side, uint8_t value);

};
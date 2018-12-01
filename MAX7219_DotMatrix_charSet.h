#include <avr/pgmspace.h>
#include <MAX7219_DotMatrix.h>


class MAX7219_DotMatrix_charSet : public MAX7219_DotMatrix{

    private:
        static const PROGMEM char charSet_A01[];

        // methods
        void direct(uint16_t x, int16_t y, uint8_t idx);

    public:

        // constructor
        MAX7219_DotMatrix_charSet(uint8_t pin_clk, uint8_t pin_cs, uint8_t pin_din, uint8_t mr, uint8_t mc);
        MAX7219_DotMatrix_charSet(uint8_t mr, uint8_t mc);
        ~MAX7219_DotMatrix_charSet();

        void setCharDirect(uint16_t x, int16_t y, uint8_t idx);



};
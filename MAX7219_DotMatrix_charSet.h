#ifndef MAX7219_DotMatrix_CharSet_H
#define MAX7219_DotMatrix_CharSet_H

#include <avr/pgmspace.h>
#include <MAX7219_DotMatrix.h>

#define DM_MARGINE_LEFT     0
#define DM_MARGINE_TOP      1
#define DM_MARGINE_BOTTOM   2
#define DM_MARGINE_RIGHT    3

class MAX7219_DotMatrix_charSet : public MAX7219_DotMatrix{

    private:
        static const PROGMEM uint8_t charSet_A01[];
        int8_t margin_left, margin_top, margin_bottom, margin_right;
        int16_t cursor_x, cursor_y;
        uint16_t scroll_wait_time;
        unsigned long scroll_timer;
        String scroll_string;
        int32_t scroll_point;
        uint16_t scroll_string_size;
        bool char_draw_mode, scroll_status, blink;
        uint16_t scroll_round_time, blink_interval;

        // methods
        bool direct(uint8_t idx);
        void updateScrollRoundTime();
        void init_charSet();

    public:
        // constructor
        MAX7219_DotMatrix_charSet(uint8_t pin_clk, uint8_t pin_cs, uint8_t pin_din, uint8_t mr, uint8_t mc);
        MAX7219_DotMatrix_charSet(uint8_t mr, uint8_t mc);
        ~MAX7219_DotMatrix_charSet();

        static const uint8_t SIZE_OF_CHARSET;

        bool printCharDirect(int16_t x, int16_t y, uint8_t idx);
        bool printCharDirect(uint8_t idx);
        void setMargine(uint8_t side, int16_t value);
        bool printChar(char c, int16_t x, int16_t y);
        bool printChar(char c);
        void printStr(String str, int16_t x, int16_t y);
        void printStr(String str);
        virtual void scroll(void);
        void scrollStop(void);
        void setScrollStr(String str);
        void setScrollStr(String str, uint16_t v, int16_t x, int16_t y);
        void setScrollStr(String str, uint16_t v);
        void setScrollSpeed(uint16_t v);
        void addScrollStr(String str);
        void setCharDrawMode(bool mode);
        void setBlink(bool mode);
        void setBlinkInterval(uint16_t interval);

};

#endif
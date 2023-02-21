#ifndef __DISPLAYDRIVER_H__
#define __DISPLAYDRIVER_H__

#include "../ev3dev.hpp"

enum LcdColor {
    LCD_WHITE   = 0,
    LCD_GREY    = 1,
    LCD_DARK    = 2,
    LCD_BLACK   = 3
};

class DisplayDriver {
    public:
        DisplayDriver();
        void drawPixel(int_fast8_t x, int_fast8_t y, LcdColor color);
    private:
        static ev3dev::lcd display;

        static char displayBuffer[];
};

#endif // __DISPLAYDRIVER_H__
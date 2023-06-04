#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "Screen.hpp"

class Window {
    private:
        unsigned char* _fbp;
        size_t _screensize;
        uint_fast8_t _width;
        uint_fast8_t _height;
        uint_fast8_t _bits_per_pixel;
        int fbfd;
    public:
        Window(uint_fast8_t x0, uint_fast8_t y0, uint_fast8_t x1, uint_fast8_t y1);
        ~Window();

        void clearScreen();
        void fillScreen(DisplayColors color);
        void drawPixel(uint_fast8_t xpos, uint_fast8_t ypos, DisplayColors color);
        
        void drawHLine(uint_fast8_t x0, uint_fast8_t y0, uint_fast8_t x1, uint_fast8_t y1, DisplayColors color);
        void drawHLine(uint_fast8_t x0, uint_fast8_t y0, uint_fast8_t length, DisplayColors color);

        void drawVLine(uint_fast8_t x0, uint_fast8_t y0, uint_fast8_t x1, uint_fast8_t y1, DisplayColors color);
        void drawVLine(uint_fast8_t x0, uint_fast8_t y0, uint_fast8_t length, DisplayColors color);
        
        void drawLine(uint_fast8_t x0, uint_fast8_t y0, uint_fast8_t x1, uint_fast8_t y1, DisplayColors color);

        void drawCircle(uint_fast8_t x0, uint_fast8_t y0, uint_fast16_t r, DisplayColors color);

        void drawRect(uint_fast8_t x0, uint_fast8_t y0, uint_fast8_t x1, uint_fast8_t y1, DisplayColors color); 
};

#endif // __WINDOW_H__
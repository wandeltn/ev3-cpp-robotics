#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "Screen.hpp"
#include <vector>

class Window {
    private:
        std::vector<unsigned char> frameBuffer;
        size_t _screensize;
        int fbfd;
    public:
        Window(uint_fast8_t x0, uint_fast8_t y0, uint_fast8_t x1, uint_fast8_t y1, bool border);
        ~Window();

        uint_fast8_t startX;
        uint_fast8_t startY;

        std::vector<unsigned char>& getFBP();
        uint_fast8_t getScreensize();
        uint_fast8_t width;
        uint_fast8_t height;
        uint_fast8_t bits_per_pixel;

        DisplayColors getPixel(uint_fast8_t x0, uint_fast8_t y0);

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
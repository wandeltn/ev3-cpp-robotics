#include <linux/fb.h>
#include <sys/mman.h>
#include <stdint.h>

#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__


enum DisplayColors {
    DISPLAY_BLACK = 0x00,
    DISPLAY_DARK = 0x78,
    DISPLAY_LIGHT = 0xb4,
    DISPLAY_WHITE = 0xff
};

class Display
{
private:
    int fbfd;
    unsigned char *fbp;
    fb_var_screeninfo vinfo;
    fb_fix_screeninfo finfo;
    size_t screensize = 0;

    uint_fast8_t width;
    uint_fast8_t height;
public:
    Display();
    ~Display();

    void clearScreen();
    void fillScreen(DisplayColors color);
    void drawPixel(uint_fast8_t xpos, uint_fast8_t ypos, DisplayColors color);
};

#endif
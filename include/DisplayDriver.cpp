#include "DisplayDriver.hpp"
#include <iostream>
#include <string.h>

DisplayDriver::DisplayDriver() {
    //while (!display.available()) {
    //    std::cout << "Display not available" << std::endl;
    //}
}

void DisplayDriver::drawPixel(int_fast8_t x, int_fast8_t y, LcdColor color)
{
    if (x > display.resolution_x() || y > display.resolution_y()) {
        std::cerr << "Pixel position out of range X: " << x << ", Y: " << y << std::endl;
    } else {
        std::cout << display.frame_buffer() << std::endl;
        std::cout << display.frame_buffer_size() << std::endl;
        std::cout << display.line_length() << std::endl;
        std::cout << display.bits_per_pixel() << std::endl;

        for (unsigned char* i = display.frame_buffer(); i <= display.frame_buffer() + display.frame_buffer_size(); i++) {
            *i = LCD_WHITE;
        }
        for(;;) {}
    }
}

ev3dev::lcd DisplayDriver::display = ev3dev::lcd();
char DisplayDriver::displayBuffer[] = {};

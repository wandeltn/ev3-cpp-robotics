#include "DirectRenderingManager.hpp"
#include <cstring>

Window* DirectRenderingManager::createWindow(uint_fast8_t x0, uint_fast8_t y0, uint_fast8_t x1, uint_fast8_t y1)
{
    Window* pWindow = new Window(x0, y0, x1, y1);
    _current_windows.push_back(pWindow);
    return pWindow;
}

void DirectRenderingManager::render()
{
    for(Window* window : _current_windows) {
        unsigned char* windowBuffer = window->getFBP();
        uint_fast8_t height = window->getHeight();
        for (uint_fast8_t posY = 0; posY <= height; posY++) {
            memcpy(fbp, windowBuffer + window->startX * 4, window->getWidth());
        }
    }
}

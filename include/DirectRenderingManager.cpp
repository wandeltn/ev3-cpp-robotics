#include "DirectRenderingManager.hpp"
#include <cstring>
#include <iostream>
#include <vector>
#include <math.h>

Window* DirectRenderingManager::createWindow(uint_fast8_t x0, uint_fast8_t y0, uint_fast8_t x1, uint_fast8_t y1)
{
    Window* pWindow = new Window(x0, y0, x1, y1);
    _current_windows.push_back(pWindow);
    return pWindow;
}

void DirectRenderingManager::render()
{
    for(Window* window : _current_windows) {
        std::vector<unsigned char> windowBuffer = window->getFBP();
        for (int index = 0; index <= windowBuffer.size(); index++) {
            for (int pixel = 0; pixel < 4; pixel++) {
                fbp[
                    static_cast<int>(
                        pixel
                        + (window->startX) * 4
                        + (floor(index / window->width)) * ((178 - (window->startX + window->width)) + window->startX)  * 4
                        //+ floor(index / window->width) * 178
                        + 178 * window->startY * 4
                        + index * 4
                    )
                ] = windowBuffer[index];
            }
        }
    }
}

std::vector<Window*> DirectRenderingManager::_current_windows = {};
#include "DirectRenderingManager.hpp"
#include <cstring>
#include <iostream>
#include <vector>
#include <math.h>

DirectRenderingManager::DirectRenderingManager()
{
    
}

std::shared_ptr<Window> DirectRenderingManager::createWindow(uint_fast8_t x0, uint_fast8_t y0, uint_fast8_t x1, uint_fast8_t y1, bool border)
{
    std::shared_ptr<Window> pWindow = std::make_shared<Window>(x0, y0, x1, y1, border);
    _current_windows.push_back(pWindow);
    return pWindow;
}

void DirectRenderingManager::registerWindow(std::shared_ptr<Window> window)
{
    _current_windows.push_back(window);
}



void DirectRenderingManager::pushToScreen()
{
    for(std::shared_ptr<Window> window : _current_windows) {
        pushToScreen(window);
    }
}

void DirectRenderingManager::pushToScreen(std::shared_ptr<Window> window)
{
    std::vector<uint32_t> windowBuffer = window->getFBP();
    for (size_t index = 0; index <= windowBuffer.size(); index++) {
        // for (int pixel = 0; pixel < 4; pixel++) {
            fbp[
                static_cast<int>(
                    // pixel +
                    (window->startX)
                    + (floor(index / window->width)) * ((178 - (window->startX + window->width)) + window->startX)
                    //+ floor(index / window->width) * 178
                    + 178 * window->startY
                    + index
                )
            ] = windowBuffer[index];
        // }
    }
}

std::vector<std::shared_ptr<Window>> DirectRenderingManager::_current_windows = {};

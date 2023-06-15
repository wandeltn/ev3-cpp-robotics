#ifndef __DIRECTRENDERINGMANAGER_H__
#define __DIRECTRENDERINGMANAGER_H__

#include "Screen.hpp"
#include "Window.hpp"
#include <vector>

class DirectRenderingManager: protected Screen {
    private:
        static std::vector<std::shared_ptr<Window>> _current_windows;
    public:
        static std::shared_ptr<Window> createWindow(uint_fast8_t x0, uint_fast8_t y0, uint_fast8_t x1, uint_fast8_t y1, bool border);
        void render();
        void clearWindows();
};

#endif
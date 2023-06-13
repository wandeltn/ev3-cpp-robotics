#ifndef __USERINTERFACE_H__
#define __USERINTERFACE_H__

#include "DirectRenderingManager.hpp"
#include "../ev3dev.hpp"
#include "Window.hpp"
#include <array>

#define USER_INTERFACE_X0   0
#define USER_INTERFACE_Y0   0
#define USER_INTERFACE_X1   178
#define USER_INTERFACE_Y1   28

extern DirectRenderingManager DRM;

class UserInterface {
    private:
        static Window* _window;

    public:
        UserInterface();
        void render();
        void update();
};

#endif // __USERINTERFACE_H__
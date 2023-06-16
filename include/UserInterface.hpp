#ifndef __USERINTERFACE_H__
#define __USERINTERFACE_H__

#include "DirectRenderingManager.hpp"
#include "../ev3dev.hpp"
#include "Window.hpp"
#include "Ports.hpp"
#include "ButtonNotifiable.hpp"
#include <array>


class UserInterface: private ButtonNotifiable {
    private:


    public:
        UserInterface();
        void render();
        void update();

        void onButtonBackPressed() override;
        void onButtonEnterPressed() override;
        void onButtonUpPressed() override;
        void onButtonDownPressed() override;
        void onButtonLeftPressed() override;
        void onButtonRightPressed() override;
};

#endif // __USERINTERFACE_H__
#ifndef __USERINTERFACE_H__
#define __USERINTERFACE_H__

#include "../ev3dev.hpp"
#include "DirectRenderingManager.hpp"
#include "Window.hpp"
#include "Ports.hpp"
#include "ButtonListener.hpp"
#include "Thread.hpp"
#include <array>


class UserInterface: private ButtonListener {
    private:
        static bool _button_listener_acitve;
        static uint_fast8_t _select_index;
        uint_fast8_t _select_index_max;
        static Thread _thread;

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
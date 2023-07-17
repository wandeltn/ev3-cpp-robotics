#ifndef __USERINTERFACE_H__
#define __USERINTERFACE_H__

#include "../../ev3dev.hpp"
#include "DirectRenderingManager.hpp"
#include "Window.hpp"
#include <array>


class UserInterface {
    private:
        static bool _button_listener_acitve;
        static uint_fast8_t _select_index;
        uint_fast8_t _select_index_max;


};

#endif // __USERINTERFACE_H__
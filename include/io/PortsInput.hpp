#ifndef __PORTSOUTPUT_H__
#define __PORTSOUTPUT_H__

#include "PortsInput.hpp"
#include "Ports.hpp"
#include "Rope.hpp"
#include "ButtonListener.hpp"

class PortsInput : private Ports {
    private:
        static Rope _rope; 
        static std::vector<std::shared_ptr<ButtonListener>> _button_listeners;
        static bool _button_thread_registered;

    public:
        PortsInput();

        static float getUSDistance();
        static float getReflect(DEVICE_SIDE side);
        static float getHeading();
        static void buttonCallback();
        static void registerButtonListener(std::shared_ptr<ButtonListener> listener);
};

#endif // __PORTSOUTPUT_H__
#ifndef __BUTTONNOTIFIER_H__
#define __BUTTONNOTIFIER_H__ 

#include <memory>
#include <vector>
#include <linux/input.h>
#include <fstream>
#include <stdexcept>
#include <string>
#include <iostream>
#include <linux/input-event-codes.h>
#include <mutex>

#define EVENT_PATH "/dev/input/by-path/platform-gpio_keys-event"

class ButtonNotifier {
    private:
        static std::ifstream _ifstream;
        static __u16 _previous_key;
        static std::mutex _mutex;
        static std::unique_ptr<ButtonNotifier> _pinstance;
        

        void Dispatcher();

    protected:
        ButtonNotifier();        

        virtual void onButtonBackPressed();
        virtual void onButtonEnterPressed();
        virtual void onButtonUpPressed();
        virtual void onButtonDownPressed();
        virtual void onButtonLeftPressed();
        virtual void onButtonRightPressed();

        virtual void onButtonBackReleased();
        virtual void onButtonEnterReleased();
        virtual void onButtonUpReleased();
        virtual void onButtonDownReleased();
        virtual void onButtonLeftReleased();
        virtual void onButtonRightReleased();

    public:
        ButtonNotifier(ButtonNotifier& other) = delete;
        void operator=(const ButtonNotifier&) = delete;

        static std::unique_ptr<ButtonNotifier>& GetInstance();
};

#endif
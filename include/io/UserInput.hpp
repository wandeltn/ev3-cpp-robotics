#ifndef __USERINPUT_H__
#define __USERINPUT_H__

#include <thread>
#include <vector>
#inc

class UserInput {
    private:
        static std::thread button_thread;
        static volatile std::vector<ev3dev::

    public:
        UserInput();

        static void PollButtons();
};

#endif // __USERINPUT_H__
#ifndef __USERINPUT_H__
#define __USERINPUT_H__

#include <thread>
#include <vector>
#include <functional>

class UserInput {
    private:
        static std::thread button_thread;
        
        static std::vector<std::function<void()>> button_listener_back;
        static std::vector<std::function<void()>> button_listener_enter;
        static std::vector<std::function<void()>> button_listener_up;
        static std::vector<std::function<void()>> button_listener_down;
        static std::vector<std::function<void()>> button_listener_left;
        static std::vector<std::function<void()>> button_listener_right;

    public:
        UserInput();

        static void PollButtons();
};

#endif // __USERINPUT_H__
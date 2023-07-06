#include "include/DirectRenderingManager.hpp"
#include "include/Window.hpp"
#include "include/Ports.hpp"

#include <thread>
#include <chrono>
#include <iostream>

#ifndef NO_LINUX_HEADERS
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#define KEY_RELEASE 0
#define KEY_PRESS   1
#define KEY_REPEAT  2
#endif

DirectRenderingManager DRM;

ev3dev::power_supply battery{""};

void test() {
    while(true) {
        std::cout << "2" << std::endl;
        usleep(500);
    }
}

int main() {
    std::thread thread_test = std::thread{&test};


    while (true){
        std::cout << "1" << std::endl;
        usleep(200);
    }
}
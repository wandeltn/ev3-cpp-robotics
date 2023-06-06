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
Ports::Input sensors;

int main() {



    while (true){
        std::cout << sensors.getHeading() << std::endl;
    }
}
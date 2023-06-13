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
Ports::Output motors;

int main() {
    std::cout << motors.rotateMotor() << std::endl;


    while (!sensors.getButtonBackPressed()){
        std::cout << sensors.getHeading() << std::endl;
        DRM.render();
    }
}
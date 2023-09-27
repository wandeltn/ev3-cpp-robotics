#include "include/Robot.hpp"

#include <thread>
#include <chrono>
#include <iostream>
#include <sys/inotify.h>

#define EV3DEV_PLATFORM_EV3

#ifndef NO_LINUX_HEADERS
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <signal.h>
#define KEY_RELEASE 0
#define KEY_PRESS   1
#define KEY_REPEAT  2
#endif
#ifdef EV3DEV_PLATFORM_EV3
    // LocationTracker lt{};
#else
#endif


Robot rt{};

void signal_callback(int signum) {
    std::cout << "Exiting..:" << signum << std::endl;
    rt.stopAll();
    rt.waitForFinish();
    exit(signum);
}


int main() {
    #ifdef EV3DEV_PLATFORM_EV3
    signal(SIGINT, signal_callback);

    rt.moveToPosition({400, 800});
    // rt.moveStraight(200);
    // rt.rotateTo(50);
    // rt.rotateTo(0);

    rt.waitForFinish();
    // rrt.generateTree();
    #endif
    using namespace std::chrono_literals;
    // while (true){

        
    // }
}
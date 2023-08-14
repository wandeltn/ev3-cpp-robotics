#include "include/display/DirectRenderingManager.hpp"
#include "include/display/Window.hpp"
#include "include/io/ButtonNotifier.hpp"
#include "include/positioning/Pathfind.hpp"
#include "include/positioning/AStar.hpp"
#include "include/positioning/RobotMovement.hpp"
#include "ev3dev.hpp"

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

RobotMovement rm{};

void signal_callback(int signum) {
    std::cout << "Exiting..." << std::endl;
    rm.stopAll();
    exit(signum);
}


int main() {
    #ifdef EV3DEV_PLATFORM_EV3
    signal(SIGINT, signal_callback);

    rm.goToLocation(MovementAction{300, 60, 300});
    // mc.rotateTo(50);

    // rrt.generateTree();
    #endif
    using namespace std::chrono_literals;
    // mc._sensors._run_thread.store(false);
    // mc._sensors._polling_thread.wait();
    while (true){

        // std::this_thread::sleep_for(100ms);
        // mc._sensors.Dispatcher();
    }
}
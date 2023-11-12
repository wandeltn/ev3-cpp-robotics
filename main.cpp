#include "include/Robot.hpp"
#include "include/http-server/Server.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <sys/inotify.h>


#ifndef NO_LINUX_HEADERS
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <signal.h>
#define KEY_RELEASE 0
#define KEY_PRESS   1
#define KEY_REPEAT  2
#endif


Robot rt{false};

void signal_callback(int signum) {
    std::cout << "Exiting..:" << signum << std::endl;
    rt.stopAll();
    exit(signum);
}

int main() {

    signal(SIGINT, signal_callback);
    std::cout << "Starting in main" << "\n";

    // rt.moveToPosition({400, 800});
    // rt.moveToPosition(Vector{65,200});
    rt.moveToPosition({200, 200});
    // rt.moveToPosition({200, 185});
    // rt.moveToPosition({65, 185});
    // rt.moveToPosition(50, 90);
    // rt.moveToPosition(50, 180);
    // rt.moveToPosition(50, 270);
    // rt.moveToPosition(50, 0);
    // rt.moveStraight(200);
    // rt.rotateTo(50);
    // rt.rotateTo(0);

    rt.finishQueue();
    // while (true) {
        // std::this_thread::sleep_for(std::chrono::seconds(3));
    // }
}
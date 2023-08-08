#include "include/display/DirectRenderingManager.hpp"
#include "include/display/Window.hpp"
#include "include/io/ButtonNotifier.hpp"
#include "include/positioning/Pathfind.hpp"
#include "include/positioning/AStar.hpp"
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
#define KEY_RELEASE 0
#define KEY_PRESS   1
#define KEY_REPEAT  2
#endif
#ifdef EV3DEV_PLATFORM_EV3
    DirectRenderingManager drm{};
#else
#endif


int main() {
    #ifdef EV3DEV_PLATFORM_EV3
    std::shared_ptr<Window> window = drm.createWindow(0, 0, 178, 128, true);
    Pathfind pf{window};
    std::vector<Vector> path = pf.findPath({10, 10}, {119, 119});
    for (Vector node : path) {
        std::cout << node << std::endl;
    }
    // rrt.generateTree();
    drm.pushToScreen();
    #endif
    
    sleep(10);
    // while (true){

    // }
}
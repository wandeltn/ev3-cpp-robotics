#include "include/display/DirectRenderingManager.hpp"
#include "include/display/Window.hpp"
#include "include/io/ButtonNotifier.hpp"
#include "include/positioning/Pathfind.hpp"
#include "include/positioning/Rrt.hpp"
#include "ev3dev.hpp"

#include <thread>
#include <chrono>
#include <iostream>
#include <sys/inotify.h>

#ifndef NO_LINUX_HEADERS
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#define KEY_RELEASE 0
#define KEY_PRESS   1
#define KEY_REPEAT  2
#endif

    // DirectRenderingManager drm{};

int main() {
    // std::shared_ptr<Window> window = drm.createWindow(0, 0, 178, 128, true);
    // Pathfind pf{window};
    // std::vector<Vector> path = pf.findPath({3, 8}, {120, 120});
    // for (Vector node : path) {
        // std::cout << node << std::endl;
    // }
    Rrt rrt{};
    rrt.generateTree();
    // drm.pushToScreen();
    
    sleep(10);
    // while (true){

    // }
}
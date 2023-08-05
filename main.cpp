#include "include/display/DirectRenderingManager.hpp"
#include "include/display/Window.hpp"
#include "include/io/ButtonNotifier.hpp"
#include "include/positioning/Pathfind.hpp"
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

    DirectRenderingManager drm{};

int main() {
    std::shared_ptr<Window> window = drm.createWindow(0, 0, 200, 100, true);
    // Pathfind pf{window};
    // pf.findPath({3, 8}, {48, 48});
    drm.pushToScreen();
    
    sleep(10);
    // while (true){

    // }
}
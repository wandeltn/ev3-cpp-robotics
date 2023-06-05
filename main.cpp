#include "./include/DirectRenderingManager.hpp"
#include "./include/Window.hpp"

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

int main() {
    Window* frame = DRM.createWindow(50, 50, 100, 100);

    frame->fillScreen(DISPLAY_BLACK);


    while (true){
        DRM.render();
    }
}
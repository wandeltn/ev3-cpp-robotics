#include "./include/Display.hpp"

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

Display lcdDisplay;

int main() {
    lcdDisplay.clearScreen();

    lcdDisplay.drawPixel(0, 0, DISPLAY_BLACK);
    lcdDisplay.drawPixel(178, 128, DISPLAY_BLACK);
    lcdDisplay.drawPixel(128, 178, DISPLAY_BLACK);

    printf("finished program execution\n");
    while (true){    }
}
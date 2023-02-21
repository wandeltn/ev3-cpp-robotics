#include "ev3dev.hpp"
#include "include/DriveControl.hpp"
#include "include/SensorControl.hpp"
#include "include/DisplayDriver.hpp"

#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>

#ifndef NO_LINUX_HEADERS
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#define KEY_RELEASE 0
#define KEY_PRESS   1
#define KEY_REPEAT  2
#endif

DriveControl motors;
SensorControl sensors;
DisplayDriver lcdDisplay;

int main() {
    //sensors.calibrateGyro();
    lcdDisplay.drawPixel(0, 0, LCD_WHITE);
    motors.driveStraight(720, motors.max_speed);
    motors.driveCurve(300, 3);
    motors.turnOnSpot(90, -1, 300);
    motors.driveStraight(-720, 500);

    return 0;
}
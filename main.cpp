#include "ev3dev.hpp"
#include "include/DriveControl.hpp"
#include "include/SensorControl.hpp"
#include "include/DisplayDriver.hpp"
#include "include/Pathfinder.hpp"
#include "include/Robot.hpp"

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

Robot robot;
SensorControl sensors;

int main() {
    sensors.calibrateGyro();
    //robot.moveToPosition(Vector2{1, 10});
    robot.driveStraight(500, robot.max_speed);
    robot.driveStraight(-500, 400);
    // for (;;) {
    //     std::cout << sensors.getGyroValue() << std::endl;
    // }

    return 0;
}
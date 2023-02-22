#include "ev3dev.hpp"
#include "include/DriveControl.hpp"
#include "include/SensorControl.hpp"
#include "include/DisplayDriver.hpp"
#include "include/Pathfinder.hpp"
#include "include/Robot.hpp"
#include "include/ToolControl.hpp"

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
ToolControl tools;

int main() {
    sensors.calibrateGyro();
    robot.resetMotors();
    //robot.moveToPosition(Vector2{1, 10});

    robot.moveToPosition(Vector2{20, 60});
    robot.moveToPosition(Vector2{(int_fast8_t)150, 60});
    robot.moveToPosition(Vector2{(int_fast8_t)150, 20});
    robot.moveToPosition(Vector2{20, 20});
    robot.turnToGyro(sensors, 0);

    // for (;;) {
    //     std::cout << sensors.getGyroValue() << std::endl;
    // }

    return 0;
}
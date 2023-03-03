#ifndef __DRIVECONTROL_HPP__
#define __DRIVECONTROL_HPP__

#include "../ev3dev.hpp"
#include "SensorControl.hpp"
#include "DriveAction.hpp"

class DriveControl {
    public:
        DriveControl();
        void resetMotors();
        void driveStraight(int distance, int speed);
        void driveToLine(SensorControl& sensors, int distance_estimate, int speed);
        void driveOverLines(SensorControl& sensors, std::vector<int> lines, int speed);
        void driveCurve(int speed, int curve);
        void turnOnSpot(int distance, int direction, int speed);
        void turnToGyro(SensorControl& sensors, int targetAngle);
        void lineFollow(int distance);

        static int max_speed;

    protected:
        static int rot_to_steps;
        void waitForMotorIdle();

    private:
        static ev3dev::large_motor _motor_left;
        static ev3dev::large_motor _motor_right;
};

#endif
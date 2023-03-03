#include "DriveControl.hpp"
#include <stdio.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include "../ev3dev.hpp"

#define BLACK_LINE_REFLECT  30

DriveControl::DriveControl()
{
    //max_speed = _motor_left.max_speed();
    //cm_to_rot = _motor_left.count_per_rot();
}

void DriveControl::resetMotors()
{
    _motor_left.reset();
    _motor_right.reset();
}

/// @brief
/// Drive staight to the desired location. This funtion blocks the thread until the 
/// motors are in idle mode. As this happens the motors start and the code continues.
/// @param distance The distance to drive
/// @param speed The speed in which to drive
void DriveControl::driveStraight(int distance, int speed)
{
    _motor_left.set_stop_action("hold");
    _motor_right.set_stop_action("hold");
    //wait until the motors are finished moving before next move
    waitForMotorIdle();

    //register distance to travel
    _motor_left.set_position_sp(_motor_left.position_sp() + distance);
    _motor_right.set_position_sp(_motor_right.position_sp() + distance);

    //set time to ramp down -> may improve accuracy
    //_motor_left.set_ramp_down_sp(1500);
    //_motor_right.set_ramp_down_sp(1500);

    //set speed and start moving
    _motor_left.set_speed_sp(speed).run_to_abs_pos();
    _motor_right.set_speed_sp(speed).run_to_abs_pos();
}

void DriveControl::driveToLine(SensorControl& sensors, int distance_estimate, int speed)
{
    //set action to coast for non stop drive to line
    _motor_right.set_stop_action("coast");
    _motor_left.set_stop_action("coast");

    waitForMotorIdle();

    //set distance to 80% of distance for later slow approach
    _motor_left.set_position_sp(_motor_left.position_sp() + distance_estimate * 0.8);
    _motor_right.set_position_sp(_motor_right.position_sp() + distance_estimate * 0.8);

    //drive to line at set speed
    _motor_left.set_speed_sp(speed).run_to_abs_pos();
    _motor_right.set_speed_sp(speed).run_to_abs_pos();
    
    //slow approach to line
    _motor_left.set_speed_sp(200).run_forever();
    _motor_right.set_speed_sp(200).run_forever();

    //reset stop action to hold
    _motor_left.set_stop_action("hold");
    _motor_right.set_stop_action("hold");

    //wait for black line
    while(sensors.getColorLeftReflect() >= BLACK_LINE_REFLECT) {}

    _motor_left.stop();
    _motor_right.stop();
}

void DriveControl::driveOverLines(SensorControl& sensors, std::vector<int> distances, int speed)
{
    for(int index = 0; index <= distances.size(); index++) {
        if (index = distances.size() -1) {
            driveStraight(distances[index], speed);
        } else {
            driveToLine(sensors, distances[index], speed);
        }
    }
}


void DriveControl::driveCurve(int speed, int curve)
{
    std::cerr << "DriveControl::driveCurve is not implemented" << std::endl;
}


/// @brief Rotate both motors is opposite rotaition distances to result in turn which is whithout any forward movement.
/// @param speed Speed at which the motors are supposed to turn
/// @param rotation Distance to rotate
/// @param direction Values should be 1 or -1 beacause the rotation ist multiplied to result in turn
void DriveControl::turnOnSpot(int rotation, int direction, int speed)
{
    //wait until motors are finished with previous move before next move
    waitForMotorIdle();

    std::cout << "turning without gyro assistance" << std::endl;
    //set distance to rotate motors
    _motor_left.set_position_sp(_motor_left.position_sp() + rotation * direction);
    _motor_right.set_position_sp(_motor_right.position_sp() + -rotation * direction);

    // set speed to rotate and start moving
    _motor_left.set_speed_sp(speed).run_to_abs_pos();
    _motor_right.set_speed_sp(speed).run_to_abs_pos();
}

void DriveControl::turnToGyro(SensorControl& sensors, int targetAngle)
{
    waitForMotorIdle();

    _motor_left.set_stop_action("hold");
    _motor_right.set_stop_action("hold");
    
    if (targetAngle > sensors.getGyroValue()) {
        _motor_left.set_speed_sp(100);
        _motor_right.set_speed_sp(-100);
    } else {
        _motor_left.set_speed_sp(-100);
        _motor_right.set_speed_sp(100);
    }
    _motor_left.run_forever();
    _motor_right.run_forever();

    while (sensors.getGyroValue() != targetAngle) {
        std::cout << sensors.getGyroValue() << std::endl;
    }
    _motor_left.stop();
    _motor_right.stop();
}

void DriveControl::lineFollow(int distance)
{
    //while (_motor_left.position_sp())
    //_motor_left.run_direct();
}

void DriveControl::waitForMotorIdle()
{
    while (_motor_right.state().count("running") >= 1 ||
            _motor_left.state().count("running") >= 1) {}
}


int DriveControl::max_speed = 800;
int DriveControl::rot_to_steps = 360;
ev3dev::large_motor DriveControl::_motor_left = ev3dev::large_motor(ev3dev::OUTPUT_A);
ev3dev::large_motor DriveControl::_motor_right = ev3dev::large_motor(ev3dev::OUTPUT_B);
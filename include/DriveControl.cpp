#include "DriveControl.hpp"
#include <stdio.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include "../ev3dev.hpp"

DriveControl::DriveControl()
{
    //max_speed = _motor_left.max_speed();
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
    while (_motor_right.state().count("running") >= 1 &&
            _motor_left.state().count("running") >= 1) {
        std::cout << _motor_left.position_sp() << std::endl;
    }
    //register distance to travel
    _motor_left.set_position_sp(_motor_left.position_sp() + distance);
    _motor_right.set_position_sp(_motor_right.position_sp() + distance);

    //set time to ramp down -> may improve accuracy
    //_motor_left.set_ramp_down_sp(1500);
    //_motor_right.set_ramp_down_sp(1500);

    //set speed and start moving
    _motor_left.set_speed_sp(speed).run_to_abs_pos();
    _motor_right.set_speed_sp(speed).run_to_abs_pos();


    while (_motor_right.state().count("running") >= 1 &&
            _motor_left.state().count("running") >= 1) {
        std::cout << _motor_left.stop_action() << std::endl;
    }

    for (std::string action : _motor_right.stop_actions()) {
        std::cout << action << std::endl;
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
    while (_motor_right.state().count("running") >= 1 &&
            _motor_left.state().count("running") >= 1) {
        std::cout << _motor_left.position() << std::endl;
    }

    std::cout << "turning without gyro assistance" << std::endl;
    //set distance to rotate motors
    _motor_left.set_position_sp(_motor_left.position_sp() + rotation * direction);
    _motor_right.set_position_sp(_motor_right.position_sp() + -rotation * direction);

    // set speed to rotate and start moving
    _motor_left.set_speed_sp(speed).run_to_abs_pos();
    _motor_right.set_speed_sp(speed).run_to_abs_pos();
}

void DriveControl::lineFollow(int distance)
{
    //while (_motor_left.position_sp())
    //_motor_left.run_direct();
}


int DriveControl::max_speed = 800;
ev3dev::large_motor DriveControl::_motor_left = ev3dev::large_motor(ev3dev::OUTPUT_A);
ev3dev::large_motor DriveControl::_motor_right = ev3dev::large_motor(ev3dev::OUTPUT_B);
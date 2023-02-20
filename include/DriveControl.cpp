#include "DriveControl.hpp"
#include <stdio.h>
#include <iostream>

DriveControl::DriveControl()
{
    //max_speed = _motor_left.max_speed();
}

void DriveControl::resetMotors()
{
    _motor_left.reset();
    _motor_right.reset();
}

void DriveControl::driveStraight(int distance, int speed)
{
    _motor_left.set_position_sp(_motor_left.position_sp() + distance);
    _motor_right.set_position_sp(_motor_right.position_sp() + distance);

    _motor_left.set_speed_sp(speed).run_to_abs_pos();
    _motor_right.set_speed_sp(speed).run_to_abs_pos();
}

void DriveControl::driveCurve(int speed, int curve)
{
    
}

void DriveControl::turnOnSpot(int speed, int rotation)
{
    
}

int DriveControl::max_speed = 800;
ev3dev::large_motor DriveControl::_motor_left = ev3dev::large_motor(ev3dev::OUTPUT_A);
ev3dev::large_motor DriveControl::_motor_right = ev3dev::large_motor(ev3dev::OUTPUT_B);
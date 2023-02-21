#include "Robot.cpp"
#include <chrono>
#include <iostream>
#include <cmath>

#define START_POSITION_X 20
#define START_POSITION_Y 20
#define START_HEADING 90
#define PI 3.14159265

Robot::Robot()
{
}

void Robot::moveToPosition(Vector2 destination)
{
    double targetAngle = atan((_current_position.x - destination.x) / (_current_position.y - destination.y)) * 180 / PI;
    
}

SensorControl Robot::sensors = SensorControl{};
Vector2 Robot::_current_position = Vector2{START_POSITION_X, START_POSITION_Y};
int_fast8_t Robot::_current_heading = START_HEADING;
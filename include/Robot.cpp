#include "Robot.hpp"
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
    double targetAngle = atan2(_current_position.y - destination.y, _current_position.x - destination.x) * 180 / PI;
    int distance = std::round(_current_position.getDistanceToPoint(destination));

    std::cout << "targetAngle: " << targetAngle + _current_heading << " distance: " << distance / 17.6 * 360 << std::endl;
    turnToGyro(sensors, (int)std::round(targetAngle));
    driveStraight(distance / 17.6 * rot_to_steps, 500);

    _current_position = destination;
    _current_heading += targetAngle;
}

void Robot::moveToPosition(double x, double y)
{
    moveToPosition(Vector2{x, y});
}

SensorControl Robot::sensors = SensorControl{};
LineIntersect Robot::intersections = LineIntersect{};
Vector2 Robot::_current_position = Vector2{START_POSITION_X, START_POSITION_Y};
int_fast8_t Robot::_current_heading = START_HEADING;

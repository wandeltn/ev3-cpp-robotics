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
    LineType travelLine{_current_position, destination};
    std::vector<Vector2> intersect_points = intersections.checkForIntersects(travelLine);
    std::vector<int> drive_distances;


    for(int vector_index = 0; vector_index <= intersect_points.size(); vector_index++) {
        if (vector_index != 0) {
            drive_distances.push_back(intersect_points[vector_index].getDistanceToPoint(intersect_points[vector_index-1]));
        } else {
            drive_distances.push_back(intersect_points[vector_index].getDistanceToPoint(_current_position));
        }
    }
    //calculate movement parameters
    double targetAngle = atan2(_current_position.y - destination.y, _current_position.x - destination.x) * 180 / PI;
    int distance = std::round(_current_position.getDistanceToPoint(destination));

    //output parameters and move to determined position
    std::cout << "targetAngle: " << targetAngle + _current_heading << " distance: " << distance / 17.6 * 360 << std::endl;
    turnToGyro(sensors, (int)std::round(targetAngle));
    driveStraight(distance / 17.6 * rot_to_steps, 500);


    //set virtual position to new position
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

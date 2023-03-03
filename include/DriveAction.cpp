#include "DriveAction.hpp"
#include <iostream>
#include <cmath>

DriveAction::DriveAction()
{
    std::cerr << "using DriveAction default constructor";
}

DriveAction::DriveAction(int distance, int targetAngle)
{
    _distance = distance;
    _targetAngle = targetAngle;
}

DriveAction::DriveAction(float distance, int targetAngle)
{
    _distance = round(distance);
    _targetAngle = targetAngle;
}

DriveAction::DriveAction(int distance, float targetAngle)
{
    _distance = distance;
    _targetAngle = round(targetAngle);
}

DriveAction::DriveAction(float distance, float targetAngle)
{
    _distance = round(distance);
    _targetAngle = round(targetAngle);
}

int DriveAction::getDistance()
{
    return _distance;
}

int DriveAction::getTargetAngle()
{
    return _targetAngle;
}



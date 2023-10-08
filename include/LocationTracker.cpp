#include "LocationTracker.hpp"

MovementAction::MovementAction(int distance, int direction, int speed)
{
    this->distance = distance;
    this->direction = direction;
    this->speed = speed;
}

MovementAction::MovementAction(Line line, int speed)
{
    this->distance = line.getLength();
    direction = line.getAngle();
    this->speed = speed;

    std::cout << this->direction << std::endl;
}

MovementAction::MovementAction()
{
}

std::deque<MovementAction> LocationTracker::_pendingActions{};
SensorNotifier LocationTracker::_notifier{};
LineManager LocationTracker::_lineManager{};
Vector LocationTracker::_position{65,185};
Vector LocationTracker::_prevPixel = {1,1};
int LocationTracker::_heading_gyro = 0;
double LocationTracker::_heading_motor = 0;



LocationTracker::LocationTracker()
{
    _notifier.subscribeToAllChanges(LocationTracker::updateLocation);
}

LocationTracker::LocationTracker(int startX, int startY)
{
    _position.x = startX;
    _position.y = startY;
    _notifier.subscribeToAllChanges(LocationTracker::updateLocation);
}

void LocationTracker::updateLocation(std::map<subscriber_port, int> sensor_values, std::map<subscriber_port, int> prev_values)
{

    _heading_gyro = abs(sensor_values[sensor_gyro]) % 360;
    if (_heading_gyro < 0) {
        _heading_gyro += 360;
    }


    double movedPulses = ((sensor_values[motor_drive_right] - prev_values[motor_drive_right]) + (sensor_values[motor_drive_left] - prev_values[motor_drive_left])) / 2;
    _position.x += (cos(_heading_gyro * (180 / M_PI))) * motorPulsesToMm(movedPulses);
    _position.y += (sin(_heading_gyro * (180 / M_PI))) * motorPulsesToMm(movedPulses);
    // std::cout << _position << std::endl;
    // std::cout << "moved pulses: " << movedPulses << std::endl;

    if (state == MOVEMENT_TURNING) {
        double turned_angle_right = (motorPulsesToMm(sensor_values[motor_drive_right] - prev_values[motor_drive_right]) / (M_PI * VEHICLE_WIDTH_MM)) * 360;
        double turned_angle_left = (motorPulsesToMm(sensor_values[motor_drive_left] - prev_values[motor_drive_left]) / (M_PI * VEHICLE_WIDTH_MM)) * 360;
        std::cout << "estimated turned_angle_right: " << turned_angle_right << "\n";
        std::cout << "estimated turned_angle_left: " << turned_angle_left << "\n";

        _heading_motor += ((turned_angle_left * -1) + turned_angle_right) / 2;

        std::cout << "LocationTracker::_heading_motor: " << _heading_motor << "\n";
    }
}

const Vector LocationTracker::getLocation()
{
    return _position;
}

int LocationTracker::getHeading()
{
    return _heading_gyro;
}
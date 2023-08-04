#include "LocationTracker.hpp"

SensorNotifier LocationTracker::_notifier;

float LocationTracker::_position_x = 0;
float LocationTracker::_position_y = 0;
int LocationTracker::_heading = 0;



LocationTracker::LocationTracker()
{
    _notifier.subscribeToChange(updateLocation);
}

LocationTracker::LocationTracker(int startX, int startY)
{
    _position_x = startX;
    _position_y = startY;
}

void LocationTracker::updateLocation(std::map<subscriber_port&, int> sensor_values)
{
    int motor_difference = sensor_values[motor_drive_left] - sensor_values[motor_drive_left];
    if (motor_difference <= -10 || motor_difference >= 10) {
        std::cerr << "large motor unsynchronization: " << motor_difference << std::endl;    
    }

    float moved_pulses = (sensor_values[motor_drive_left] + sensor_values[motor_drive_right]) / 2;
    _heading += sensor_values[sensor_gyro];

    _position_x += MotorPulsesToInt(moved_pulses * cos(_heading));
    _position_y += MotorPulsesToInt(moved_pulses * sin(_heading));
}

const Point LocationTracker::getLocation()
{
    return Point();
}

float LocationTracker::MotorPulsesToInt(float pulses)
{
    return ((static_cast<float>(pulses) / 360.0f) + 15.6f);
}
#include "LocationTracker.hpp"

SensorNotifier LocationTracker::_notifier;

Vector LocationTracker::_position{2,2};
int LocationTracker::_heading = 0;
Vector LocationTracker::_previousMotorPulses = {0,0};



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

void LocationTracker::updateLocation(std::map<subscriber_port, int> sensor_values)
{
    
    // double moved_pulses = ((sensor_values[motor_drive_left] - _previousMotorPulses.x) + (sensor_values[motor_drive_right] - _previousMotorPulses.y)) / 2;
    // _heading += sensor_values[sensor_gyro];

    // _position.x += MotorPulsesToInt(moved_pulses * cos(_heading));
    // _position.y += MotorPulsesToInt(moved_pulses * sin(_heading));

    // _previousMotorPulses.x = sensor_values[motor_drive_left];
    // _previousMotorPulses.y = sensor_values[motor_drive_right];
}

const Vector LocationTracker::getLocation()
{
    return _position;
}

int LocationTracker::getHeading()
{
    return _heading;
}

double LocationTracker::MotorPulsesToInt(double pulses)
{
    return ((static_cast<double>(pulses) / 360.0) * 15.6);
}
#include "LocationTracker.hpp"

SensorNotifier LocationTracker::_notifier;

double LocationTracker::_position_x = 0;
double LocationTracker::_position_y = 0;
int LocationTracker::_heading = 0;



LocationTracker::LocationTracker()
{
    _notifier.subscribeToAllChanges(LocationTracker::updateLocation);
}

LocationTracker::LocationTracker(int startX, int startY)
{
    _position_x = startX;
    _position_y = startY;
    _notifier.subscribeToAllChanges(LocationTracker::updateLocation);
}

void LocationTracker::updateLocation(std::map<subscriber_port, int> sensor_values)
{
    int motor_difference = sensor_values[DeviceCommunicator::motor_drive_left] - sensor_values[output_A];
    if (motor_difference <= -10 || motor_difference >= 10) {
        std::cerr << "large motor unsynchronization: " << motor_difference << std::endl;    
    }

    double moved_pulses = (sensor_values[motor_drive_left] + sensor_values[motor_drive_right]) / 2;
    _heading += sensor_values[sensor_gyro];

    _position_x += MotorPulsesToInt(moved_pulses * cos(_heading));
    _position_y += MotorPulsesToInt(moved_pulses * sin(_heading));
}

const Point LocationTracker::getLocation()
{
    return Point();
}

int LocationTracker::getHeading()
{
    return _heading;
}

double LocationTracker::MotorPulsesToInt(double pulses)
{
    return ((static_cast<double>(pulses) / 360.0) * 15.6);
}
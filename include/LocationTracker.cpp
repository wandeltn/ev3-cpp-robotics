#include "LocationTracker.hpp"

SensorNotifier LocationTracker::_notifier;

int LocationTracker::_position_x = 0;
int LocationTracker::_position_y = 0;
int LocationTracker::_heading = 0;



LocationTracker::LocationTracker()
{
    
}

LocationTracker::LocationTracker(int startX, int startY)
{
    _position_x = startX;
    _position_y = startY;
}

void LocationTracker::updateLocation(std::map<subscriber_port&, int> sensor_values)
{
    int motor_difference = sensor_values[_notifier.motor_drive_right] - sensor_values[_notifier.motor_drive_left];

    if (motor_difference <= -10 || motor_difference >= 10) {std::cerr << "large motor unsynchronization: " << motor_difference << std::endl;}

    if (sensor_values[_notifier.sensor_gyro] != _heading) {
        
    }
}
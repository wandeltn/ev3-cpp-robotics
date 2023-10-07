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
int LocationTracker::_heading = 0;



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

    _heading = abs(sensor_values[sensor_gyro]) % 360;
    if (_heading < 0) {
        _heading += 360;
    }


    double movedPulses = ((sensor_values[motor_drive_right] - prev_values[motor_drive_right]) + (sensor_values[motor_drive_left] - prev_values[motor_drive_left])) / 2;
    _position.x += (cos(_heading * (180 / M_PI))) * motorPulsesToMm(movedPulses);
    _position.y += (sin(_heading * (180 / M_PI))) * motorPulsesToMm(movedPulses);
    // std::cout << _position << std::endl;
    // std::cout << "moved pulses: " << movedPulses << std::endl;

    
    switch (state)
    {
        case MOVEMENT_IDLE:
    //     if (
    //         _previousValues[motor_drive_left] != sensor_values[motor_drive_left] ||
    //         _previousValues[motor_drive_right] != sensor_values[motor_drive_right] ||
    //         _previousValues[sensor_gyro] != sensor_values[sensor_gyro]
    //         ) {
    //             std::cout << "motor right: prev:" << _previousValues[motor_drive_right] << " now:" << sensor_values[motor_drive_right] << std::endl;
    //             std::cout << "motor left: prev:" << _previousValues[motor_drive_left] << " now:" << sensor_values[motor_drive_left] << std::endl;
    //             std::cout << "gyro: prev:" << _previousValues[sensor_gyro] << " now:" << sensor_values[sensor_gyro] << std::endl;
    //             std::cerr << "WARN: Robot moving without command" << std::endl;
    //         }
            break;

        case MOVEMENT_MOVING: {
            break;
        }

        case MOVEMENT_TURNING:
    // //     _heading = sensor_values[sensor_gyro] % 360;
    // //     if (_heading < 0) {
    // //         _heading += 360;
    // //     }
            break;
    
        default:
            // std::cerr << "ERR: state not matchable" << state << std::endl;
            break;
    }
}

const Vector LocationTracker::getLocation()
{
    return _position;
}

int LocationTracker::getHeading()
{
    return _heading;
}
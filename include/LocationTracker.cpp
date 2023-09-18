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
Vector LocationTracker::_position{2,2};
int LocationTracker::_heading = 0;
std::map<std::string, int> LocationTracker::_previousValues = {};
bool LocationTracker::_initialized = false;



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
    // _previousValues = sensor_values;
    // if (!_initialized) {
    //     for (auto value : sensor_values) {
    //         _previousValues[value.first] = value.second;
    //     }
    //     _initialized = true;
    // }

    _heading = sensor_values[sensor_gyro] % 360;
    if (_heading < 0) {
        _heading += 360;
    }

    // switch (state)
    // {
    // case MOVEMENT_IDLE:
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
    //     break;

    // // case MOVEMENT_MOVING: {
    // //     double movedPulses = (sensor_values[motor_drive_right] - _previousValues[motor_drive_right] + sensor_values[motor_drive_left] - _previousValues[motor_drive_left]) / 2;

    // //     _position.x += (cos(_heading * (M_PI / 180))) * motorPulsesToMm(movedPulses);
    // //     _position.y += (sin(_heading * (M_PI / 180))) * motorPulsesToMm(movedPulses);
    // //     break;
    // // }

    // // case MOVEMENT_TURNING:
    // //     _heading = sensor_values[sensor_gyro] % 360;
    // //     if (_heading < 0) {
    // //         _heading += 360;
    // //     }
    // //     break;
    
    // default:
    //     std::cerr << "ERR: state not matchable" << state << std::endl;
    //     break;
    // }
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
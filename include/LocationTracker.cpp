#include "LocationTracker.hpp"

MovementAction::MovementAction(int distance, int direction, int speed)
{
    this->distance = distance;
    this->direction = direction;
    this->speed = speed;
}

MovementAction::MovementAction(Line line, int speed)
{
    std::cout << "MovementAction::line" << line.end_point << "\n";
    this->distance = sqrt(pow(line.end_point.x - LocationTracker::getLocation().x, 2) + pow(line.end_point.y - LocationTracker::getLocation().y, 2));
    std::cout << "this->distance: " << this->distance << "\n"; 
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
PolyFit LocationTracker::_polyfit{};
Vector LocationTracker::_position{65,185};
Vector LocationTracker::_positionByCommand{65, 185};
Vector LocationTracker::_prevPixel = {1,1};
std::deque<std::map<std::string, int>> LocationTracker::_cachedValues{};
int LocationTracker::_heading_gyro = 0;
double LocationTracker::_heading_motor = 0;

int LocationTracker::prevPulses = 0;
bool LocationTracker::_firstCall = true;
int LocationTracker::_colorSensorTriggerValue = 20;


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
    if (!_firstCall) {       
        if (prevPulses == 0) {
            prevPulses = sensor_values[motor_drive_left];
        }


        _heading_gyro = abs(sensor_values[sensor_gyro]) % 360;
        if (_heading_gyro < 0) {
            _heading_gyro += 360;
        }


        double movedPulses = ((sensor_values[motor_drive_right] - prev_values[motor_drive_right]) + (sensor_values[motor_drive_left] - prev_values[motor_drive_left])) / 2;
        if (movedPulses <= 100) {
            _position.x += (cos(_heading_gyro * (M_PI / 180))) * motorPulsesToMm(movedPulses);
            _position.y -= (sin(_heading_gyro * (M_PI / 180))) * motorPulsesToMm(movedPulses);
            // std::cout << _position << std::endl;
            // std::cout << "moved pulses: " << movedPulses << std::endl;
        } else {
            std::cout << "W: skipped position update, robot moving to fast: " << movedPulses << "\n";
        }

        if (state == MOVEMENT_TURNING) {
            double turned_angle_right = (motorPulsesToMm(sensor_values[motor_drive_right] - prev_values[motor_drive_right]) / (M_PI * VEHICLE_WIDTH_MM)) * 360;
            double turned_angle_left = (motorPulsesToMm(sensor_values[motor_drive_left] - prev_values[motor_drive_left]) / (M_PI * VEHICLE_WIDTH_MM)) * 360;
            // std::cout << "estimated turned_angle_right: " << turned_angle_right << "\n";
            // std::cout << "estimated turned_angle_left: " << turned_angle_left << "\n";

            _heading_motor += ((turned_angle_left * -1) + turned_angle_right) / 2;
            
            if (_heading_motor < 0) {
                _heading_motor += 360;
            } else if (_heading_motor >= 360) {
                _heading_motor -= 360;
            }

            // std::cout << "LocationTracker::_heading_motor: " << _heading_motor << "\n";
            // std::cout << "Absolute motor angle calculation: " << (motorPulsesToMm(sensor_values[motor_drive_left] - prevPulses) / (M_PI * VEHICLE_WIDTH_MM)) * 360 << "\n";
        }

        AddValuesToCache(sensor_values);

        // check for line under left color sensor
        if (sensor_values[sensor_color_left] <= _colorSensorTriggerValue) {
            
        }
        if (sensor_values[sensor_color_right] <= _colorSensorTriggerValue) {
            
        }

        
    } else {
        _firstCall = false;
    }
}

const Vector LocationTracker::getLocation()
{
    return _position;
}

int LocationTracker::getHeading()
{
    std::cout << _heading_motor << "\n";
    return _heading_gyro;
}

void LocationTracker::sendForwardMovementUpdate(uint distanceInPulses)
{
    _positionByCommand.x -= (cos(_heading_gyro * (M_PI / 180))) * motorPulsesToMm(distanceInPulses);
    _positionByCommand.y -= (sin(_heading_gyro * (M_PI / 180))) * motorPulsesToMm(distanceInPulses);

    std::cout << "Position By Command: " << _positionByCommand << "\n";
}

void LocationTracker::AddValuesToCache(std::map<std::string, int> values)
{
    _cachedValues.push_back(values);

    if (_cachedValues.size() > COLOR_SENSOR_CACHE_SIZE) {
        _cachedValues.pop_front();
    }
}

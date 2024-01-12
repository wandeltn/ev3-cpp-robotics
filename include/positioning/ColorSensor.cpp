#include "ColorSensor.hpp"

LineManager ColorSensor::_lines{};
Vector ColorSensor::_nextIntersect = NULL;

ColorSensor::ColorSensor()
{
}

ColorSensor::~ColorSensor()
{
}

void ColorSensor::notifyLineFound(std::string port, double heading, Vector position, Line currentTrip, double *out_ang, Vector *out_vector)
{
    std::vector<Vector> intersects = _lines.getIntersect(currentTrip);
    Vector nearestIntersect;
    Vector sensorPos = position;
    double relSensorAng;
    
    if (port == DeviceCommunicator::sensor_color_left) {
        relSensorAng = currentTrip.getAngle() + SENSOR_COLOR_ANGLE;
    } else {
        relSensorAng = currentTrip.getAngle() - SENSOR_COLOR_ANGLE;
    }
    sensorPos.moveDistanceInDirection(relSensorAng, SENSOR_COLOR_DISTANCE);

    if (intersects.size()) {
        double nearestDist = std::numeric_limits<double>::infinity();
        for (const Vector& point : intersects) {
            double dist = sensorPos.getDistanceTo(point);
            if (nearestDist > dist) {
                nearestIntersect = point;
                nearestDist = dist;
            }
        }

        if (_nextIntersect == NULL) {
            _nextIntersect = position;
            if (port == DeviceCommunicator::sensor_color_left) {
                _nextIntersect.moveDistanceInDirection(currentTrip.getAngle() - SENSOR_COLOR_ANGLE, SENSOR_COLOR_DISTANCE);
            } else {
                _nextIntersect.moveDistanceInDirection(currentTrip.getAngle() + SENSOR_COLOR_ANGLE, SENSOR_COLOR_DISTANCE);
            }
        } else {
            *out_vector = _nextIntersect;
            *out_ang = Line{nearestIntersect, _nextIntersect}.getAngle();
        }
    }

}

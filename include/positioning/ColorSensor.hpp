#ifndef __COLORSENSOR_H__
#define __COLORSENSOR_H__

#include <string>
#include "Line.hpp"
#include "LineManager.hpp"
#include "../io/DeviceCommunicator.hpp"

#define SENSOR_COLOR_ANGLE      60
#define SENSOR_COLOR_DISTANCE   50

class ColorSensor {
    public:
        ColorSensor();
        ~ColorSensor();

        static void notifyLineFound(std::string port, double heading, Vector position, Line currentTrip, double* out_ang, Vector* out_vector);

    private:
        static LineManager _lines;
        static Vector _nextIntersect;
};

#endif
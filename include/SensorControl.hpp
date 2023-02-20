#ifndef __SENSORCONTROL_H__
#define __SENSORCONTROL_H__

#include "../ev3dev.hpp"

class SensorControl {
    public:
        SensorControl();
        void calibrateGyro();
        int getGyroValue();
        int getColorLeftReflect();
        int getColorRightReflect();
    
    protected:
        static ev3dev::gyro_sensor  _gyro_sensor;
        static ev3dev::color_sensor _color_right;
        static ev3dev::color_sensor _color_left;
};

#endif // __SENSORCONTROL_H__
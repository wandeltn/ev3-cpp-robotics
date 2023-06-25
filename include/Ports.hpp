#ifndef __PORTS_H__
#define __PORTS_H__

#include "../ev3dev.hpp"

enum DEVICE_SIDE {
    DEVICE_RIGHT = 0,
    DEVICE_LEFT = 1
};

class Ports {
    protected:
        static ev3dev::color_sensor _color_sensor_left;
        static ev3dev::color_sensor _color_sensor_right;
        static ev3dev::ultrasonic_sensor _distance_sensor;
        static ev3dev::gyro_sensor _gyro_sensor;
        
        static ev3dev::button _button_up;
        static ev3dev::button _button_down;
        static ev3dev::button _button_left;
        static ev3dev::button _button_right;
        static ev3dev::button _button_enter;
        static ev3dev::button _button_back;

        static ev3dev::large_motor _motor_left;

    public:
        Ports();
};

#endif // __PORTS_H__
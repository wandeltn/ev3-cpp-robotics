#include "SensorControl.hpp"

SensorControl::SensorControl()
{
    _gyro_sensor.
}


ev3dev::gyro_sensor SensorControl::_gyro_sensor = ev3dev::gyro_sensor(ev3dev::INPUT_1);
ev3dev::color_sensor SensorControl::_color_left = ev3dev::color_sensor(ev3dev::INPUT_2);
ev3dev::color_sensor SensorControl::_color_right = ev3dev::color_sensor(ev3dev::INPUT_3);

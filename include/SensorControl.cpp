#include "SensorControl.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <unistd.h>

SensorControl::SensorControl()
{
    
}

void SensorControl::calibrateGyro()
{
    _gyro_sensor.set_mode("GYRO-CAL");
}

int SensorControl::getGyroValue()
{
    return _gyro_sensor.angle();
}

int SensorControl::getColorLeftReflect()
{
    return _color_left.reflected_light_intensity();
}


ev3dev::gyro_sensor SensorControl::_gyro_sensor = ev3dev::gyro_sensor(ev3dev::INPUT_1);
ev3dev::color_sensor SensorControl::_color_left = ev3dev::color_sensor(ev3dev::INPUT_2);
ev3dev::color_sensor SensorControl::_color_right = ev3dev::color_sensor(ev3dev::INPUT_3);

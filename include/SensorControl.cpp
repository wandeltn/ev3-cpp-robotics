#include "SensorControl.hpp"
#include <thread>
#include <chrono>
#include <iostream>

SensorControl::SensorControl()
{
    
}

void SensorControl::calibrateGyro()
{
    using namespace std::this_thread;

    ev3dev::lego_port gyro_port = ev3dev::lego_port(ev3dev::INPUT_1);
    gyro_port.set_mode("other-uart");
    sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
    gyro_port.set_mode("auto");
}

int SensorControl::getGyroValue()
{
    if (_gyro_sensor.connected()) {
        return _gyro_sensor.angle();
    } else {
        std::cout << _gyro_sensor.address();
        return 0;
    }
}

int SensorControl::getColorLeftReflect()
{
    return _color_left.reflected_light_intensity();
}


ev3dev::gyro_sensor SensorControl::_gyro_sensor = ev3dev::gyro_sensor(ev3dev::INPUT_1);
ev3dev::color_sensor SensorControl::_color_left = ev3dev::color_sensor(ev3dev::INPUT_2);
ev3dev::color_sensor SensorControl::_color_right = ev3dev::color_sensor(ev3dev::INPUT_3);

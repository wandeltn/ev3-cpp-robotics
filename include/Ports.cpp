#include "Ports.hpp"

//ev3dev::color_sensor Ports::_color_sensor_left = ev3dev::color_sensor(ev3dev::INPUT_2);
ev3dev::ultrasonic_sensor Ports::_distance_sensor = ev3dev::ultrasonic_sensor(ev3dev::INPUT_1);
ev3dev::gyro_sensor Ports::_gyro_sensor = ev3dev::gyro_sensor(ev3dev::INPUT_2);
ev3dev::color_sensor Ports::_color_sensor_left = ev3dev::color_sensor(ev3dev::INPUT_3);
ev3dev::color_sensor Ports::_color_sensor_right = ev3dev::color_sensor(ev3dev::INPUT_4);

ev3dev::large_motor Ports::_motor_left = ev3dev::large_motor(ev3dev::OUTPUT_A);

Ports::Ports()
{
    _distance_sensor.set_mode(ev3dev::ultrasonic_sensor::mode_us_dist_cm); 
    _gyro_sensor.set_mode(ev3dev::gyro_sensor::mode_gyro_cal);
    _gyro_sensor.set_mode(ev3dev::gyro_sensor::mode_gyro_ang);
    _color_sensor_left.set_mode(ev3dev::color_sensor::mode_ref_raw);
    _color_sensor_right.set_mode(ev3dev::color_sensor::mode_ref_raw);

    _motor_left.reset();
}

float Ports::Input::getUSDistance()
{
    if (_distance_sensor.connected()) {
        return _distance_sensor.float_value();
    } else {
        return -1.0f;
    }
}

float Ports::Input::getReflect(DEVICE_SIDE side)
{
    if (side = DEVICE_RIGHT) {
        return _color_sensor_right.float_value();
    } else {
        return _color_sensor_left.float_value();
    }
}

float Ports::Input::getHeading()
{
    return _gyro_sensor.float_value();
}

int Ports::Output::rotateMotor()
{
    _motor_left.set_position_sp(2000);
    _motor_left.set_speed_sp(_motor_left.max_speed()).run_to_abs_pos();
    return _motor_left.count_per_rot();
}


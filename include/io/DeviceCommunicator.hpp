#ifndef __DEVICECOMMUNICATOR_H__
#define __DEVICECOMMUNICATOR_H__

#include <string>
#include <array>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>

#define SENSORS_DIRECTORY   "/sys/class/lego-sensor/"
#define MOTORS_DIRECTORY    "/sys/class/tacho-motor/"
// #define SENSORS_DIRECTORY   "/home/niklas/fakesys/lego-sensor/"
// #define MOTORS_DIRECTORY    "/home/niklas/fakesys/tacho-motor/"
#define TYPE_PATH           "/driver_name"
#define PORT_PATH           "/address"
#define MOTOR_COMMAND_PATH  "/command"

class DeviceCommunicator {
    public: 
        DeviceCommunicator();
        static std::string input_1;
        static std::string input_2;
        static std::string input_3;
        static std::string input_4;
        
        static std::string output_A;
        static std::string output_B;
        static std::string output_C;
        static std::string output_D;

        //port binding to device
        static std::string& sensor_color_right;
        static std::string& sensor_color_left;
        static std::string& sensor_gyro;
        static std::string& sensor_ultrasonic;

        static std::string& motor_drive_right;
        static std::string& motor_drive_left;
        static std::string& motor_tool_drive;
        static std::string& motor_tool_shift;

    protected:
        static const std::string INPUT_1_TYPE;  //!< Sensor port 1
        static const std::string INPUT_2_TYPE;  //!< Sensor port 2
        static const std::string INPUT_3_TYPE;  //!< Sensor port 3
        static const std::string INPUT_4_TYPE;  //!< Sensor port 4

        static const std::string OUTPUT_A_TYPE; //!< Motor port A
        static const std::string OUTPUT_B_TYPE; //!< Motor port B
        static const std::string OUTPUT_C_TYPE; //!< Motor port C
        static const std::string OUTPUT_D_TYPE; //!< Motor port D

        static void readPorts();
        static double motorPulsesToCm(const double& value);
        static double CmToMotorPulses(const double& value);
};

#endif // __DEVICECOMMUNICATOR_H__
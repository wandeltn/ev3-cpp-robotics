#ifndef __DEVICECOMMUNICATOR_H__
#define __DEVICECOMMUNICATOR_H__

#include <string>
#include <array>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <atomic>
#include <unistd.h>

#define SENSORS_DIRECTORY   "/sys/class/lego-sensor/"
#define MOTORS_DIRECTORY    "/sys/class/tacho-motor/"
// #define SENSORS_DIRECTORY   "/home/niklas/fakesys/lego-sensor/"
// #define MOTORS_DIRECTORY    "/home/niklas/fakesys/tacho-motor/"
#define TYPE_PATH           "/driver_name"
#define PORT_PATH           "/address"
#define MOTOR_COMMAND_PATH  "/command"

enum MovementState {
    MOVEMENT_IDLE = 0,
    MOVEMENT_TURNING = 1,
    MOVEMENT_MOVING = 2
};

enum GyroMode {
    GYRO_ANG = 0,
    GYRO_RATE = 1,
    GYRO_FAS = 2,
    GYRO_G_A = 3,
    GYRO_CAL = 4,
    GYRO_TILT_RATE = 5,
    GYRO_TILT_ANG = 6
};

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
        static std::string INPUT_1_TYPE;  //!< Sensor port 1
        static std::string INPUT_2_TYPE;  //!< Sensor port 2
        static std::string INPUT_3_TYPE;  //!< Sensor port 3
        static std::string INPUT_4_TYPE;  //!< Sensor port 4
        static std::string OUTPUT_A_TYPE; //!< Motor port A
        static std::string OUTPUT_B_TYPE; //!< Motor port B
        static std::string OUTPUT_C_TYPE; //!< Motor port C
        static std::string OUTPUT_D_TYPE; //!< Motor port D

        static std::atomic<MovementState> state;

        static void readPorts();
        static double motorPulsesToMm(const double& value);
        static double MmToMotorPulses(const double& value);

        static void sendGyroMode(const GyroMode& mode);


        static int gyroValueOffset;
};

#endif // __DEVICECOMMUNICATOR_H__
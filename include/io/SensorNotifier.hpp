#pragma once

#include <string>
#include <sys/inotify.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <array>
#include <thread>
#include <functional>
#include <vector>
#include <map>

#define SENSORS_DIRECTORY   "/sys/class/lego-sensor/"
#define MOTORS_DIRECTORY    "/sys/class/lego-port/"
#define TYPE_PATH           "/driver_name"
#define PORT_PATH           "/address"

typedef std::string subscriber_port;


class SensorNotifier
{
    public:
        static const std::string INPUT_1_TYPE;   //!< Sensor port 1
        static const std::string INPUT_2_TYPE;   //!< Sensor port 2
        static const std::string INPUT_3_TYPE;   //!< Sensor port 3
        static const std::string INPUT_4_TYPE;   //!< Sensor port 4

        static const std::string OUTPUT_A_TYPE; //!< Motor port A
        static const std::string OUTPUT_B_TYPE; //!< Motor port B
        static const std::string OUTPUT_C_TYPE; //!< Motor port C
        static const std::string OUTPUT_D_TYPE; //!< Motor port D


        static std::string input_1;
        static std::string input_2;
        static std::string input_3;
        static std::string input_4;
        
        static std::string output_A;
        static std::string output_B;
        static std::string output_C;
        static std::string output_D;

        static std::string& sensor_color_right;
        static std::string& sensor_color_left;
        static std::string& sensor_gyro;
        static std::string& sensor_ultrasonic;
        
        static std::string& motor_drive_right;
        static std::string& motor_drive_left;
        static std::string& motor_tool_drive;
        static std::string& motor_tool_shift;
        
        SensorNotifier();
        ~SensorNotifier();

        static void subscribeToChange(subscriber_port device_port, std::function<void(int)> callback);
        static void subscribeToChange(std::function<void(std::map<subscriber_port&, int>)> callback);

    private:
        static std::thread _polling_thread;

        
        static std::vector<std::function<void(int)>> _input_1_listeners;
        static std::vector<std::function<void(int)>> _input_2_listeners;
        static std::vector<std::function<void(int)>> _input_3_listeners;
        static std::vector<std::function<void(int)>> _input_4_listeners;

        static std::vector<std::function<void(int)>> _output_A_listeners;
        static std::vector<std::function<void(int)>> _output_B_listeners;
        static std::vector<std::function<void(int)>> _output_C_listeners;
        static std::vector<std::function<void(int)>> _output_D_listeners;    

        static std::map<subscriber_port&, std::vector<std::function<void(int)>>> _path_listeners;
        static std::vector<std::function<void(std::map<subscriber_port&, int>)>> _listeners_to_all;
        static std::map<std::string&, int> _previous_values;

        static void readPorts();
        void Dispatcher(uint_fast8_t depth = 0);
};
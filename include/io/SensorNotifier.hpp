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
    static const std::string INPUT_1;   //!< Sensor port 1
    static const std::string INPUT_2;   //!< Sensor port 2
    static const std::string INPUT_3;   //!< Sensor port 3
    static const std::string INPUT_4;   //!< Sensor port 4

    static const std::string OUTPUT_A; //!< Motor port A
    static const std::string OUTPUT_B; //!< Motor port B
    static const std::string OUTPUT_C; //!< Motor port C
    static const std::string OUTPUT_D; //!< Motor port D
    
    SensorNotifier();
    ~SensorNotifier();

    static void subscribeToChange(subscriber_port device_port, std::function<void(int)> callback);

private:
    static std::thread _polling_thread;

    static std::string _input_1_path;
    static std::string _input_2_path;
    static std::string _input_3_path;
    static std::string _input_4_path;
    
    static std::string _output_A_path;
    static std::string _output_B_path;
    static std::string _output_C_path;
    static std::string _output_D_path;

    
    static std::vector<std::function<void(int)>> _input_1_listeners;
    static std::vector<std::function<void(int)>> _input_2_listeners;
    static std::vector<std::function<void(int)>> _input_3_listeners;
    static std::vector<std::function<void(int)>> _input_4_listeners;

    static std::vector<std::function<void(int)>> _output_A_listeners;
    static std::vector<std::function<void(int)>> _output_B_listeners;
    static std::vector<std::function<void(int)>> _output_C_listeners;
    static std::vector<std::function<void(int)>> _output_D_listeners;    

    static std::map<std::string, std::vector<std::function<void(int)>>> _path_listeners;

    static void readPorts();
    void Dispatcher();
};
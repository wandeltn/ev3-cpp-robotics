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
#include <set>
#include <map>
#include "DeviceCommunicator.hpp"



typedef std::string subscriber_port;
typedef std::array<ListenerTableRow, 8> port_listener_table;

struct ListenerTableRow {
    ListenerTableRow(std::string name) {
        portName = name;
        previousValue = 0;
        listeners = std::vector<std::function<void(int)>>{};
    }

    std::string portName;
    int previousValue;
    std::vector<std::function<void(int)>> listeners;
};

class SensorNotifier : protected DeviceCommunicator
{
    public:        
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

        static port_listener_table _lookup_table;

        void Dispatcher();
};
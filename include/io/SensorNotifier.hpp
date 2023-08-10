#ifndef __SENSORNOTIFIER_H__
#define __SENSORNOTIFIER_H__

#include <string>
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
#include <list>
#include <atomic>
#include "DeviceCommunicator.hpp"



typedef std::string subscriber_port;

struct ListenerTableRow {
    ListenerTableRow(subscriber_port& name):  portName(name) {
        previousValue = 0;
        listeners = {};
    }

    subscriber_port& portName;
    int previousValue;
    std::list<void(*)(int)> listeners;
};

typedef std::array<ListenerTableRow, 8> port_listener_table;

class SensorNotifier : protected DeviceCommunicator
{
    public:        
        SensorNotifier();
        ~SensorNotifier();

        static std::list<void(*)(int)>::iterator subscribeToChange(subscriber_port device_port, void(*callback)(int));
        static void unsubscribeFromChange(std::list<void(*)(int)>::iterator callback);
        static void subscribeToAllChanges(std::function<void(std::map<subscriber_port, int>)> callback);

    private:
        static std::thread _polling_thread;
        static std::vector<std::function<void(std::map<subscriber_port, int>)>> _listeners;

        static port_listener_table _lookup_table;
        static std::atomic<bool> _run_thread;

        void Dispatcher();
};

#endif // __SENSORNOTIFIER_H__
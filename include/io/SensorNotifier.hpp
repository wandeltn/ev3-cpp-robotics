#ifndef __SENSORNOTIFIER_H__
#define __SENSORNOTIFIER_H__

#include <string>
#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <array>
#include <functional>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <atomic>
#include <future>
#include "DeviceCommunicator.hpp"



typedef std::string subscriber_port;

struct ListenerTableRow {
    ListenerTableRow(subscriber_port& name, std::string id):  portName(name) {
        previousValue = 0;
        listeners = {};
        deviceIdentifier = id;
        firstRead = true;
    }

    std::string deviceIdentifier;
    subscriber_port& portName;
    int previousValue;
    std::list<void(*)(int)> listeners;
    static bool firstRead;
};

struct port_listener_table {
    port_listener_table(
        ListenerTableRow first,
        ListenerTableRow second,
        ListenerTableRow third,
        ListenerTableRow fourth,
        ListenerTableRow fifth,
        ListenerTableRow sixth,
        ListenerTableRow seventh,
        ListenerTableRow eightth
    ): _content{first, second, third, fourth, fifth, sixth, seventh, eightth} {

    }
    auto begin() {
        return _content.begin();
    }

    auto end() {
        return _content.end();
    }

    std::map<std::string, std::string> getFilePaths(){
        std::map<std::string, std::string> map{};
        for (auto& device : *this) {
            map[device.deviceIdentifier] = device.portName;
        }
        return map;
    };

    const auto operator[](const std::string& value) {
        for (auto& device : _content) {
            if (device.deviceIdentifier == value) {
                return &device;
            }
        }
    }
    explicit operator std::map<std::string, int>() {
        std::map<std::string, int> map{};
        for (auto device : *this) {
            map[device.deviceIdentifier] = device.previousValue;
        }
        return map;
    }
    std::array<ListenerTableRow, 8> _content;
};

class SensorNotifier : protected DeviceCommunicator
{
    public:        
        SensorNotifier();
        ~SensorNotifier();

        static std::list<void(*)(int)>::iterator subscribeToChange(subscriber_port device_port, void(*callback)(int));
        static void unsubscribeFromChange(std::list<void(*)(int)>::iterator callback, subscriber_port device_port);
        static void subscribeToAllChanges(std::function<void(std::map<subscriber_port, int>, std::map<subscriber_port, int>)> callback);

        int Dispatcher(bool dispatch = true);

        static std::map<std::string, int> getCurrentValues();
        static const std::map<std::string, std::string> getDevices();

    private:
        static std::vector<std::function<void(std::map<subscriber_port, int>, std::map<subscriber_port, int>)>> _listeners;
        static port_listener_table _lookup_table;

};

#endif // __SENSORNOTIFIER_H__
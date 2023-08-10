#include "SensorNotifier.hpp"


std::thread SensorNotifier::_polling_thread;
std::vector<std::function<void(std::map<subscriber_port, int>)>> SensorNotifier::_listeners{};
std::atomic<bool> SensorNotifier::_run_thread;

port_listener_table SensorNotifier::_lookup_table = port_listener_table{
    ListenerTableRow{input_1},
    ListenerTableRow{input_2},
    ListenerTableRow{input_3},
    ListenerTableRow{input_4},
    ListenerTableRow{output_A},
    ListenerTableRow{output_B},
    ListenerTableRow{output_C},
    ListenerTableRow{output_D}
};


SensorNotifier::SensorNotifier()
{
    _run_thread.store(true);
    _polling_thread = std::thread{&SensorNotifier::Dispatcher, this};
    
}

SensorNotifier::~SensorNotifier()
{
    _run_thread.store(false);
    _polling_thread.join();
}

std::list<void(*)(int)>::iterator SensorNotifier::subscribeToChange(subscriber_port device_port, void(*callback)(int))
{
    for (ListenerTableRow& row : _lookup_table) {
        if (row.portName == device_port) {
            row.listeners.push_back(callback);
            return row.listeners.end();
            break;
        }
    }
}

void SensorNotifier::subscribeToAllChanges(std::function<void(std::map<subscriber_port, int>)> callback)
{
    _listeners.push_back(callback);
}

void SensorNotifier::unsubscribeFromChange(std::list<void(*)(int)>::iterator callback)
{
    for (ListenerTableRow& row : _lookup_table) {
        row.listeners.erase(callback);
    }
}

void SensorNotifier::Dispatcher()
{
    while (_run_thread.load()) {
        for (ListenerTableRow device : _lookup_table) {
            
            std::ifstream ifs = std::ifstream{};

            if (!ifs.is_open()) {
                std::cerr << "Device could not be found: " << device.portName << std::endl;
                readPorts();
                ifs.open(device.portName);
                //check if problem continues
                if (!ifs.is_open()) {
                    throw new std::invalid_argument("Device failed to open: " + device.portName);
                }
            }

            std::string readValue;
            getline(ifs, readValue);

            //check for letters before cast to int
            if (readValue.find_first_not_of("0123456789") == std::string::npos) {
                throw new std::invalid_argument("device file contains letters and can not be cast to int: " + device.portName);
            } 
            if (std::stoi(readValue) != device.previousValue) {
                for (std::function<void(int)> listener : device.listeners) {
                    listener(std::stoi(readValue));
                }
            }
            device.previousValue = std::stoi(readValue);
            ifs.close();
        }
        std::map<subscriber_port, int> tempMap = {};
        for (ListenerTableRow row : _lookup_table) {
            tempMap[row.portName] = row.previousValue;
        }
        for (std::function<void(std::map<subscriber_port, int>)> listener : _listeners) {
            listener(tempMap);
        }
        usleep(10);
    }
}

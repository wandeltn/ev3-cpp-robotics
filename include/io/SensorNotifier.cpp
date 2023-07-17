#include "SensorNotifier.hpp"


std::thread SensorNotifier::_polling_thread;

std::vector<std::function<void(int)>> SensorNotifier::_input_1_listeners = {};
std::vector<std::function<void(int)>> SensorNotifier::_input_2_listeners = {};
std::vector<std::function<void(int)>> SensorNotifier::_input_3_listeners = {};
std::vector<std::function<void(int)>> SensorNotifier::_input_4_listeners = {};

std::vector<std::function<void(int)>> SensorNotifier::_output_A_listeners = {};
std::vector<std::function<void(int)>> SensorNotifier::_output_B_listeners = {};
std::vector<std::function<void(int)>> SensorNotifier::_output_C_listeners = {};
std::vector<std::function<void(int)>> SensorNotifier::_output_D_listeners = {}; 

port_listener_table SensorNotifier::_lookup_table = std::array<ListenerTableRow, 8>{
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
    readPorts();

    _polling_thread = std::thread{&SensorNotifier::Dispatcher, this};
}

SensorNotifier::~SensorNotifier()
{

}

void SensorNotifier::subscribeToChange(subscriber_port device_port, std::function<void(int)> callback)
{
    if (_path_listeners.count(device_port) != 0){
        _path_listeners[device_port].push_back(callback);
    } else {
        throw new std::invalid_argument("device port " + device_port + " not recognized");
    }
}

void SensorNotifier::subscribeToChange(std::function<void(std::map<subscriber_port&, int>)> callback)
{
    // _listeners_to_all.push_back(callback);
}

void SensorNotifier::Dispatcher()
{
    // for (std::pair<subscriber_port &, std::vector<std::function<void (int)>>> device : _path_listeners) {
        
    //     std::ifstream ifs = std::ifstream{};

    //     if (!ifs.is_open()) {
    //         std::cerr << "Device could not be found: " << device.first << std::endl;
    //         readPorts();
    //         ifs.open(device.first);
    //         //check if problem continues
    //         if (!ifs.is_open()) {
    //             throw new std::invalid_argument("Device failed to open: " + device.first);
    //         }
    //     }

    //     std::string readValue;
    //     getline(ifs, readValue);

    //     //check for letters before cast to int
    //     if (readValue.find_first_not_of("0123456789") == std::string::npos) {
    //         throw new std::invalid_argument("device file contains letters and can not be cast to int: " + device.first);
    //     } 
    //     if (std::stoi(readValue) != _previous_values[device.first]) {
    //         for (std::function<void(int)> listener : device.second) {
    //             listener(std::stoi(readValue));
    //         }
    //     }
    //     _previous_values[device.first] = std::stoi(readValue);
    //     ifs.close();
    // }
    // for (std::function<void (std::map<subscriber_port&, int>)> listener : _listeners_to_all) {
    //     listener(_previous_values);
    // }
    // usleep(10);
}

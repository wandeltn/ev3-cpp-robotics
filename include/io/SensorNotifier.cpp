#include "SensorNotifier.hpp"

const std::string SensorNotifier::INPUT_1 = std::string{"ev3-ports:in1"};
const std::string SensorNotifier::INPUT_2 = std::string{"ev3-ports:in2"};
const std::string SensorNotifier::INPUT_3 = std::string{"ev3-ports:in3"};
const std::string SensorNotifier::INPUT_4 = std::string{"ev3-ports:in4"};
const std::string SensorNotifier::OUTPUT_A = std::string{"ev3-ports:outA"};
const std::string SensorNotifier::OUTPUT_B = std::string{"ev3-ports:outB"};
const std::string SensorNotifier::OUTPUT_C = std::string{"ev3-ports:outC"};
const std::string SensorNotifier::OUTPUT_D = std::string{"ev3-ports:outD"};

std::thread SensorNotifier::_polling_thread;

std::string SensorNotifier::_input_1_path;
std::string SensorNotifier::_input_2_path;
std::string SensorNotifier::_input_3_path;
std::string SensorNotifier::_input_4_path;

std::string SensorNotifier::_output_A_path;
std::string SensorNotifier::_output_B_path;
std::string SensorNotifier::_output_C_path;
std::string SensorNotifier::_output_D_path;

std::vector<std::function<void(int)>> SensorNotifier::_input_1_listeners = {};
std::vector<std::function<void(int)>> SensorNotifier::_input_2_listeners = {};
std::vector<std::function<void(int)>> SensorNotifier::_input_3_listeners = {};
std::vector<std::function<void(int)>> SensorNotifier::_input_4_listeners = {};

std::vector<std::function<void(int)>> SensorNotifier::_output_A_listeners = {};
std::vector<std::function<void(int)>> SensorNotifier::_output_B_listeners = {};
std::vector<std::function<void(int)>> SensorNotifier::_output_C_listeners = {};
std::vector<std::function<void(int)>> SensorNotifier::_output_D_listeners = {}; 


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
    if (device_port == INPUT_1) { _input_1_listeners.push_back(callback); }
    else if (device_port == INPUT_2) { _input_2_listeners.push_back(callback); }
    else if (device_port == INPUT_3) { _input_3_listeners.push_back(callback); }
    else if (device_port == INPUT_4) { _input_4_listeners.push_back(callback); }
    else if (device_port == OUTPUT_A) { _output_A_listeners.push_back(callback); }
    else if (device_port == OUTPUT_B) { _output_B_listeners.push_back(callback); }
    else if (device_port == OUTPUT_C) { _output_C_listeners.push_back(callback); }
    else if (device_port == OUTPUT_D) { _output_D_listeners.push_back(callback); }
    else {
        throw new std::invalid_argument("device port " + device_port + " not recognized");
    }
}


void SensorNotifier::readPorts()
{
    std::array<std::string, 2> sensor_types = {
        SENSORS_DIRECTORY,
        MOTORS_DIRECTORY
    };

    for (std::string sensor_type : sensor_types) {
        DIR *directory = opendir(sensor_type.c_str());
        struct dirent *entry = readdir(directory);
        while (entry != NULL) {
            if (entry->d_type == DT_DIR) {
                std::ifstream ifs = std::ifstream{};
                ifs.open(sensor_type + std::string{entry->d_name} + PORT_PATH);
                if (!ifs.is_open()) {
                    throw(
                        new std::invalid_argument{
                            "error while opening " + 
                            std::string{sensor_type} + 
                            std::string{entry->d_name} + 
                            PORT_PATH
                        }
                    );
                }
                std::string line;
                getline(ifs, line);
                std::string path = std::string{sensor_type} + 
                    std::string{entry->d_name} + 
                    PORT_PATH;

                if (line == INPUT_1) { _input_1_path = path; }
                else if (line == INPUT_2) { _input_2_path = path; }
                else if (line == INPUT_3) { _input_3_path = path; }
                else if (line == INPUT_4) { _input_4_path = path; }
                else if (line == OUTPUT_A) { _output_A_path = path; }
                else if (line == OUTPUT_B) { _output_B_path = path; }
                else if (line == OUTPUT_C) { _output_C_path = path; }
                else if (line == OUTPUT_D) { _output_D_path = path; }
                else {
                    ifs.close();
                    closedir(directory);
                    throw new std::invalid_argument("sensor port not recognized");
                }
                ifs.close();
            entry = readdir(directory);
            }
        }
        closedir(directory);
    }
}

void SensorNotifier::Dispatcher()
{
    
}

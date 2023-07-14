#include "SensorNotifier.hpp"

const std::string SensorNotifier::INPUT_1_TYPE = std::string{"ev3-ports:in1"};
const std::string SensorNotifier::INPUT_2_TYPE = std::string{"ev3-ports:in2"};
const std::string SensorNotifier::INPUT_3_TYPE = std::string{"ev3-ports:in3"};
const std::string SensorNotifier::INPUT_4_TYPE= std::string{"ev3-ports:in4"};
const std::string SensorNotifier::OUTPUT_A_TYPE = std::string{"ev3-ports:outA"};
const std::string SensorNotifier::OUTPUT_B_TYPE = std::string{"ev3-ports:outB"};
const std::string SensorNotifier::OUTPUT_C_TYPE = std::string{"ev3-ports:outC"};
const std::string SensorNotifier::OUTPUT_D_TYPE = std::string{"ev3-ports:outD"};

std::thread SensorNotifier::_polling_thread;

std::string SensorNotifier::input_1;
std::string SensorNotifier::input_2;
std::string SensorNotifier::input_3;
std::string SensorNotifier::input_4;

std::string SensorNotifier::output_A;
std::string SensorNotifier::output_B;
std::string SensorNotifier::output_C;
std::string SensorNotifier::output_D;


std::string& SensorNotifier::sensor_color_right = SensorNotifier::input_1;
std::string& SensorNotifier::sensor_color_left = SensorNotifier::input_2;
std::string& SensorNotifier::sensor_gyro = SensorNotifier::input_3;
std::string& SensorNotifier::sensor_ultrasonic = SensorNotifier::input_4;

std::string& SensorNotifier::motor_drive_right = SensorNotifier::output_A;
std::string& SensorNotifier::motor_drive_left = SensorNotifier::output_B;
std::string& SensorNotifier::motor_tool_drive = SensorNotifier::output_C;
std::string& SensorNotifier::motor_tool_shift = SensorNotifier::output_D;


std::vector<std::function<void(int)>> SensorNotifier::_input_1_listeners = {};
std::vector<std::function<void(int)>> SensorNotifier::_input_2_listeners = {};
std::vector<std::function<void(int)>> SensorNotifier::_input_3_listeners = {};
std::vector<std::function<void(int)>> SensorNotifier::_input_4_listeners = {};

std::vector<std::function<void(int)>> SensorNotifier::_output_A_listeners = {};
std::vector<std::function<void(int)>> SensorNotifier::_output_B_listeners = {};
std::vector<std::function<void(int)>> SensorNotifier::_output_C_listeners = {};
std::vector<std::function<void(int)>> SensorNotifier::_output_D_listeners = {}; 

std::map<subscriber_port&, std::vector<std::function<void(int)>>> SensorNotifier::_path_listeners = {
    {SensorNotifier::input_1, SensorNotifier::_input_1_listeners},
    {SensorNotifier::input_2, SensorNotifier::_input_2_listeners},
    {SensorNotifier::input_3, SensorNotifier::_input_3_listeners},
    {SensorNotifier::input_4, SensorNotifier::_input_4_listeners},
    {SensorNotifier::output_A, SensorNotifier::_output_A_listeners},
    {SensorNotifier::output_B, SensorNotifier::_output_B_listeners},
    {SensorNotifier::output_C, SensorNotifier::_output_C_listeners},
    {SensorNotifier::output_D, SensorNotifier::_output_D_listeners},
};

std::vector<std::function<void(std::map<subscriber_port&, int>)>> SensorNotifier::_listeners_to_all = {};

std::map<std::string&, int> SensorNotifier::_previous_values = {
    {SensorNotifier::input_1, 0},
    {SensorNotifier::input_2, 0},
    {SensorNotifier::input_3, 0},
    {SensorNotifier::input_4, 0},
    {SensorNotifier::output_A, 0},
    {SensorNotifier::output_B, 0},
    {SensorNotifier::output_C, 0},
    {SensorNotifier::output_D, 0},
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
    _listeners_to_all.push_back(callback);
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

                if (line == INPUT_1_TYPE) { input_1 = path; }
                else if (line == INPUT_2_TYPE) { input_2 = path; }
                else if (line == INPUT_3_TYPE) { input_3 = path; }
                else if (line == INPUT_4_TYPE) { input_4 = path; }
                else if (line == OUTPUT_A_TYPE) { output_A = path; }
                else if (line == OUTPUT_B_TYPE) { output_B = path; }
                else if (line == OUTPUT_C_TYPE) { output_C = path; }
                else if (line == OUTPUT_D_TYPE) { output_D = path; }
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

void SensorNotifier::Dispatcher(uint_fast8_t depth = 0)
{
    for (std::pair<subscriber_port &, std::vector<std::function<void (int)>>> device : _path_listeners) {
        
        std::ifstream ifs = std::ifstream{};
        ifs.open(device.first);

        if (!ifs.is_open()) {
            std::cerr << "Device could not be found: " << device.first << std::endl;
            readPorts();
        }

        std::string readValue;
        getline(ifs, readValue);

        //check for letters before cast to int
        if (readValue.find_first_not_of("0123456789") == std::string::npos) {
            throw new std::invalid_argument("device file contains letters and can not be cast to int: " + device.first);
        } 
        if (std::stoi(readValue) != _previous_values[device.first]) {
            for (std::function<void(int)> listener : device.second) {
                listener(std::stoi(readValue));
            }
        }
        _previous_values[device.first] = std::stoi(readValue);
        ifs.close();
    }
    for (std::function<void (std::map<subscriber_port&, int>)> listener : _listeners_to_all) {
        listener(_previous_values);
    }
    usleep(10);
}

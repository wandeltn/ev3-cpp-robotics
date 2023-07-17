#include "DeviceCommunicator.hpp"


const std::string DeviceCommunicator::INPUT_1_TYPE = std::string{"ev3-ports:in1"};
const std::string DeviceCommunicator::INPUT_2_TYPE = std::string{"ev3-ports:in2"};
const std::string DeviceCommunicator::INPUT_3_TYPE = std::string{"ev3-ports:in3"};
const std::string DeviceCommunicator::INPUT_4_TYPE= std::string{"ev3-ports:in4"};

const std::string DeviceCommunicator::OUTPUT_A_TYPE = std::string{"ev3-ports:outA"};
const std::string DeviceCommunicator::OUTPUT_B_TYPE = std::string{"ev3-ports:outB"};
const std::string DeviceCommunicator::OUTPUT_C_TYPE = std::string{"ev3-ports:outC"};
const std::string DeviceCommunicator::OUTPUT_D_TYPE = std::string{"ev3-ports:outD"};


std::string DeviceCommunicator::input_1 = "";
std::string DeviceCommunicator::input_2 = "";
std::string DeviceCommunicator::input_3 = "";
std::string DeviceCommunicator::input_4 = "";

std::string DeviceCommunicator::output_A = "";
std::string DeviceCommunicator::output_B = "";
std::string DeviceCommunicator::output_C = "";
std::string DeviceCommunicator::output_D = "";


std::string& sensor_color_right = DeviceCommunicator::input_1;
std::string& sensor_color_left = DeviceCommunicator::input_2;
std::string& sensor_gyro = DeviceCommunicator::input_3;
std::string& sensor_ultrasonic = DeviceCommunicator::input_4;
std::string& motor_drive_right = DeviceCommunicator::output_A;
std::string& motor_drive_left = DeviceCommunicator::output_B;
std::string& motor_tool_drive = DeviceCommunicator::output_C;
std::string& motor_tool_shift = DeviceCommunicator::output_D;


void DeviceCommunicator::readPorts()
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
                std::string path = std::string{sensor_type} + std::string{entry->d_name};

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

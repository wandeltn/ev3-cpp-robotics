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


std::string& DeviceCommunicator::sensor_color_right = DeviceCommunicator::input_1;
std::string& DeviceCommunicator::sensor_color_left = DeviceCommunicator::input_2;
std::string& DeviceCommunicator::sensor_gyro = DeviceCommunicator::input_3;
std::string& DeviceCommunicator::sensor_ultrasonic = DeviceCommunicator::input_4;
std::string& DeviceCommunicator::motor_drive_right = DeviceCommunicator::output_A;
std::string& DeviceCommunicator::motor_drive_left = DeviceCommunicator::output_B;
std::string& DeviceCommunicator::motor_tool_drive = DeviceCommunicator::output_C;
std::string& DeviceCommunicator::motor_tool_shift = DeviceCommunicator::output_D;

MovementState DeviceCommunicator::state = MOVEMENT_IDLE;


void DeviceCommunicator::readPorts()
{
    std::array<const std::string, 2> sensor_types = {
        SENSORS_DIRECTORY,
        MOTORS_DIRECTORY
    };

    for (const std::string sensor_type : sensor_types) {
        DIR *directory = opendir(sensor_type.c_str());
        struct dirent *entry = readdir(directory);
        while ((entry = readdir(directory)) != nullptr) {
            // std::cout << entry->d_name << std::endl;
            if (std::string{entry->d_name}.find(".") == std::string::npos) {
                std::string path{sensor_type + std::string{entry->d_name}};

                FILE* fp = fopen((path + PORT_PATH).c_str(), "r");
                char* charLine = NULL;
                size_t len = 0;
                getline(&charLine, &len, fp); 

                std::string line{charLine};
                line.erase(std::remove_if(
                    line.begin(),
                    line.end(),
                    [](unsigned char c){
                        return !std::isprint(c);
                    }),
                    line.end()
                );

                if (line == INPUT_1_TYPE) { input_1 = path; }
                else if (line == INPUT_2_TYPE) { input_2 = path; }
                else if (line == INPUT_3_TYPE) { input_3 = path; }
                else if (line == INPUT_4_TYPE) { input_4 = path; }
                else if (line == OUTPUT_A_TYPE) { output_A = path; }
                else if (line == OUTPUT_B_TYPE) { output_B = path; }
                else if (line == OUTPUT_C_TYPE) { output_C = path; }
                else if (line == OUTPUT_D_TYPE) { output_D = path; }
                else {
                    std::cout << "port not recognized" << std::endl;
                    // closedir(directory);
                    // throw new std::invalid_argument("sensor port not recognized");
                }
                fclose(fp);
                if(charLine) {
                    free(charLine);
                }
            }
        }
        closedir(directory);
    }
}

double DeviceCommunicator::motorPulsesToCm(const double& value)
{
    return value / 360 * 15.6; 
}

double DeviceCommunicator::CmToMotorPulses(const double& value)
{
    return value / 15.6 * 360;
}


DeviceCommunicator::DeviceCommunicator()
{
    readPorts();
    sensor_color_right = input_1;
    sensor_color_left = input_2;
    sensor_gyro = input_3;
    sensor_ultrasonic = input_4;
    motor_drive_right = output_A;
    motor_drive_left = output_B;
    motor_tool_drive = output_C;
    motor_tool_shift = output_D;
}

#include "DeviceCommunicator.hpp"

std::string DeviceCommunicator::INPUT_1_TYPE = std::string{"ev3-ports:in1"};
std::string DeviceCommunicator::INPUT_2_TYPE = std::string{"ev3-ports:in2"};
std::string DeviceCommunicator::INPUT_3_TYPE = std::string{"ev3-ports:in3"};
std::string DeviceCommunicator::INPUT_4_TYPE= std::string{"ev3-ports:in4"};

std::string DeviceCommunicator::OUTPUT_A_TYPE = std::string{"ev3-ports:outA"};
std::string DeviceCommunicator::OUTPUT_B_TYPE = std::string{"ev3-ports:outB"};
std::string DeviceCommunicator::OUTPUT_C_TYPE = std::string{"ev3-ports:outC"};
std::string DeviceCommunicator::OUTPUT_D_TYPE = std::string{"ev3-ports:outD"};


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

std::atomic<MovementState> DeviceCommunicator::state;

int DeviceCommunicator::gyroValueOffset = 0;


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

                INPUT_1_TYPE = std::string{"ev3-ports:in1"};
                INPUT_2_TYPE = std::string{"ev3-ports:in2"};
                INPUT_3_TYPE = std::string{"ev3-ports:in3"};
                INPUT_4_TYPE= std::string{"ev3-ports:in4"};
                OUTPUT_A_TYPE = std::string{"ev3-ports:outA"};
                OUTPUT_B_TYPE = std::string{"ev3-ports:outB"};
                OUTPUT_C_TYPE = std::string{"ev3-ports:outC"};
                OUTPUT_D_TYPE = std::string{"ev3-ports:outD"};

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

    sendGyroMode(GYRO_CAL);
    sleep(0.5);
    sendGyroMode(GYRO_ANG);
}

double DeviceCommunicator::motorPulsesToMm(const double& value)
{
    return value / 360 * 156; 
}

double DeviceCommunicator::MmToMotorPulses(const double& value)
{
    return value / 156 * 360;
}

void DeviceCommunicator::sendGyroMode(const GyroMode &mode)
{
    FILE* fp;
    fp = fopen((sensor_gyro + "/mode").c_str(), "w");

    switch (mode)
    {
    case GYRO_ANG:
        fprintf(fp, "GYRO-ANG");
        break;
    
    case GYRO_RATE:
        fprintf(fp, "GYRO-RATE");

    case GYRO_FAS:
        fprintf(fp, "GYRO-FAS");

    case GYRO_G_A:
        fprintf(fp, "GYRO-G&A");

    case GYRO_CAL:
        fprintf(fp, "GYRO-CAL");

    case GYRO_TILT_RATE:
        fprintf(fp, "TILT-RATE");

    case GYRO_TILT_ANG:
        fprintf(fp, "TILT_ANG");

    default:
        break;
    }

    fclose(fp);
}

DeviceCommunicator::DeviceCommunicator()
{
    state.store(MOVEMENT_IDLE);
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
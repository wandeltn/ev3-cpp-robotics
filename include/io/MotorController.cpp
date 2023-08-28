#include "MotorController.hpp"

std::thread MotorController::_movement_thread;
SensorNotifier MotorController::_sensors{};
LocationTracker MotorController::_location{};
std::atomic<bool> MotorController::_turnReached;
std::atomic<int> MotorController::_gyroTarget;

MotorController::MotorController()
{
    // readPorts();
    _sensors.subscribeToChange(sensor_gyro, watchGyro);
}

void MotorController::rotateTo(const int angle)
{
    state = MOVEMENT_TURNING;
    if (_location.getHeading() == angle) {
        state = MOVEMENT_IDLE;
        return;
    } else if (_location.getHeading() > angle) {
        setDutyCycle(motor_drive_right, 20);
        setDutyCycle(motor_drive_left, -20);
    } else {
        setDutyCycle(motor_drive_right, -20);
        setDutyCycle(motor_drive_left, 20);
    }

    sendCommand(motor_drive_left, MotorCommandRunDirect);
    sendCommand(motor_drive_right, MotorCommandRunDirect);

    _turnReached.store(false);
    _gyroTarget.store(angle);

    std::vector<std::string> right_state = getState(motor_drive_right);
    std::vector<std::string> left_state = getState(motor_drive_left);

    std::cout << "right state: " << std::endl;
    for (std::string state : right_state) {
        std::cout << state;
    }
    std::cout << std::endl;
    std::cout << "left state: " << std::endl;
    for (std::string state : left_state) {
        std::cout << state;
    }
    std::cout << std::endl;

}

void MotorController::moveStraight(const int distance)
{
    state = MOVEMENT_MOVING;

    setMotorSpeed(motor_drive_left, 600);
    setMotorSpeed(motor_drive_right, 600);


    FILE* fp_left_pos;
    FILE* fp_right_pos;
    FILE* fp_left_com;
    FILE* fp_right_com;

    fp_left_pos = fopen((motor_drive_left + "/position_sp").c_str(), "w");
    fp_right_pos = fopen((motor_drive_right + "/position_sp").c_str(), "w");
    fp_left_com = fopen((motor_drive_left + "/command").c_str(), "w");
    fp_right_com = fopen((motor_drive_right + "/command").c_str(), "w");

    if (
        fp_left_pos == NULL ||
        fp_right_pos == NULL ||
        fp_left_com == NULL ||
        fp_right_com == NULL
    ) {
        std::cout << "failed to open drive motor files" << std::endl;
    } else {
        fprintf(fp_left_pos, "%d", distance);
        fprintf(fp_right_pos, "%d", distance);

        fprintf(fp_left_com, "run-to-rel-pos");
        fprintf(fp_right_com, "run-to-rel-pos");
    }

    fclose(fp_left_pos);
    fclose(fp_right_pos);
    fclose(fp_left_com);
    fclose(fp_right_com);  

    state = MOVEMENT_IDLE;
}

void MotorController::setMotorSpeed(std::string motor, int speed)
{
    FILE* fp;
    fp = fopen((motor + "/speed_sp").c_str(), "w");

    if (fp == NULL) {
        std::cout << "failed to set speed: " << motor << std::endl;
    } else {
        fprintf(fp, "%d", speed);
        fclose(fp);
    }
}

void MotorController::watchGyro(int value)
{   
    if (state == MOVEMENT_TURNING) {
        std::cout << "current gyro value: " << value << std::endl;
        if (value % 360 == _gyroTarget.load()) {
            _turnReached.store(true);
            setStop(motor_drive_left);
            setStop(motor_drive_right);
            state = MOVEMENT_IDLE;
        }
    }
}

std::vector<std::string> MotorController::getState(const std::string motor)
{
    std::ifstream ifs{};
    std::vector<std::string> deviceState{};
    std::string state{};
    ifs.open(motor + "/state");
    if(ifs.is_open()) {
        while (getline(ifs, state, ' ')) {
            state.erase(std::remove_if(
                    state.begin(),
                    state.end(),
                    [](unsigned char c){
                        return !std::isprint(c);
                    }),
                    state.end()
            );
            deviceState.push_back(state);
        }
    } else {
        std::cout << "state could not be read" << std::endl;
    }
    return deviceState;
}

void MotorController::setPolarity(const std::string motor, MotorPolarityInversed)
{
    FILE* fp;
    fp = fopen((motor + "/polarity").c_str(), "w");

    if (fp == NULL) {
        std::cout << "failed to set inversed polarity: " << motor << std::endl;
    } else {
        fprintf(fp, "inversed");
        fclose(fp);
    }
}

void MotorController::setPolarity(const std::string motor, MotorPolarityNormal)
{
    FILE* fp;
    fp = fopen((motor + "/polarity").c_str(), "w");

    if (fp == NULL) {
        std::cout << "failed to set normal polarity: " << motor << std::endl;
    } else {
        fprintf(fp, "normal");
        fclose(fp);
    }
}

void MotorController::setDutyCycle(const std::string motor, const int value)
{
    FILE* fp;
    fp = fopen((motor + "/duty_cycle_sp").c_str(), "w");

    if (fp == NULL) {
        std::cout << "failed to set duty cycle: " << motor << std::endl;
    } else
    {
        fprintf(fp, "%d", value);
        fclose(fp);
    }
}

void MotorController::setStop(const std::string motor)
{
    sendCommand(motor, MotorCommandStop);
}

void MotorController::setStopAction(const std::string motor, const MotorStopAction action)
{
    FILE* fp;
    fp = fopen((motor + "/stop_action").c_str(), "w");

    if (fp == NULL) {
        std::cout << "failed to set stop action: " << motor << std::endl;
    } else {
        switch (action)
        {
        case MotorStopActionCoast:
            fprintf(fp, "coast");
            break;
        
        case MotorStopActionHold:
            fprintf(fp, "hold");
            break;

        case MotorStopActionBrake:
            fprintf(fp, "brake");
            break;

        default:
            break;
        }
        fclose(fp);
    }
}

void MotorController::sendCommand(const std::string motor, const MotorCommand command)
{
    FILE* fp;
    fopen((motor + "/command").c_str(), "w");

    if (fp == NULL) {
        std::cout << "failed to send command to: " << motor << std::endl;
    } else {
        switch (command)
        {
        case MotorCommandStop:
            fprintf(fp, "stop");
            break;

        case MotorCommandReset:
            fprintf(fp, "reset");
            break;

        case MotorCommandRunToAbsPos:
            fprintf(fp, "run-to-abs-pos");
            break;
        
        case MotorCommandRunDirect:
            fprintf(fp, "run-direct");
            break;

        case MotorCommandRunToRelPos:
            fprintf(fp, "run-to-rel-pos");
            break;

        case MotorCommandRunTimed:
            fprintf(fp, "run-timed");
            break;

        case MotorCommandRunForever:
            fprintf(fp, "run-forever");
            break;

        default:
            std::cout << "unable to send command: " << command << std::endl;
            break;
        }
        fclose(fp);
    }
}

void MotorController::stopAll()
{
    setStop(motor_drive_left);
    setStop(motor_drive_right);
}

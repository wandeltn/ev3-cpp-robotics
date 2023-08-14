#include "MotorController.hpp"

std::thread MotorController::_movement_thread;
std::deque<MovementAction> MotorController::_movement_queue{};
SensorNotifier MotorController::_sensors{};
LocationTracker MotorController::_location{};
// std::condition_variable MotorController::_cv;
std::atomic<bool> MotorController::_turnReached;
std::atomic<int> MotorController::_gyroTarget;
MovementState MotorController::state = MOVEMENT_IDLE;
std::mutex MotorController::_mutex{};


MotorController::MotorController()
{
    // readPorts();
    std::list<void(*)(int)>::iterator listener = _sensors.subscribeToChange(sensor_gyro, watchGyro);
    _movement_thread = std::thread{updateMovement};   
    _movement_thread.join();
}   

void MotorController::updateMovement()
{
    std::ifstream ifs{};
    std::string deviceState{};
    ifs.open(DeviceCommunicator::motor_drive_left + "/state");
    if(ifs.is_open()) {
        getline(ifs, deviceState);
        std::cout << "current state: " << deviceState << std::endl;
    } else {
        std::cout << "state could not be read" << std::endl;
    }
    if (deviceState.find("running") == std::string::npos) {
        MovementAction current = _movement_queue.front();
        _movement_queue.pop_front();
        
    }
}

void MotorController::appendMovement(MovementAction action)
{
    _movement_queue.push_back(action);

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

    FILE* fp_left;
    FILE* fp_right;

    fp_left = fopen((motor_drive_left + "/command").c_str(), "w");
    fp_right = fopen((motor_drive_right + "/command").c_str(), "w");

    if (
        fp_left == NULL ||
        fp_right == NULL
    ) {
        std::cout << "failed to open command file" << std::endl;
    } else {
        fprintf(fp_left, "run-direct");
        fprintf(fp_right, "run-direct");
    }
    fclose(fp_left);
    fclose(fp_right);

    _turnReached.store(false);
    _gyroTarget.store(angle);
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
    std::cout << "setting speed: " << speed << " of: " << motor << std::endl;

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
    std::cout << "watching gyro value: " << value << std::endl;
    if (state == MOVEMENT_TURNING) {
        if (value % 360 == _gyroTarget.load()) {
            _turnReached.store(true);
            setStop(motor_drive_left);
            setStop(motor_drive_right);
            state = MOVEMENT_IDLE;
        }
    }
        // _cv.notify_all();
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
    FILE* fp;
    fp = fopen((motor + "/command").c_str(), "w");

    if (fp == NULL) {
        std::cout << "failed to stop motor: " << motor << std::endl;
    } else
    {
        fprintf(fp, "stop");
        fclose(fp);
    }
    
}

void MotorController::stopAll()
{
    setStop(motor_drive_left);
    setStop(motor_drive_right);
}

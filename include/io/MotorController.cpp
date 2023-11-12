#include "MotorController.hpp"

SensorNotifier MotorController::_sensors{};
LocationTracker MotorController::_location{};
std::atomic<bool> MotorController::_turnReached;
std::atomic<bool> MotorController::_turningRight;
std::atomic<int> MotorController::_gyroTarget;
std::list<void(*)(int)>::iterator MotorController::_listener;
int MotorController::_turningGyroTargetOffset = 0;

MotorController::MotorController()
{
    _sensors.subscribeToAllChanges(MotorController::watchGyro);
    // readPorts();
}

double MotorController::shortestSignedDistanceBetweenCircularValues(double origin, double target){

  double signedDiff = 0.0;
  double raw_diff = origin > target ? origin - target : target - origin;
  double mod_diff = fmod(raw_diff, 360); //equates rollover values. E.g 0 == 360 degrees in circle

  if(mod_diff > (360/2) ){
    //There is a shorter path in opposite direction
    signedDiff = (360 - mod_diff);
    if(target>origin) signedDiff = signedDiff * -1;
  } else {
    signedDiff = mod_diff;
    if(origin>target) signedDiff = signedDiff * -1;
  }

  return signedDiff;

}

void MotorController::rotateTo(const int angle)
{
    state = MOVEMENT_TURNING;
    if (_location.getHeading() == angle) {
        state = MOVEMENT_IDLE;
        return;
    } else if (shortestSignedDistanceBetweenCircularValues(_location.getHeading(), angle) > 0) {
        setMotorSpeed(motor_drive_right, 80);
        setMotorSpeed(motor_drive_left, -80);
        _turningRight.store(false);
        _gyroTarget.store(angle - _turningGyroTargetOffset);
    } else {
        setMotorSpeed(motor_drive_right, -80);
        setMotorSpeed(motor_drive_left, 80);
        _turningRight.store(true);
        _gyroTarget.store(angle + _turningGyroTargetOffset);
    }

    _gyroTarget = _gyroTarget % 360;
    if (_gyroTarget < 0) {
        _gyroTarget += 360;
    }

    std::cout << "MotorController::rotateTo() using target: " << _gyroTarget << "\n";
    std::cout << "MotorController::rotateTo() using _turningGyroTargetOffset: " << _turningGyroTargetOffset << "\n";

#ifndef NO_MOTOR
    sendCommand(motor_drive_left, MotorCommandRunForever);
    sendCommand(motor_drive_right, MotorCommandRunForever);
#endif

    _turnReached.store(false);
    

    std::vector<std::string> right_state = getState(motor_drive_right);
    std::vector<std::string> left_state = getState(motor_drive_left);

    std::cout << "right state: " << "\n";
    for (std::string state : right_state) {
        std::cout << state;
    }
    std::cout << "\n";
    std::cout << "left state: " << "\n";
    for (std::string state : left_state) {
        std::cout << state;
    }
    std::cout << std::endl;

}

void MotorController::moveStraight(const int distance, bool reverse)
{
    state.store(MOVEMENT_MOVING);

    std::cerr << "moving motor pulses: " << distance << std::endl;

    if (reverse) {
        setPolarity(motor_drive_left, MotorPolarityInversed{});
        setPolarity(motor_drive_right, MotorPolarityInversed{});
    }

    setMotorSpeed(motor_drive_left, 300);
    setMotorSpeed(motor_drive_right, 300);


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

#ifndef NO_MOTOR
        fprintf(fp_left_com, "run-to-rel-pos");
        fprintf(fp_right_com, "run-to-rel-pos");
#endif
    }

    fclose(fp_left_pos);
    fclose(fp_right_pos);
    fclose(fp_left_com);
    fclose(fp_right_com);  

    _location.sendForwardMovementUpdate(distance);

    if (reverse) {
        setPolarity(motor_drive_left, MotorPolarityNormal{});
        setPolarity(motor_drive_right, MotorPolarityNormal{});
    }

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

void MotorController::watchGyro(std::map<subscriber_port, int> sensor_values, std::map<subscriber_port, int> prev_values)
{   
//     if (state == MOVEMENT_TURNING) {
//         std::cout << _location.getHeading() << std::endl;
//         if (_turningRight) {
//             if (_location.getHeading() <= _gyroTarget.load()) {
//                 _turnReached.store(true);
//                 setStop(motor_drive_left);
//                 setStop(motor_drive_right);
//                 std::cout << "Stopped turning at: " << _location.getHeading() << std::endl;
//                 _turningGyroTargetOffset = round((double)(_turningGyroTargetOffset + abs(_location.getHeading() - _gyroTarget)) / 2);
//                 state = MOVEMENT_IDLE;
//             }
//         } else {
//             if (_location.getHeading() >= _gyroTarget.load()) {
//                 _turnReached.store(true);
//                 setStop(motor_drive_left);
//                 setStop(motor_drive_right);
//                 std::cout << "Stopped turning at: " << _location.getHeading() << std::endl;
//                 _turningGyroTargetOffset = round((double)(_turningGyroTargetOffset + abs(_location.getHeading() - _gyroTarget)) / 2);
//                 state = MOVEMENT_IDLE;
//             }
//         }
//     }

    std::cout << "watchGyro::state: " << state << "\n";

    if (state == MOVEMENT_TURNING) {
        double distanceToTarget = shortestSignedDistanceBetweenCircularValues(_location.getHeading(), _gyroTarget);
        std::cout << "distance to target: " << distanceToTarget << "\n";
        std::cout << "offset: " << _turningGyroTargetOffset << "\n";
        std::cout << "watchGyro::_turningRight: " << _turningRight << "\n";
        if (
            (_turningRight && (distanceToTarget >= -_turningGyroTargetOffset))
            || (!_turningRight && (distanceToTarget >= _turningGyroTargetOffset))
        ) {
            setStop(motor_drive_left);
            setStop(motor_drive_right);
            _turnReached.store(true);
            std::cout << "Stopped turning at: " << _location.getHeading() << std::endl;
            // _turningGyroTargetOffset = round((double)(_turningGyroTargetOffset + shortestSignedDistanceBetweenCircularValues(_gyroTarget, _location.getHeading())) / 2);
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
    fp = fopen((motor + "/command").c_str(), "w");

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

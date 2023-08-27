#ifndef __MOTORCONTROLLER_H__
#define __MOTORCONTROLLER_H__

#include <fstream>
#include <queue>
#include <thread>
#include <iostream>
#include <atomic>
#include <mutex>
#include <cassert>
#include "DeviceCommunicator.hpp"
#include "SensorNotifier.hpp"
#include "../LocationTracker.hpp"

#define assertm(exp, msg) assert(((void)msg, exp))

struct MotorPolarityInversed{};
struct MotorPolarityNormal{};

enum MotorStopAction{
    MotorStopActionCoast = 0,
    MotorStopActionHold = 1,
    MotorStopActionBrake = 2
};

enum MotorCommand {
    MotorCommandStop = 0,
    MotorCommandReset = 1,
    MotorCommandRunToAbsPos = 2,
    MotorCommandRunDirect = 3,
    MotorCommandRunToRelPos = 4,
    MotorCommandRunTimed = 5,
    MotorCommandRunForever = 6,
};

enum MovementState {
    MOVEMENT_IDLE = 0,
    MOVEMENT_TURNING = 1,
    MOVEMENT_MOVING = 2
};

class MotorController : protected DeviceCommunicator {
    public:
        MotorController();

        static void exit();

        static void rotateTo(const int angle);
        static void moveStraight(const int distance);
        static void setMotorSpeed(const std::string motor, const int speed);
        static void watchGyro(const int value);

        static std::vector<std::string> getState(const std::string motor);
        
        static void setPolarity(const std::string motor, MotorPolarityInversed);
        static void setPolarity(const std::string motor, MotorPolarityNormal);

        static void setDutyCycle(const std::string motor, const int value);
        static void setStop(const std::string motor);
        static void setStopAction(const std::string motor, const MotorStopAction action);

        static void sendCommand(const std::string motor, const MotorCommand command);

        static void stopAll();
        
    protected:
        static SensorNotifier _sensors;
        static MovementState state;

    private:
        static std::thread _movement_thread;
        static LocationTracker _location;
        static std::atomic<bool> _turnReached;
        static std::mutex _mutex;
        static std::atomic<int> _gyroTarget;
};

#endif // __MOTORCONTROLLER_H__
#ifndef __MOTORCONTROLLER_H__
#define __MOTORCONTROLLER_H__

#include <fstream>
#include <queue>
#include <iostream>
#include <atomic>
#include <mutex>
#include <cassert>
#include "DeviceCommunicator.hpp"
#include "SensorNotifier.hpp"
#include "../LocationTracker.hpp"

#define assertm(exp, msg) assert(((void)msg, exp))
#define NO_MOTOR

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

class MotorController : protected DeviceCommunicator {
    public:
        MotorController();
        
        static double shortestSignedDistanceBetweenCircularValues(double origin, double target);

        static void exit();

        static void rotateTo(const int angle);
        static void moveStraight(const int distance, bool reverse = false);
        static void setMotorSpeed(const std::string motor, const int speed);
        static void watchGyro(std::map<subscriber_port, int> sensor_values, std::map<subscriber_port, int> prev_values);

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

    private:
        static LocationTracker _location;
        static std::atomic<bool> _turnReached;
        static std::atomic<bool> _turningRight;
        static std::mutex _mutex;
        static std::atomic<int> _gyroTarget;
        static std::list<void(*)(int)>::iterator _listener;
        static int _turningGyroTargetOffset;
};

#endif // __MOTORCONTROLLER_H__
#ifndef __MOTORCONTROLLER_H__
#define __MOTORCONTROLLER_H__

#include <fstream>
#include <queue>
#include <thread>
#include <iostream>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include "DeviceCommunicator.hpp"
#include "MovementAction.hpp"
#include "SensorNotifier.hpp"
#include "../LocationTracker.hpp"

struct MotorPolarityInversed{};
struct MotorPolarityNormal{};


enum MovementState {
    MOVEMENT_IDLE = 0,
    MOVEMENT_TURNING = 1,
    MOVEMENT_MOVING = 2
};

class MotorController : protected DeviceCommunicator {
    public:
        MotorController();

        static void updateMovement();  
        static void appendMovement(MovementAction action);
        static void rotateTo(const int angle);
        static void moveStraight(const int distance);
        static void setMotorSpeed(const std::string motor, const int speed);
        static void watchGyro(const int value);
        
        static void setPolarity(const std::string motor, MotorPolarityInversed);
        static void setPolarity(const std::string motor, MotorPolarityNormal);

        static void setDutyCycle(const std::string motor, const int value);

        static void setStop(const std::string motor);

        static void stopAll();
        
        static MovementState state;
        static SensorNotifier _sensors;

    private:

        static std::thread _movement_thread;
        static std::deque<MovementAction> _movement_queue;
        static LocationTracker _location;
        // static std::condition_variable _cv;
        static std::atomic<bool> _turnReached;
        static std::mutex _mutex;
        static std::atomic<int> _gyroTarget;
};

#endif // __MOTORCONTROLLER_H__
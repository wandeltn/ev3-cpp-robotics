#ifndef __MOTORCONTROLLER_H__
#define __MOTORCONTROLLER_H__

#include <fstream>
#include <queue>
#include <thread>
#include "DeviceCommunicator.hpp"
#include "MovementAction.hpp"

class MotorController : protected DeviceCommunicator{
    public:
        MotorController();

        static void updateMovement();
        static void appendMovement(MovementAction action);

    private:
        static std::thread _movement_thread;
        static std::queue<MovementAction> _movement_queue;
};

#endif // __MOTORCONTROLLER_H__
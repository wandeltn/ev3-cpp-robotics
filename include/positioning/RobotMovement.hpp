#ifndef __ROBOTMOVEMENT_H__
#define __ROBOTMOVEMENT_H__

#include <deque>
#include <math.h>
#include "../io/MotorController.hpp"
#include "Line.hpp"

class RobotMovement : protected MotorController, protected LocationTracker {
    public:    
        RobotMovement();
        ~RobotMovement();

        static void updateMovement();

        static void goToLocation(MovementAction action);
        static void goToLocation(std::vector<MovementAction> actions);
        static void goToLocation(std::deque<MovementAction> actions);

        static void waitForThreadStop();

        static void stopAll();

    private:
        static std::thread _movementThread;
        static std::atomic<bool> _runMovementThread;
        static std::atomic<bool> _threadRunning;
};

#endif // __ROBOTMOVEMENT_H__
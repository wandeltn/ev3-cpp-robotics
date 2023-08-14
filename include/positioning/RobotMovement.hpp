#ifndef __ROBOTMOVEMENT_H__
#define __ROBOTMOVEMENT_H__

#include <deque>
#include <math.h>
#include "../io/MotorController.hpp"
#include "Line.hpp"

struct MovementAction {
    MovementAction(int distance, int direction, int speed);
    MovementAction(Line line, int speed);
    MovementAction();

    int distance;
    int direction;
    int speed;
};

class RobotMovement : private MotorController {
    public:    
        RobotMovement();
        ~RobotMovement();

        static void updateMovement();

        static void goToLocation(MovementAction action);
        static void goToLocation(std::vector<MovementAction> actions);
        static void goToLocation(std::deque<MovementAction> actions);

        static void stopAll();

    private:
        static std::deque<MovementAction> _pendingActions;
        static std::thread _movementThread;
        static std::atomic<bool> _runMovementThread;
};

#endif // __ROBOTMOVEMENT_H__
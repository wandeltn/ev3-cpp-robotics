#ifndef __ROBOTMOVEMENT_H__
#define __ROBOTMOVEMENT_H__

#include <deque>
#include <math.h>
#include "../io/MotorController.hpp"
#include "Line.hpp"
#include "../display/Window.hpp"
#include "../http-server/Server.hpp"

class RobotMovement : public MotorController, public LocationTracker {
    public:    
        RobotMovement();
        ~RobotMovement();

        static void updateMovement();

        static void goToLocation(MovementAction action);
        static void goToLocation(std::vector<MovementAction> actions);
        static void goToLocation(std::deque<MovementAction> actions);

        static void finishQueue();

        static void stopAll();

    private:
        static bool actionAvailable;
        static bool actionCompleted;
        static bool currentlyTurning;


};

#endif // __ROBOTMOVEMENT_H__
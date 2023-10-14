#include "RobotMovement.hpp"

bool RobotMovement::currentlyTurning = true;
bool RobotMovement::actionCompleted = false;
bool RobotMovement::actionAvailable = false;
MovementAction RobotMovement::currentAction;


RobotMovement::RobotMovement() : LocationTracker(65, 185)
{
    setStopAction(motor_drive_left, MotorStopActionHold);
    setStopAction(motor_drive_right, MotorStopActionHold);
    _pendingActions.clear();
}

RobotMovement::~RobotMovement()
{
}

void RobotMovement::updateMovement()
{
    while (
        actionAvailable  
        || _pendingActions.size()
    )
    {
        if (_pendingActions.size() && !actionAvailable)
        {
            // std::cout << "getting new aciton" << std::endl;
            currentAction = _pendingActions.front();
            _pendingActions.pop_front();
            actionAvailable = true;
        }

        std::vector<std::string> state = getState(motor_drive_left);
        if (std::find(state.begin(), state.end(), "running") == state.end())
        {
            state = getState(motor_drive_right);
            if (std::find(state.begin(), state.end(), "running") == state.end())
            {
                if (currentlyTurning)
                {
                    std::cout << "targetAngle: " << currentAction.direction << std::endl;
                    rotateTo(currentAction.direction);
                    currentlyTurning = false;
                }
                else if (!actionCompleted)
                {
                    std::cout << "moving forward: " << currentAction.distance << std::endl;
                    moveStraight(MmToMotorPulses(currentAction.distance));
                    actionCompleted = true;
                }
                else
                {
                    if (_pendingActions.size())
                    {
                        // std::cout << "resetting action state" << std::endl;
                        currentlyTurning = true;
                        actionCompleted = false;
                    } else {
                        currentlyTurning = false;
                        actionCompleted = true;
                    }
                    actionAvailable = false;
                }
            }
        }
        _sensors.Dispatcher();
    }
}

void RobotMovement::goToLocation(MovementAction action)
{
    _pendingActions.push_back(action);
}

void RobotMovement::goToLocation(std::vector<MovementAction> actions)
{
    _pendingActions.insert(_pendingActions.end(), actions.begin(), actions.end());
}

void RobotMovement::goToLocation(std::deque<MovementAction> actions)
{
    _pendingActions.insert(_pendingActions.end(), actions.begin(), actions.end());
}

void RobotMovement::finishQueue()
{
    for (int i = 0; i <= 5; i++) {
        _sensors.Dispatcher(false);
    }
    updateMovement();
}

void RobotMovement::stopAll()
{
    MotorController::stopAll();
}

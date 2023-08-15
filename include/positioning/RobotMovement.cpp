#include "RobotMovement.hpp"

MovementAction::MovementAction(int distance, int direction, int speed)
{
    this->distance = distance;
    this->direction = direction;
    this->speed = speed;
}

MovementAction::MovementAction(Line line, int speed)
{
    this->distance = line.getLength();
    direction = line.getAngle();
    this->speed = speed;

    std::cout << this->direction << std::endl;
}

MovementAction::MovementAction()
{
}

std::deque<MovementAction> RobotMovement::_pendingActions{};
std::thread RobotMovement::_movementThread;
std::atomic<bool> RobotMovement::_runMovementThread;
std::atomic<bool> RobotMovement::_threadRunning;

RobotMovement::RobotMovement()
{
    setStopAction(motor_drive_left, MotorStopActionHold);
    setStopAction(motor_drive_right, MotorStopActionHold);
    _pendingActions.clear();
    _runMovementThread.store(true);
    _movementThread = std::thread{updateMovement};
    _movementThread.detach();
}

RobotMovement::~RobotMovement()
{
    _runMovementThread.store(false);
}

void RobotMovement::updateMovement()
{
    using namespace std::chrono_literals;
    _threadRunning.store(true);
    bool currentlyTurning = true;
    bool actionCompleted = false;
    bool actionAvailable = false;
    MovementAction currentAction;
    while (
        _runMovementThread || 
        actionAvailable ||
        _pendingActions.size()
    )
    {
        std::this_thread::sleep_for(500ms);
        if (_pendingActions.size() && !actionAvailable)
        {
            std::cout << "getting new aciton" << std::endl;
            currentAction = _pendingActions.front();
            _pendingActions.pop_front();
            actionAvailable = true;
        }
        else if (actionAvailable) {
        }
        else
        {
            _sensors.stopDispatcher();
            continue;
        }

        _sensors.startDispatcher();
        std::vector<std::string> state = getState(motor_drive_left);
        if (std::find(state.begin(), state.end(), "running") == state.end())
        {
            std::vector<std::string> state = getState(motor_drive_right);
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
                    moveStraight(CmToMotorPulses(currentAction.distance));
                    actionCompleted = true;
                }
                else
                {
                    if (_pendingActions.size())
                    {
                        std::cout << "resetting action state" << std::endl;
                        currentlyTurning = true;
                        actionCompleted = false;
                        actionAvailable = false;
                    }
                }
            }
        }
    }
    _threadRunning.store(false);
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

void RobotMovement::waitForThreadStop()
{
    using namespace std::chrono_literals;
    _runMovementThread.store(false);
    while (_threadRunning)
    {
        std::this_thread::sleep_for(500ms);
    }
    
}

void RobotMovement::stopAll()
{
    MotorController::stopAll();
}

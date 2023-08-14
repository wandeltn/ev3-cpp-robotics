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
    this->direction = line.getAngle();
    this->speed = speed;   
}

MovementAction::MovementAction()
{

}

std::deque<MovementAction> RobotMovement::_pendingActions{};
std::thread RobotMovement::_movementThread;
std::atomic<bool> RobotMovement::_runMovementThread;

RobotMovement::RobotMovement()
{
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
    bool currentlyTurning = true;
    bool actionCompleted = false;
    MovementAction currentAction = _pendingActions.front();
    _pendingActions.pop_front();
    while (_runMovementThread)
    {
        std::this_thread::sleep_for(500ms);

        std::vector<std::string> state = getState(motor_drive_left);
        if (std::find(state.begin(), state.end(), "running") == state.end()) {
            std::vector<std::string> state = getState(motor_drive_right);
            if (std::find(state.begin(), state.end(), "running") == state.end()) {
                if (currentlyTurning) {
                    rotateTo(currentAction.direction);
                    currentlyTurning = false;
                } 
                else if (!actionCompleted) {
                    moveStraight(currentAction.distance);
                    actionCompleted = true;
                } 
                else
                {
                    if (_pendingActions.size()) {
                        currentAction = _pendingActions.front();
                        _pendingActions.pop_front();
                        currentlyTurning = true;
                        actionCompleted = false;
                    }
                }
            } 
        } 
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

void RobotMovement::stopAll()
{
    MotorController::stopAll();
}

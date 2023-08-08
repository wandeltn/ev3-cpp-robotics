#include "MotorController.hpp"

std::thread MotorController::_movement_thread;
std::queue<MovementAction> MotorController::_movement_queue = std::queue<MovementAction>{};

MotorController::MotorController()
{
    _movement_thread = std::thread{updateMovement};   
}

void MotorController::updateMovement()
{
    
}

void MotorController::appendMovement(MovementAction action)
{
    _movement_queue.push(action);
}



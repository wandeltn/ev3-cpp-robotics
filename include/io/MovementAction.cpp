#include "MovementAction.hpp"

MovementAction::MovementAction(int heading, int distance)
{
    _heading = heading;
    _distance = distance;
}

int MovementAction::getHeading()
{
    return _heading;
}


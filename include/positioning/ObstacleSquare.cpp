#include "ObstacleSquare.hpp"
#include "Line.hpp"

ObstacleSquare::ObstacleSquare(Vector upperLeft, Vector lowerRight)
{
    _upperLeft = upperLeft;
    _lowerRight = lowerRight;    
}

bool ObstacleSquare::checkForIntersect(const Line& line)
{
    const Line _leftBound{_upperLeft, {_upperLeft.x, _lowerRight.y}};
    const Line _rightBound{_lowerRight, {_lowerRight.x, _upperLeft.y}};
    const Line _upperBound{_upperLeft, {_lowerRight.x, _upperLeft.y}};
    const Line _lowerBound{_lowerRight, {_upperLeft.x, _lowerRight.y}};
    if (
        line.checkForIntersect(_leftBound) ||
        line.checkForIntersect(_rightBound) ||
        line.checkForIntersect(_upperBound) ||
        line.checkForIntersect(_lowerBound)
        ) {
        return true;
    }
    return false;
}

void ObstacleSquare::paint(std::shared_ptr<Window> window)
{
    window->drawRect(_upperLeft, _lowerRight, DISPLAY_DARK);
}

std::string ObstacleSquare::writeOut()
{
    return std::string(
        "SQ:" + 
        std::to_string(_upperLeft.x) + 
        "/" + 
        std::to_string(_upperLeft.y) +
        ";" + 
        std::to_string(_lowerRight.x) + 
        "/" + 
        std::to_string(_lowerRight.y)
    );
}

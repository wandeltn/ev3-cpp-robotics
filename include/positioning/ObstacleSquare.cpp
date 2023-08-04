#include "ObstacleSquare.hpp"

ObstacleSquare::ObstacleSquare(Vector upperLeft, Vector lowerRight)
{
    _upperLeft = upperLeft;
    _lowerRight = lowerRight;    
}

bool ObstacleSquare::checkForIntersect(const Line& line)
{
    if (
        (line.start_point.x >= _upperLeft.x && line.start_point.x <= _lowerRight.x) ||
        (line.start_point.y <= _upperLeft.y && line.start_point.y >= _lowerRight.y) ||
        (line.end_point.x >= _upperLeft.x && line.end_point.x <= _lowerRight.x) ||
        (line.end_point.y <= _upperLeft.y && line.end_point.y >= _lowerRight.y)
        ) {
        return true;
    }
    return false;
}



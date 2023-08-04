#include "ObstacleLine.hpp"

ObstacleLine::ObstacleLine(Line line)
{
    _obstacle = line;
}

bool ObstacleLine::checkForIntersect(const Line& line)
{
    return _obstacle.checkForIntersect(line);
}
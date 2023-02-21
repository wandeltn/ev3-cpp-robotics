#include "Vector2.hpp"
#include <cmath>

Vector2::Vector2(int_fast8_t positionX, int_fast8_t positionY)
{
    x = positionX;
    y = positionY;
}

double Vector2::getDistanceToPoint(Vector2 point)
{
    return sqrt(((x - point.x) << 1) + ((y - point.y) << 1));
}


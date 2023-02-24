#include "Vector2.hpp"
#include <cmath>
#include <iostream>


Vector2::Vector2()
{
    std::cerr << "Default constructor of Vector2" << std::endl;
}
Vector2::Vector2(double positionX, double positionY)
{
    x = positionX;
    y = positionY;
}

double Vector2::getDistanceToPoint(Vector2 point)
{
    return sqrt(pow((double)(x - point.x), 2.0) + pow((double)(y - point.y), 2.0));
}

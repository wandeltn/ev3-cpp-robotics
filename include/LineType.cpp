#include "LineType.hpp"
#include <iostream>

LineType::LineType(Vector2 start, Vector2 end)
{
        _start = start;
    _end = end;
}

LineType::LineType(
            double start_x,
            double start_y,
            double end_x,
            double end_y)
{
    _start = Vector2{start_x, start_y};
    _end = Vector2{end_x, end_y};

    std::cout << "x1: " << _start.x << std::endl; 
    std::cout << "x2: " << _end.x << std::endl;
    std::cout << "y1: " << _start.y << std::endl;
    std::cout << "y2: " << _end.y << std::endl;
}

bool LineType::checkForIntersect(LineType line)
{
    double t_denominator = (_start.x - _end.x) * (line._start.y - line._end.y) - (_start.y - _end.y) * (line._start.x - line._end.x);
    double t_numerator = (_start.x - line._start.x) * (line._start.y - line._end.y) - (_start.y - line._start.y) * (line._start.x - line._end.x);
    double t = t_numerator / t_denominator;

    double u_denominator = (_start.x - _end.x) * (line._start.y - line._end.y) - (_start.y - _end.y) * (line._start.x - line._end.x);
    double u_numerator = (_start.x - line._start.x) * (_start.y - _end.y) - (_start.y - line._start.y) * (_start.x - _end.y);
    double u = u_numerator / u_denominator;

    if (u <= 1 && u >= 0 && t <= 1 && t >= 0) {
        return true;
    } else {
        return false;
    }
}


Vector2 LineType::getIntersect(LineType line)
{
    // link: https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
    double point_denominator = (_start.x - _end.x) * (line._start.y - line._end.y) - (_start.y - _end.y) * (line._start.x - line._end.x);
    double point_x_numerator = (_start.x * _end.y - _start.y * _end.x) * (line._start.x - line._end.x) - (_start.x - _end.x) * (line._start.x * line._end.y - line._start.y * line._end.x);
    double point_y_numerator = (_start.x * _end.y - _start.y * _end.x) * (line._start.y - line._end.y) - (_start.y - _end.y) * (line._start.x * line._end.y - line._start.y * line._end.x);
    double point_x = point_x_numerator / point_denominator;
    double point_y = point_y_numerator / point_denominator;
    
    std::cout << point_x << " / " << point_y << std::endl;
    return Vector2{point_x, point_y};
}

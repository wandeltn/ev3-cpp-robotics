#include "LineType.hpp"
#include <iostream>

LineType::LineType(Vector2 start, Vector2 end)
{
    _start = start;
    _end = end;
}

LineType::LineType(
            int_fast8_t start_x,
            int_fast8_t start_y,
            int_fast8_t end_x,
            int_fast8_t end_y)
{
    _start = Vector2{start_x, start_y};
    _end = Vector2{end_x, end_y};
}

bool LineType::checkForIntersect(LineType line)
{
    // link: https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
    double point_x_denominator = (_start.x - _end.x) * (line._start.y - line._end.y) - (_start.y - _end.y) * (line._start.x - line._end.x);
    double point_x_numerator = (_start.x * _end.y - _start.y * _end.x) * (line._start.x - line._end.x) - (_start.x - _end.x) * (line._start.x * line._end.y - line._start.y * line._end.x);

    double point_x = point_x_numerator / point_x_denominator;

    std::cout << point_x << std::endl;
}

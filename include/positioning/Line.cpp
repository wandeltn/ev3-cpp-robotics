#include "Line.hpp"


Line::Line(Vector start, Vector end): start_point{start}, end_point{end}
{
    direction_vector = end - start;
    double length = direction_vector ^ direction_vector;
    direction_vector = direction_vector / length;
}

Vector Line::getIntersect(Line line)
{
    double lambda = (start_point.y * line.direction_vector.x - line.start_point.y * line.direction_vector.x - start_point.x * line.direction_vector.y + line.start_point.x * line.direction_vector.y) /
        (line.direction_vector.x * line.direction_vector.y - direction_vector.y * line.direction_vector.x);
    double intersect_x = start_point.x + lambda * direction_vector.x;
    double intersect_y = start_point.y + lambda * direction_vector.y;

    return Vector(intersect_x, intersect_y);
}

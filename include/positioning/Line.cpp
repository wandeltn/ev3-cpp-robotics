#include <limits>
#include "Line.hpp"


Line::Line(Vector start, Vector end): start_point{start}, end_point{end}
{
    direction_vector = end - start;
    _length = direction_vector ^ direction_vector;
    direction_vector = direction_vector / _length;
}

Vector Line::getIntersect(Line line)
{
    double lambda = (start_point.y * line.direction_vector.x - line.start_point.y * line.direction_vector.x - start_point.x * line.direction_vector.y + line.start_point.x * line.direction_vector.y) /
        (line.direction_vector.x * line.direction_vector.y - direction_vector.y * line.direction_vector.x);
    double intersect_x = start_point.x + lambda * direction_vector.x;
    double intersect_y = start_point.y + lambda * direction_vector.y;
    if (lambda < 0 || lambda > _length) {
        return Vector(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
    }
    // check lambda of second line
    lambda = (intersect_y - line.start_point.y) / line.direction_vector.y; 
    if (lambda < 0 || lambda > _length) {
        // direction vector may be 0 in y axis
        lambda = (intersect_x - line.start_point.x) / line.direction_vector.x; 
        if (lambda < 0 || lambda > _length) {
            return Vector(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
        }
    }
    return Vector(intersect_x, intersect_y);
}

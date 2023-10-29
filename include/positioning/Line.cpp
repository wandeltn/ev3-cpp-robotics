#include <limits>
#include "Line.hpp"

Line::Line()
{
    std::cerr << "No Vector provided" << std::endl;
}

Line::Line(Vector start, Vector end): start_point{start}, end_point{end}
{
    this->direction_vector = end - start;
    // std::cout << "Line::Line() direction_vector: " << direction_vector << "\n";
    // std::cout << "Line::Line() end: " << end << "\n";
    // std::cout << "Line::Line() start: " << start << std::endl;
    _length = direction_vector ^ direction_vector;
    if (_length != 0) {
    }
        direction_vector = direction_vector / _length;
    // std::cout << "Line::Line() _length: " << _length << std::endl;
    // std::cout << "Line::Line() new_direction_vector: " << direction_vector << "\n";
}

Vector Line::getIntersect(const Line& line)
{
    double lambda1 = (start_point.y * line.direction_vector.x - line.start_point.y * line.direction_vector.x - start_point.x * line.direction_vector.y + line.start_point.x * line.direction_vector.y) /
        (line.direction_vector.x * line.direction_vector.y - direction_vector.y * line.direction_vector.x);
    double intersect_x = start_point.x + lambda1 * direction_vector.x;
    double intersect_y = start_point.y + lambda1 * direction_vector.y;
    if (lambda1 < 0 || lambda1 > _length) {
        // return Vector(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    }
    // check lambda of second line
    double lambda2 = (intersect_y - line.start_point.y) / line.direction_vector.y; 
    if ((lambda2 < 0 || lambda2 > line._length) && (lambda1 < 0 || lambda1 > _length)) {
        // direction vector may be 0 in y axis
        double lambda2 = (intersect_x - line.start_point.x) / line.direction_vector.x; 
        if (lambda2 < 0 || lambda2 > _length) {
            return Vector(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
        }
    }
    return Vector(intersect_x, intersect_y);
}

bool Line::checkForIntersect(const Line& line) const
{
    //https://bryceboe.com/2006/10/23/line-segment-intersection-algorithm/
    
    return counterclockwise(start_point, line.start_point, line.end_point) != 
            counterclockwise(end_point,line.start_point,line.end_point) && 
            counterclockwise(start_point,end_point,line.start_point) != 
            counterclockwise(start_point,end_point,line.end_point);
    // Vector intersect = getIntersect(line);
    // if ((intersect.x != std::numeric_limits<double>::max()) || (intersect.y != std::numeric_limits<double>::max())) {
    //     return true;
    // }
    // return false;
}

double Line::getLength() const
{
    double start_at_zero_x = end_point.x - start_point.x;
    double start_at_zero_y = end_point.y - start_point.y;
    return sqrt(pow(start_at_zero_x, 2) + pow(start_at_zero_y, 2)); 
    // return Vector(start_at_zero_x, start_at_zero_y) ^ Vector(start_at_zero_x, start_at_zero_y);
}

double Line::getAngle() const
{
    double result = atan2(direction_vector.y, direction_vector.x);
    std::cout << "getAngle() directionVector:" << direction_vector << "\n";
    std::cout << "getAngle() atan2:" << result << "\n";
    result = result * 180 / M_PI;
    if (result < 0) {
        result = 360 + result;
    }
    // std::cout << "dir_x: " << direction_vector.x << " dir_y: " << direction_vector.y << std::endl;
    std::cout << "getAngle(): " << result << std::endl;
    assertm((result <= 360), "Angle out of range in Line::getAngle");
    return result;
}

bool Line::counterclockwise(Vector A, Vector B, Vector C) const
{
    return (C.y-A.y)*(B.x-A.x) > (B.y-A.y)*(C.x-A.x);
}

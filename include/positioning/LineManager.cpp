#include "LineManager.hpp"

std::vector<Line> LineManager::_fieldLines{};

LineManager::LineManager() 
{

}

LineManager::~LineManager()
{

}

std::vector<Vector> LineManager::getIntersect(Line line)
{
    std::vector<Vector> intersections{};
    for (Line fieldLine : _fieldLines) {
        Vector intersect = fieldLine.getIntersect(line);
        if (
            intersect.x != std::numeric_limits<double>::infinity() &&
            intersect.y != std::numeric_limits<double>::infinity()
        ) {
            intersections.push_back(intersect);
        }
    }
    return intersections;
}
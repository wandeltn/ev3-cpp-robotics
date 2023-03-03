#include "LineIntersect.hpp"
#include "LineType.hpp"
#include <vector>

LineIntersect::LineIntersect()
{
    intersectLines.push_back(LineType{10,10,20,20});
    intersectLines.push_back(LineType{25,20,30,30});
}

std::vector<Vector2> LineIntersect::checkForIntersects(LineType travelPath)
{
    std::vector<Vector2> resultVector;
    for (LineType intersectLine : intersectLines) {
        if (travelPath.checkForIntersect(intersectLine)) {
            resultVector.push_back(travelPath.getIntersect(intersectLine));
        }
    }
    return resultVector;
}

std::vector<LineType> LineIntersect::intersectLines;

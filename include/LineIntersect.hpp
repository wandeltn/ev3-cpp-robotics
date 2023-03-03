#ifndef __LINEINTERSECT_H__
#define __LINEINTERSECT_H__

#include "Vector2.hpp"
#include "LineType.hpp"

class LineIntersect {
    public:
        LineIntersect();

        std::vector<Vector2> checkForIntersects(LineType travelPath);

    private:
        static std::vector<LineType> intersectLines;        
};

#endif // __LINEINTERSECT_H__
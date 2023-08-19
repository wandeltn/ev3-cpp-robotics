#ifndef __LINEMANAGER_H__
#define __LINEMANAGER_H__

#include <vector>
#include "Line.hpp"
#include "Vector.hpp"

class LineManager {
    public:
        LineManager();
        ~LineManager();

        static std::vector<Vector> getIntersect(Line line);

    private:
        static std::vector<Line> _fieldLines;
};

#endif
#ifndef __LINE_H__
#define __LINE_H__

#include "Vector.hpp"
#include <limits>

class Line {
    public:
        Line(Vector start, Vector end);
        Line();

        Vector getIntersect(const Line& line);
        bool checkForIntersect(const Line& line);

        const Vector start_point;
        const Vector end_point;
        Vector direction_vector;
        
    private:
};

#endif // __LINE_H__
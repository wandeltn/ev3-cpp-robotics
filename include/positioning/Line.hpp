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
        
        Line& operator=(const Line& line) = default;

        Vector start_point;
        Vector end_point;
        Vector direction_vector;
        
    private:
        double _length;
};

#endif // __LINE_H__
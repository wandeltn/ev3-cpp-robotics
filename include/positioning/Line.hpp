#ifndef __LINE_H__
#define __LINE_H__

#include "Vector.hpp"

class Line {
    public:
        Line(Vector start, Vector end);

        Vector getIntersect(Line);

        const Vector start_point;
        const Vector end_point;
        Vector direction_vector;
        
    private:
};

#endif // __LINE_H__
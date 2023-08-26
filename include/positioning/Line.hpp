#ifndef __LINE_H__
#define __LINE_H__

#include "Vector.hpp"
#include <limits>
#include <cassert>

#define assertm(exp, msg) assert(((void)msg, exp))

class Line {
    public:
        Line(Vector start, Vector end);
        Line();

        Vector getIntersect(const Line& line);
        bool checkForIntersect(const Line& line) const;
        double getLength() const;
        double getAngle() const;

        Line& operator=(const Line& line) = default;

        Vector start_point;
        Vector end_point;
        Vector direction_vector;
        
    private:
        double _length;
        bool counterclockwise(Vector A, Vector B, Vector C) const;
};

#endif // __LINE_H__
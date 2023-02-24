#ifndef __LINETYPE_H__
#define __LINETYPE_H__

#include "Vector2.hpp"

class LineType {
    public:
        LineType(Vector2 start, Vector2 end);
        LineType(
            double start_x,
            double start_y,
            double end_x,
            double end_y
        );
        bool checkForIntersect(LineType line);
        Vector2 getIntersect(LineType line);

    private:
        Vector2 _start;
        Vector2 _end;
};

#endif // __LINETYPE_H__
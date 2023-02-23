#ifndef __LINETYPE_H__
#define __LINETYPE_H__

#include "Vector2.hpp"

class LineType {
    public:
        LineType(Vector2 start, Vector2 end);
        LineType(
            int_fast8_t start_x,
            int_fast8_t start_y,
            int_fast8_t end_x,
            int_fast8_t end_y
        );
        bool checkForIntersect(LineType line);

    private:
        Vector2 _start;
        Vector2 _end;
};

#endif // __LINETYPE_H__
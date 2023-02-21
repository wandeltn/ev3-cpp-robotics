#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include <stdint.h>

class Vector2 {
    public: 
        Vector2(int_fast8_t positionX, int_fast8_t positionY);
        double getDistanceToPoint(Vector2 point);

        int_fast8_t x;
        int_fast8_t y;
};

#endif // __VECTOR2_H__
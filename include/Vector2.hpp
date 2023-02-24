#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include <stdint.h>

class Vector2 {
    public: 
        Vector2();
        Vector2(double positionX, double positionY);
        double getDistanceToPoint(Vector2 point);

        int x;
        int y;
};

#endif // __VECTOR2_H__
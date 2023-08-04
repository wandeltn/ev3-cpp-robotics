#ifndef __BASEOBSTACLE_H__
#define __BASEOBSTACLE_H__

#include "Line.hpp"

class BaseObstacle {
    public: 
        BaseObstacle() = default;
        virtual bool checkForIntersect(const Line& line) = 0;
};

#endif // __BASEOBSTACLE_H__
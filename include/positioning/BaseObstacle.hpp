#ifndef __BASEOBSTACLE_H__
#define __BASEOBSTACLE_H__

#include <memory>
#include "Line.hpp"
#include "../display/Window.hpp"


class BaseObstacle {
    public: 
        BaseObstacle() = default;
        virtual bool checkForIntersect(const Line& line) = 0;
        virtual void paint(std::shared_ptr<Window> window) = 0;
};

#endif // __BASEOBSTACLE_H__
#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "DriveControl.hpp"
#include "SensorControl.hpp"
#include "Vector2.hpp"
#include "LineIntersect.hpp"

class Robot: public DriveControl {
    public:
        Robot();
        void moveToPosition(Vector2 destination);
        void moveToPosition(double x, double y);

    private:
        static SensorControl sensors;
        static LineIntersect intersections;
        static Vector2 _current_position;
        static int_fast8_t _current_heading;
};

#endif // __ROBOT_H__
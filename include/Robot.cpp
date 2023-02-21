#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "DriveControl.hpp"
#include "SensorControl.hpp"
#include "Vector2.hpp"

class Robot: public DriveControl {
    public:
        Robot();
        void moveToPosition(Vector2 destination);

    private:
        static SensorControl sensors;
        static Vector2 _current_position;
        static int_fast8_t _current_heading;
};

#endif // __ROBOT_H__
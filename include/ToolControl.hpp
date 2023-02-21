#ifndef __TOOLCONTROL_H__
#define __TOOLCONTROL_H__

#include "../ev3dev.hpp"
#include <stdint.h>

enum GearNumber {
    GEAR_0 = 0,
    GEAR_1 = 1,
    GEAR_2 = 2,
    GEAR_3 = 3
};

class ToolControl {
    public:
        ToolControl();
        void setGear(GearNumber newGear);

    private:
        static GearNumber _current_gear;
        static ev3dev::medium_motor _driver_motor;
        static ev3dev::medium_motor _gear_motor;
};

#endif // __TOOLCONTROL_H__
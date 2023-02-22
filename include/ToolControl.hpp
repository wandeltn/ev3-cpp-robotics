#ifndef __TOOLCONTROL_H__
#define __TOOLCONTROL_H__

#include "../ev3dev.hpp"
#include <stdint.h>

enum GearNumber {
    GEAR_0 = 0,
    GEAR_1 = 100,
    GEAR_2 = 200,
    GEAR_3 = 300
};

enum ToolPosition {
    TOOL_POSITION_DOWN =    0,
    TOOL_POSITION_UP =      300
};


class ToolControl {
    public:
        ToolControl();
        void setGear(GearNumber newGear);
        void raiseTool(int position);
        void setToolPosition(ToolPosition newPosition);

    private:
        static GearNumber _current_gear;
        static ev3dev::medium_motor _driver_motor;
        static ev3dev::medium_motor _gear_motor;
};

#endif // __TOOLCONTROL_H__
#include "ToolControl.hpp"


void ToolControl::setGear(GearNumber newGear)
{
    
}


GearNumber ToolControl::_current_gear = 0;
ev3dev::medium_motor ToolControl::_driver_motor = ev3dev::medium_motor{ev3dev::OUTPUT_C};
ev3dev::medium_motor ToolControl::_gear_motor = ev3dev::medium_motor{ev3dev::OUTPUT_D};
#include "ToolControl.hpp"
#include <iostream>

ToolControl::ToolControl()
{

}

void ToolControl::setGear(GearNumber newGear)
{
    while(
        _driver_motor.state().count("running") >= 1 ||
        _gear_motor.state().count("running") >= 1) {
        continue;
    }
    _gear_motor.set_stop_action("hold");
    _gear_motor.set_position_sp(newGear);
    _gear_motor.set_speed_sp(_gear_motor.max_speed()).run_to_abs_pos();
}

void ToolControl::raiseTool(int position)
{
    while(
        _driver_motor.state().count("running") >= 1 ||
        _gear_motor.state().count("running") >= 1) {
        continue;
    }
    _driver_motor.set_stop_action("hold");
    _driver_motor.set_position_sp(position);
    _driver_motor.set_speed_sp(_driver_motor.max_speed()).run_to_abs_pos();
}

void ToolControl::setToolPosition(ToolPosition newPosition)
{
    while(
        _driver_motor.state().count("running") >= 1 ||
        _gear_motor.state().count("running") >= 1) {
        continue;
    }
    _driver_motor.set_stop_action("hold");
    _driver_motor.set_position_sp(newPosition);
    _driver_motor.set_speed_sp(_driver_motor.max_speed()).run_to_abs_pos();
}


GearNumber ToolControl::_current_gear = GEAR_0;
ev3dev::medium_motor ToolControl::_driver_motor = ev3dev::medium_motor{ev3dev::OUTPUT_D};
ev3dev::medium_motor ToolControl::_gear_motor = ev3dev::medium_motor{ev3dev::OUTPUT_C};

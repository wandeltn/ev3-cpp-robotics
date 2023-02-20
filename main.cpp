

/*
 * Copyright (c) 2014 - Franz Detro
 *
 * Some real world test program for motor control
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "ev3dev.hpp"

#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>

#ifndef NO_LINUX_HEADERS
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#define KEY_RELEASE 0
#define KEY_PRESS   1
#define KEY_REPEAT  2
#endif

using namespace std;
using namespace ev3dev;

class control
{
public:
  control();
  ~control();

  void drive(int speed, int time=0);
  void turn(int direction);
  void stop();
  void reset();

  bool initialized() const;

  void terminate_on_key();
  void panic_if_touched();

  void remote_loop();
  void drive_autonomously();

  void terminate() { _terminate = true; }

protected:
  large_motor     _motor_left;
  large_motor     _motor_right;

  enum state
  {
    state_idle,
    state_driving,
    state_turning
  };

  state _state;
  bool  _terminate;
};

control::control() :
  _motor_left(OUTPUT_B),
  _motor_right(OUTPUT_C),
  _state(state_idle),
  _terminate(false)
{
}

control::~control()
{
  reset();
}

void control::drive(int speed, int time)
{
  _motor_left.set_position_sp(360);

  _motor_right.set_position_sp(5);

  _state = state_driving;

  if (time > 0)
  {
    _motor_left .run_to_rel_pos();
    _motor_right.run_to_rel_pos();

    while (_motor_left.state().count("running") || _motor_right.state().count("running"))
      this_thread::sleep_for(chrono::milliseconds(10));

    _state = state_idle;
  }
  else
  {
    _motor_left.run_forever();
    _motor_right.run_forever();
  }
}

void control::turn(int direction)
{
  if (_state != state_idle)
    stop();

  if (direction == 0)
    return;

  _state = state_turning;

  _motor_left. set_position_sp( direction).set_speed_sp(500).run_to_rel_pos();
  _motor_right.set_position_sp(-direction).set_speed_sp(500).run_to_rel_pos();

  while (_motor_left.state().count("running") || _motor_right.state().count("running"))
    this_thread::sleep_for(chrono::milliseconds(10));

  _state = state_idle;
}

void control::stop()
{
  _motor_left .stop();
  _motor_right.stop();

  _state = state_idle;
}

void control::reset()
{
  if (_motor_left.connected())
    _motor_left.reset();

  if (_motor_right.connected())
    _motor_right.reset();

  _state = state_idle;
}

bool control::initialized() const
{
  return (_motor_left .connected() &&
          _motor_right.connected());
}

void control::terminate_on_key()
{
 #ifndef NO_LINUX_HEADERS

 #endif
}

void control::panic_if_touched()
{
}

void control::remote_loop()
{

  const int speed = 700;
  const int ninety_degrees = 260;


  reset();
}

void control::drive_autonomously()
{
    drive(750);
    this_thread::sleep_for(chrono::milliseconds(10));
}

int main()
{
  control c;

  if (c.initialized())
  {
    c.terminate_on_key(); // we terminate if a button is pressed
    c.panic_if_touched(); // we panic if the touch sensor is triggered

  // change mode to 1 to get IR remote mode
    c.drive(0, 3000);
    c.turn(1);
    c.drive(100, 100);
  }
  else
  {
    cout << "you need to connect an infrared sensor and large motors to ports B and C!" << endl;
    return 1;
  }

  return 0;
}
#ifndef __LOCATIONTRACKER_H__
#define __LOCATIONTRACKER_H__

#include <map>
#include <iostream>
#include <math.h>
#include "io/SensorNotifier.hpp"

struct Point
{
    int x;
    int y;
};


class LocationTracker {
    public:
        LocationTracker();
        LocationTracker(int startX, int startY);

        static void updateLocation(std::map<subscriber_port&, int> sensor_values);
        static const Point getLocation();

    private:
        static SensorNotifier _notifier;

        static float _position_x;
        static float _position_y;
        static int _heading;

        static float MotorPulsesToInt(float pulses);
};

#endif // __LOCATIONTRACKER_H__
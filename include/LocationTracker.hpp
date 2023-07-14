#ifndef __LOCATIONTRACKER_H__
#define __LOCATIONTRACKER_H__

#include <map>
#include <iostream>
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

        static int _position_x;
        static int _position_y;
        static int _heading;
};

#endif // __LOCATIONTRACKER_H__
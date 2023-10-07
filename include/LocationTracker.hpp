#ifndef __LOCATIONTRACKER_H__
#define __LOCATIONTRACKER_H__

#include <map>
#include <deque>
#include <iostream>
#include <math.h>
#include "io/SensorNotifier.hpp"
#include "io/DeviceCommunicator.hpp"
#include "positioning/Vector.hpp"
#include "positioning/Line.hpp"
#include "positioning/LineManager.hpp"


#define FIELD_SIZE_X    2000
#define FIELD_SIZE_Y    1000

struct MovementAction {
    MovementAction(int distance, int direction, int speed);
    MovementAction(Line line, int speed);
    MovementAction();

    int distance;
    int direction;
    int speed;
};


class LocationTracker : public DeviceCommunicator {
    public:
        LocationTracker();
        LocationTracker(int startX, int startY);

        static void updateLocation(std::map<subscriber_port, int> sensor_values, std::map<subscriber_port, int> prev_values);
        static const Vector getLocation();
        static int getHeading();

    protected:
        static std::deque<MovementAction> _pendingActions;

    private:

        static SensorNotifier _notifier;
        static LineManager _lineManager;
        static Vector _position;
        static Vector _prevPixel;
        static int _heading;
};

#endif // __LOCATIONTRACKER_H__
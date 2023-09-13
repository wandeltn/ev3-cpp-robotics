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

        static void updateLocation(std::map<subscriber_port, int> sensor_values);
        static const Vector getLocation();
        static int getHeading();

    protected:
        static std::deque<MovementAction> _pendingActions;

    private:

        static SensorNotifier _notifier;
        static LineManager _lineManager;
        static std::map<std::string, int> _previousValues;
        static Vector _position;
        static int _heading;

        static double MotorPulsesToInt(double pulses);
};

#endif // __LOCATIONTRACKER_H__
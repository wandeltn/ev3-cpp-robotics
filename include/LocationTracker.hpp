#ifndef __LOCATIONTRACKER_H__
#define __LOCATIONTRACKER_H__

#include <map>
#include <deque>
#include <iostream>
#include <queue>
#include <numeric>
#include <math.h>
#include "io/SensorNotifier.hpp"
#include "io/DeviceCommunicator.hpp"
#include "positioning/Vector.hpp"
#include "positioning/Line.hpp"
#include "positioning/LineManager.hpp"
#include "positioning/PolyFit.hpp"


#define FIELD_SIZE_X            2000
#define FIELD_SIZE_Y            1000
#define VEHICLE_WIDTH_MM        263 //255
#define COLOR_SENSOR_CACHE_SIZE 20


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

        static void sendForwardMovementUpdate(uint distanceInPulses);
        static SensorNotifier _notifier;

    protected:
        static std::deque<MovementAction> _pendingActions;

    private:

        static LineManager _lineManager;
        static PolyFit _polyfit;
        static Vector _position;
        static Vector _positionByCommand;
        static Vector _prevPixel;
        static std::deque<std::map<std::string, int>> _cachedValues;
        static int _heading_gyro;
        static double _heading_motor;

        static int prevPulses;
        static bool _firstCall;
        static int _colorSensorTriggerValue;

        static void AddValuesToCache(std::map<std::string, int> values);
};

#endif // __LOCATIONTRACKER_H__
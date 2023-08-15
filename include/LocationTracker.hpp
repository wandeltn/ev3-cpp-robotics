#ifndef __LOCATIONTRACKER_H__
#define __LOCATIONTRACKER_H__

#include <map>
#include <iostream>
#include <math.h>
#include "io/SensorNotifier.hpp"
#include "io/DeviceCommunicator.hpp"
#include "positioning/Vector.hpp"


class LocationTracker : public DeviceCommunicator {
    public:
        LocationTracker();
        LocationTracker(int startX, int startY);

        static void updateLocation(std::map<subscriber_port, int> sensor_values);
        static const Vector getLocation();
        static int getHeading();
        
    private:
        static SensorNotifier _notifier;

        static Vector _previousMotorPulses;
        static Vector _position;
        static int _heading;

        static double MotorPulsesToInt(double pulses);
};

#endif // __LOCATIONTRACKER_H__
#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "positioning/RobotMovement.hpp"
#include "LocationTracker.hpp"
#include "positioning/Pathfind.hpp"
#include "display/DirectRenderingManager.hpp"

class Robot : public RobotMovement {
    public:
        Robot();

        void moveToPosition(Vector target);
        void waitForFinish();

    private:
        Pathfind _pathfind;
        static LocationTracker _tracker;
        static DirectRenderingManager _drm;
};

#endif // __ROBOT_H__
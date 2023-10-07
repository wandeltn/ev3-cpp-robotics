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
        void moveToPosition(int distance, int direction);
        void waitForFinish();

    private:
        Pathfind _pathfind;
        static DirectRenderingManager _drm;
        static Vector _destination;
};

#endif // __ROBOT_H__
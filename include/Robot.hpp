#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "positioning/RobotMovement.hpp"
#include "LocationTracker.hpp"
#include "positioning/Pathfind.hpp"
#include "display/DirectRenderingManager.hpp"

class Robot : public RobotMovement {
    public:
        Robot(bool startServer = true);
        ~Robot();

        void moveToPosition(Vector target);
        void moveToPosition(int distance, int direction);
        void waitForFinish();

    private:
        Pathfind _pathfind;
        static DirectRenderingManager _drm;
        static Vector _destination;
        
        static bool enableServer;
        static bool serverStarted;
        static Server _server;
};

#endif // __ROBOT_H__
#include "Robot.hpp"

DirectRenderingManager Robot::_drm{};
Vector Robot::_destination{0,0};
bool Robot::enableServer = true;
bool Robot::serverStarted = false;
Server Robot::_server{};


Robot::Robot(bool startServer) 
{
    _pathfind = Pathfind{_drm.createWindow(
        0,
        0,
        178,
        128,
        false
    )};
    _destination = getLocation();
        
    enableServer = startServer;

    if (enableServer) {
        _server.start();
        serverStarted = true;
    }
}

Robot::~Robot()
{
    if (enableServer) {
        _server.stop();
    }
    serverStarted = false;
}

void Robot::moveToPosition(Vector target)
{
    std::vector<Vector> path = _pathfind.findPath(_destination, target);
    _drm.pushToScreen();
    Vector prevNode = getLocation();
    for (const Vector& node : path) {
        goToLocation(MovementAction{{prevNode, node}, 400});
        prevNode = node;
    }
    _destination = target;
}

void Robot::moveToPosition(int distance, int direction)
{
    goToLocation(MovementAction{distance, direction, 400});
}

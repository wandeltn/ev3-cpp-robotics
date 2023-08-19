#include "Robot.hpp"

DirectRenderingManager Robot::_drm{};


Robot::Robot()
{
    _pathfind = Pathfind{_drm.createWindow(
        0,
        0,
        178,
        128,
        false
    )};
}

void Robot::moveToPosition(Vector target)
{
    std::vector<Vector> path = _pathfind.findPath(getLocation(), target);
    _drm.pushToScreen();
    const Vector& prevNode = getLocation();
    for (const Vector& node : path) {
        goToLocation(MovementAction{{prevNode, node}, 400});
    }
}

void Robot::waitForFinish()
{
    waitForThreadStop();
} 

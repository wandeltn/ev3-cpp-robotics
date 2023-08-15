#include "Robot.hpp"

LocationTracker Robot::_tracker{};
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
    std::vector<Vector> path = _pathfind.findPath(_tracker.getLocation(), target);
    _drm.pushToScreen();
    const Vector& prevNode = _tracker.getLocation();
    for (const Vector& node : path) {
        goToLocation(MovementAction{{prevNode, node}, 400});
    }
}

void Robot::waitForFinish()
{
    waitForThreadStop();
} 

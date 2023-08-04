#include "ObstacleManager.hpp"
#include "ObstacleLine.hpp"

std::vector<std::shared_ptr<BaseObstacle>> ObstacleManager::_obstacles = {};

ObstacleManager::ObstacleManager()
{
    //TODO: load obstacles from file
    appendObstacle(std::make_shared<ObstacleLine>(Line{Vector{15, 25}, Vector{25, 15}}));
}

void ObstacleManager::appendObstacle(std::shared_ptr<BaseObstacle> obstacle)
{
    _obstacles.push_back(obstacle);
}

bool ObstacleManager::checkForIntersect(const Line& line)
{
    for (std::shared_ptr<BaseObstacle> obstacle : _obstacles) {
        if (obstacle->checkForIntersect(line)) {
            return true;
        }
    }
    return false;
}

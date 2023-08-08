#include "ObstacleManager.hpp"

std::vector<std::shared_ptr<BaseObstacle>> ObstacleManager::_obstacles = {};

ObstacleManager::ObstacleManager()
{
    //TODO: load obstacles from file
    appendObstacle(std::make_shared<ObstacleLine>(Line{Vector{15, 25}, Vector{25, 15}}));
    
    appendObstacle(std::make_shared<ObstacleSquare>(Vector{2, 18}, Vector{12, 15}));
    appendObstacle(std::make_shared<ObstacleSquare>(Vector{28, 38}, Vector{34, 31}));
    appendObstacle(std::make_shared<ObstacleSquare>(Vector{50, 50}, Vector{178, 100}));
    appendObstacle(std::make_shared<ObstacleSquare>(Vector{0, 0}, Vector{178, 127}));
    
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

void ObstacleManager::paint(std::shared_ptr<Window> window)
{
    for (std::shared_ptr<BaseObstacle> obstacle : _obstacles) {
        obstacle->paint(window);
    }
}

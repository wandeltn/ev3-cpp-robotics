#ifndef __OBSTACLEMANAGER_H__
#define __OBSTACLEMANAGER_H__

#include <vector>
#include <memory>
#include "Line.hpp"
#include "BaseObstacle.hpp"

class ObstacleManager {
    private:
        static std::vector<std::shared_ptr<BaseObstacle>> _obstacles;

    public:
        ObstacleManager();
        static void appendObstacle(std::shared_ptr<BaseObstacle> obstacle);
        static bool checkForIntersect(const Line& line);
};

#endif // __OBSTACLEMANAGER_H__
#ifndef __OBSTACLEMANAGER_H__
#define __OBSTACLEMANAGER_H__

#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <math.h>
#include "Line.hpp"
#include "../display/Window.hpp"
#include "BaseObstacle.hpp"
#include "ObstacleLine.hpp"
#include "ObstacleSquare.hpp"


class ObstacleManager {
    private:
        static std::vector<std::shared_ptr<BaseObstacle>> _obstacles;

    public:
        ObstacleManager();
        ~ObstacleManager();
        static void appendObstacle(std::shared_ptr<BaseObstacle> obstacle);
        static bool checkForIntersect(const Line& line);
        static void paint(std::shared_ptr<Window> window);
};

#endif // __OBSTACLEMANAGER_H__
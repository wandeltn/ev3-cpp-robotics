#ifndef __OBSTACLESQUARE_H__
#define __OBSTACLESQUARE_H__

#include "Line.hpp"
#include "BaseObstacle.hpp"

class ObstacleSquare : public BaseObstacle {
    private:
        Vector _upperLeft;
        Vector _lowerRight;

    public:
        ObstacleSquare(Vector upperLeft, Vector lowerRight);

        bool checkForIntersect(const Line& line) override;
};

#endif // __OBSTACLESQUARE_H__
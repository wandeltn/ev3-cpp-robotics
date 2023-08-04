#ifndef __OBSTACLELINE_H__
#define __OBSTACLELINE_H__

#include "BaseObstacle.hpp"

class ObstacleLine : public BaseObstacle {
    private:
        Line _obstacle;

    public:
        ObstacleLine(Line line);
        bool checkForIntersect(const Line& line) override;
};

#endif // __OBSTACLELINE_H__
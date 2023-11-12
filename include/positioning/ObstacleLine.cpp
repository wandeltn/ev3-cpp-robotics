#include "ObstacleLine.hpp"

ObstacleLine::ObstacleLine(Line line)
{
    _obstacle = line;
}

bool ObstacleLine::checkForIntersect(const Line& line)
{
    return _obstacle.checkForIntersect(line);
}

void ObstacleLine::paint(std::shared_ptr<Window> window)
{
    std::cout << "start: " <<  _obstacle.start_point << " end: " << _obstacle.end_point << std::endl;
    window->drawLine(_obstacle, DISPLAY_DARK);
}

std::string ObstacleLine::writeOut()
{
    return std::string(
        "LN:" + 
        std::to_string(_obstacle.start_point.x) + 
        "/" + 
        std::to_string(_obstacle.start_point.y) +
        ";" + 
        std::to_string(_obstacle.end_point.x) + 
        "/" + 
        std::to_string(_obstacle.end_point.y)
    );
}

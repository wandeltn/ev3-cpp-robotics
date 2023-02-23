#include "LineIntersect.hpp"
#include "LineType.hpp"

LineIntersect::LineIntersect()
{
    
}

Vector2 LineIntersect::checkForIntersect()
{
    
    LineType line1 = LineType{10, 10, 0, 0};
    //LineType line2 = LineType{temp, Vector2{-10, 10}};

    line1.checkForIntersect(LineType{
        10, 
        10,
        20,
        20
    });
}

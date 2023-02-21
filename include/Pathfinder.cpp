#include "Pathfinder.hpp"
#include <iostream>

Pathfinder::Pathfinder()
{
    
}

void Pathfinder::findPath(Vector2 destination)
{
    std::cerr << "Pathfinder::findPath not implemented" << std::endl;
}

void Pathfinder::findPathNoAnything(Vector2 destination)
{
    
}

CollisionChecker Pathfinder::collisionChecker = CollisionChecker{};

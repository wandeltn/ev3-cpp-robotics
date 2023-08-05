#ifndef __PATHFIND_H__
#define __PATHFIND_H__

#include "Vector.hpp"
#include "ObstacleManager.hpp"
#include "../display/Window.hpp"
#include <vector>
#include <list>
#include <array>
#include <bits/stdc++.h>
#include <limits>
#include <algorithm>

namespace std
{
    template<> struct less<Vector>
    {
       bool operator() (const Vector& lhs, const Vector& rhs) const
       {
           return (lhs.x + lhs.y) < (rhs.x + rhs.y);
       }
    };
}

class Pathfind
{
private:
    ObstacleManager collisionDetect{};
    static std::shared_ptr<Window> _window;

public:
	Pathfind();

	std::vector<Vector> findPath(Vector start, Vector end);
	std::vector<Vector> reconstruct_path(const std::map<Vector, Vector>& cameFrom, Vector current);
    std::vector<Vector> optimizePath(std::vector<Vector> unoptimizedPath);
    
};

#endif
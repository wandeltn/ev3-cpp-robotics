#ifndef __PATHFIND_H__
#define __PATHFIND_H__

#include "Vector.hpp"
#include "ObstacleManager.hpp"
#include "../display/Window.hpp"
#include "AStar.hpp"
#include <vector>
#include <list>
#include <array>
#include <bits/stdc++.h>
#include <limits>
#include <algorithm>


class Pathfind
{
private:
    static ObstacleManager collisionDetect;
    static std::shared_ptr<Window> _window;
    AStar::Generator generator;

public:
	Pathfind();
    Pathfind(std::shared_ptr<Window> window);

	std::vector<Vector> findPath(Vector start, Vector end);
	// std::vector<Vector> reconstruct_path(const std::map<Vector, Vector>& cameFrom, Vector current);
    // std::vector<Vector> optimizePath(std::vector<Vector> unoptimizedPath);
    
};

#endif
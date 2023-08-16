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
#include <regex>

namespace std
{
    template <>
    struct less<Vector>
    {
        bool operator()(const Vector &lhs, const Vector &rhs) const
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
    static bool _useWindow;
    static AStar::Generator generator;
    void saveToFile(Vector start, Vector end, std::vector<Vector> path);
    std::vector<Vector> readFromFile(Vector start, Vector end);
    bool checkIfInChache(Vector start, Vector end);

public:
    Pathfind();
    Pathfind(std::shared_ptr<Window> window);

    std::vector<Vector> findPath(Vector start, Vector end);
    std::vector<Vector> reconstruct_path(std::vector<Vector> total_path);
    std::vector<Vector> optimizePath(std::vector<Vector> unoptimizedPath);
};

#endif
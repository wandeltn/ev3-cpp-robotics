/*
    Copyright (c) 2015, Damian Barczynski <daan.net@wp.eu>
    Following tool is licensed under the terms and conditions of the ISC license.
    For more information visit https://opensource.org/licenses/ISC.
*/
#ifndef __ASTAR_HPP_8F637DB91972F6C878D41D63F7E7214F__
#define __ASTAR_HPP_8F637DB91972F6C878D41D63F7E7214F__

#include <vector>
#include <functional>
#include "Vector.hpp"
#include "ObstacleManager.hpp"

class AStar {
    using uint = unsigned int;
    using HeuristicFunction = std::function<uint(Vector, Vector)>;
    using CoordinateList = std::vector<Vector>;

    struct Node
    {
        uint G, H;
        Vector coordinates;
        Node *parent;

        Node(Vector coord_, Node *parent_ = nullptr);
        uint getScore();
    };

    using NodeSet = std::vector<Node*>;
public:
    class Generator
    {
        bool detectCollision(Vector coordinates_, Vector _origin);
        Node* findNodeOnList(NodeSet& nodes_, Vector coordinates_);
        void releaseNodes(NodeSet& nodes_);

    public:
        Generator();
        Generator(std::shared_ptr<Window> Window);
        void setWorldSize(Vector worldSize_);
        void setDiagonalMovement(bool enable_);
        void setHeuristic(HeuristicFunction heuristic_);
        CoordinateList findPath(Vector source_, Vector target_);
        void addCollision(Vector coordinates_);
        void removeCollision(Vector coordinates_);
        void clearCollisions();

    private:
        HeuristicFunction heuristic;
        CoordinateList direction, walls;
        Vector worldSize;
        uint directions;
        ObstacleManager _om = ObstacleManager{};
        std::shared_ptr<Window> _window;
    };
private:
    class Heuristic
    {
        static Vector getDelta(Vector source_, Vector target_);

    public:
        static uint manhattan(Vector source_, Vector target_);
        static uint euclidean(Vector source_, Vector target_);
        static uint octagonal(Vector source_, Vector target_);
    };
};

#endif // __ASTAR_HPP_8F637DB91972F6C878D41D63F7E7214F__

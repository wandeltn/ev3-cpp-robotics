#include "Rrt.hpp"

std::array<Rrt::RRTNode, 200> Rrt::_rrtTree;

Rrt::RRTNode::RRTNode()
{
    position = {0, 0};    
}

Rrt::RRTNode::RRTNode(Vector pos)
{
    position = pos;
}

void Rrt::RRTNode::addNeighbor(double distance, RRTNode* node)
{
    neighbors.insert({distance, node});
}


Rrt::Rrt()
{
    srand(time(NULL));
    _rrtTree.fill(Vector{});
}

Rrt::Rrt(std::shared_ptr<Window> window)
{
    srand(time(NULL));
    _window = window;
    _rrtTree.fill(Vector{});
}

void Rrt::generateTree()
{
    fillArray();
    generateNeighbors();
    // for (Rrt::RRTNode node : _rrtTree) {
        // for (auto neighbor : node.neighbors) {
            // _window->drawLine(node.position, neighbor.second->position, DISPLAY_BLACK);
        // }
    // }
}

void Rrt::generateNeighbors()
{
    for (RRTNode& node : _rrtTree) {
        std::cout << "checking neighbors for: " << node.position << std::endl;
        for (RRTNode possibleNeighbor : _rrtTree) {
            double distanceBetween = node.position.getDistanceTo(possibleNeighbor.position);
            std::cout << "checking: " << possibleNeighbor.position << std::endl;
            if (node.neighbors.size() >= node.maxNeighbors) {
                for (std::pair<const double, Rrt::RRTNode*> compNode : node.neighbors) {
                    if(compNode.first > distanceBetween) {
                        node.neighbors.insert({distanceBetween, &possibleNeighbor});
                        std::cout << "inserting: " << possibleNeighbor.position << std::endl;
                    }
                }
            } else {
                node.addNeighbor(distanceBetween, &possibleNeighbor);
                std::cout << "inserting new: " << possibleNeighbor.position << std::endl;
            }
        }
        if (node.neighbors.size() >= node.maxNeighbors) {
            std::map<double, RRTNode> tempMap;
            // for (int i = 0; i <= node.maxNeighbors; i++) {
                // tempMap.insert({std::advance(node.neighbors.begin(), i)})
            // }

            // int i = 0;
            // for (std::pair<const double, Rrt::RRTNode *> neighbor : node.neighbors) {
                // if (i++ >= node.maxNeighbors) {
                    // node.neighbors.erase(neighbor.first);
                // }
            // }
        }
    }
}

void Rrt::fillArray()
{
    for (RRTNode& node : _rrtTree) {
        node = RRTNode{{static_cast<double>(rand() % 177), static_cast<double>(rand() % 127)}};
    }
    std::cout << "finished filling array" << std::endl;
}


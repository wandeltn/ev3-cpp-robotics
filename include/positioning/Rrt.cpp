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
    for (Rrt::RRTNode node : _rrtTree) {
        for (auto neighbor : node.neighbors) {
            // _window->drawLine(node.position, neighbor.second->position, DISPLAY_BLACK);
        }
    }
}

void Rrt::generateNeighbors()
{
    for (RRTNode node : _rrtTree) {
        std::cout << "checking neighbors for: " << node.position << std::endl;
        for (RRTNode possibleNeighbor : _rrtTree) {
            double distanceBetween = node.position.getDistanceTo(possibleNeighbor.position);
            std::cout << "checking: " << possibleNeighbor.position << std::endl;
            for (std::pair<const double, Rrt::RRTNode*> compNode : node.neighbors) {
                if (node.neighbors.size() >= node.maxNeighbors) {
                    if(compNode.first > distanceBetween) {
                        node.neighbors.insert({distanceBetween, &possibleNeighbor});
                        node.neighbors.erase(node.neighbors.end());
                        std::cout << "inserting: " << possibleNeighbor.position << std::endl;
                    }
                } else {
                    node.addNeighbor(distanceBetween, &possibleNeighbor);
                        std::cout << "inserting new: " << possibleNeighbor.position << std::endl;
                }
            }
        }
    }
}

void Rrt::fillArray()
{
    for (RRTNode& node : _rrtTree) {
        node = RRTNode{{rand() % 177, rand() % 127}};
    }
    std::cout << "finished filling array" << std::endl;
}


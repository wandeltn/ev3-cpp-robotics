#ifndef __RRT_H__
#define __RRT_H__

#include <array>
#include <vector>
#include <map>
#include <memory>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "Vector.hpp"
#include "../display/Window.hpp"

class Rrt {
    public:
        struct RRTNode {
            RRTNode();
            RRTNode(Vector pos);
            void addNeighbor(double distance, RRTNode* node);
            
            Vector position;
            unsigned short maxNeighbors = 5;
            std::map<double, RRTNode*> neighbors;
        };

        Rrt();
        Rrt(std::shared_ptr<Window> window);
        void generateTree();

    private:
        static std::array<RRTNode, 200> _rrtTree;
        std::shared_ptr<Window> _window;

        void fillArray();
        void generateNeighbors();

};

#endif // __RRT_H__
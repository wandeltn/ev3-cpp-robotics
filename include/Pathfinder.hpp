#ifndef __PATHFINDER_H__
#define __PATHFINDER_H__

#include "Vector2.hpp"
#include "CollisionChecker.hpp"

#define FIELD_SIZE_X    120 //in cm
#define FIELD_SIZE_Y    250 //in cm

class Pathfinder {
    public:
        Pathfinder();
        void findPath(Vector2 destination);
        void findPathNoAnything(Vector2 destination);

    protected:
        static CollisionChecker collisionChecker;
};

#endif // __PATHFINDER_H__
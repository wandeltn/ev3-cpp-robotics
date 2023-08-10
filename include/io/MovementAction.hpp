#ifndef __MOVEMENTACTION_H__
#define __MOVEMENTACTION_H__

class MovementAction {
    public:
        MovementAction(int heading_ = 0, int distance_ = 0, int speed_ = 300);

        int heading;
        int distance;
        int speed;
};

#endif // __MOVEMENTACTION_H__
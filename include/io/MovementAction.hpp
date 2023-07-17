#ifndef __MOVEMENTACTION_H__
#define __MOVEMENTACTION_H__

class MovementAction {
    public:
        MovementAction(int heading, int distance);

        virtual int getHeading();
    protected:
        int _heading;
        int _distance;
};

#endif // __MOVEMENTACTION_H__
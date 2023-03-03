#ifndef __DRIVEACTION_H__
#define __DRIVEACTION_H__

class DriveAction {
    public:
        DriveAction();
        DriveAction(int distance, int targetAngle);
        DriveAction(float distance, int targetAngle);
        DriveAction(int distance, float targetAngle);
        DriveAction(float distance, float targetAngle);

        int getDistance();
        int getTargetAngle();
    private:
        int _distance;
        int _targetAngle;
};

#endif // __DRIVEACTION_H__
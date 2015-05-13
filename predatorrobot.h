#ifndef CPREDATORROBOT_H
#define CPREDATORROBOT_H

#include "robot.h"

class CPredatorRobot : public CRobot
{
public:
    CPredatorRobot();
    ~CPredatorRobot();
    QPixmap pics[4][6];
    //Functions :
    QPixmap draw(int color, int dir);

private:
    void loadGraphics();
signals:

public slots:
};

#endif // CPREDATORROBOT_H

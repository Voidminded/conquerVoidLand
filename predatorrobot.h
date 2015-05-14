#ifndef CPREDATORROBOT_H
#define CPREDATORROBOT_H

#include "robot.h"

class CPredatorRobot : public CRobot
{
public:
    CPredatorRobot();
    ~CPredatorRobot();
    //Functions :
    static QPixmap draw(int color, int dir);
//    static void loadGraphics();
    int hit();
private:
signals:

public slots:
};

#endif // CPREDATORROBOT_H

#ifndef CNINJAROBOT_H
#define CNINJAROBOT_H

#include "robot.h"

class CNinjaRobot : public CRobot
{
    Q_OBJECT
public:
    CNinjaRobot();
    ~CNinjaRobot();
    //Functions :
    static QPixmap draw(int color, int dir);
//    static void loadGraphics();
    int hit();
private:
signals:

public slots:
};

#endif // CNINJAROBOT_H

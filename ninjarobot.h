#ifndef CNINJAROBOT_H
#define CNINJAROBOT_H

#include "robot.h"

class CNinjaRobot : public CRobot
{
    Q_OBJECT
public:
    CNinjaRobot();
    ~CNinjaRobot();
    QPixmap pics[4][6];
    //Functions :
    QPixmap draw(int color, int dir);

private:
    void loadGraphics();
signals:

public slots:
};

#endif // CNINJAROBOT_H

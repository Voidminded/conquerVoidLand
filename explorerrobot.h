#ifndef CEXPLORERROBOT_H
#define CEXPLORERROBOT_H

#include "robot.h"

class CExplorerRobot : public CRobot
{
public:
    CExplorerRobot();
    ~CExplorerRobot();
    //Functions :
    static QPixmap draw(int color, int dir);
//    static void loadGraphics();
    int hit();
private:
signals:

public slots:
};

#endif // CEXPLORERROBOT_H

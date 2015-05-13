#ifndef CEXPLORERROBOT_H
#define CEXPLORERROBOT_H

#include "robot.h"

class CExplorerRobot : public CRobot
{
public:
    CExplorerRobot();
    ~CExplorerRobot();
    QPixmap pics[4][6];
    //Functions :
    QPixmap draw(int color, int dir);

private:
    void loadGraphics();
signals:

public slots:
};

#endif // CEXPLORERROBOT_H

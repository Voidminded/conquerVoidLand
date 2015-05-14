#ifndef CTERMINATORROBOT_H
#define CTERMINATORROBOT_H

#include "robot.h"
#include <QObject>

class CTerminatorRobot : public CRobot
{
public:
    CTerminatorRobot();
    ~CTerminatorRobot();
    //Functions :
    static QPixmap draw(int color, int dir);
//    static void loadGraphics();
    int hit();
private:
signals:

public slots:
};

#endif // CTERMINATORROBOT_H

#ifndef CTERMINATORROBOT_H
#define CTERMINATORROBOT_H

#include "robot.h"
#include <QObject>

class CTerminatorRobot : public CRobot
{
public:
    CTerminatorRobot();
    ~CTerminatorRobot();
    QPixmap pics[4][6];
    //Functions :
    QPixmap draw(int color, int dir);

private:
    void loadGraphics();
signals:

public slots:
};

#endif // CTERMINATORROBOT_H

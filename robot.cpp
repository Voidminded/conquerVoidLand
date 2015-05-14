#include "robot.h"

CRobot::CRobot(QObject *parent) : QObject(parent)
{
    rot=0;
    ocu = 0.3;
    oAdder = 0.001;
    xOffset=-10;//(rand()%15);
    yOffset=5;//(rand()%15);
    xAdder = 0.3;
    yAdder = -0.6;
    pr.gold = 0;
    pr.rhodium = 0;
    pr.platinum = 0;
    shiftTimer = new QTimer();
    shiftTimer->setInterval(_RATE);
    shiftTimer->start();
    connect(shiftTimer, SIGNAL(timeout()), this, SLOT(shifting()));
}

CRobot::~CRobot()
{

}

void CRobot::shifting()
{
    if(yOffset > 10 || yOffset < -10)
        yAdder*=-1;

    if(xOffset > 10 || xOffset < -10)
        xAdder*= -1;
    yOffset += yAdder;
    xOffset += xAdder;
}

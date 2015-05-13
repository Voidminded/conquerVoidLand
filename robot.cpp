#include "robot.h"

CRobot::CRobot(QObject *parent) : QObject(parent)
{
    zirs = QPixmap("./images/pa.png");
    rot=0;
    ocu = 0.3;
    oAdder = 0.001;
    xOffset=(rand()%15);
    yOffset=(rand()%15);
    xAdder = 0.3;
    yAdder = -0.6;

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
    if(yOffset > 15 || yOffset < -15)
        yAdder*=-1;

    if(xOffset > 15 || xOffset < -15)
        xAdder*= -1;
    yOffset += yAdder;
    xOffset += xAdder;
}

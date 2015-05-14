#include "terminatorrobot.h"

CTerminatorRobot::CTerminatorRobot()
{
    hp = 210;
    model = Terminator;
}

CTerminatorRobot::~CTerminatorRobot()
{

}

QPixmap CTerminatorRobot::draw(int color, int dir)
{
    QMap<int, QPixmap> robot;
    QMap<int, QPixmap> light;
    QMap<int, QPixmap> gun;
    QPixmap shadow;
    QPixmap zirs;
    zirs = QPixmap("./images/pa.png");
    robot[Yellow] = QPixmap("./images/bot3/bot3yellow");
    robot[Red] = QPixmap("./images/bot3/bot3red");
    robot[Cyan] = QPixmap("./images/bot3/bot3blue");
    robot[Magenta] = QPixmap("./images/bot3/bot3pink");
    light[Red] = QPixmap("./images/bot3/red3");
    light[Cyan] = QPixmap("./images/bot3/blue3");
    light[Yellow] = QPixmap("./images/bot3/yellow3");
    light[Magenta] = QPixmap("./images/bot3/pink3");
    gun[Cyan] = zirs.copy(36,0,60,116);
    gun[Magenta] = zirs.copy(36,0,60,116);
    gun[Red] = zirs.copy(36,0,60,116);
    gun[Yellow] = zirs.copy(36,0,60,116);
    shadow = QPixmap("./images/bot3/shadow3");
    QPixmap output(360,360);
    output.fill(Qt::transparent);
    QPainter painter(&output);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(0,0,light[color]);
    painter.drawPixmap(0,0,robot[color]);
    painter.drawPixmap(129,90,gun[color]);
    QTransform t(1, 0, 0, 1, output.width()/2, output.height()/2);
    t.rotate(dir*(360/6));
    QPixmap tempOutput = output.copy(0,0,light[color].width(),light[color].height()).transformed(t);
    output.fill(Qt::transparent);
    painter.drawPixmap(50,20,shadow.transformed(t));
    painter.drawPixmap(0,0,tempOutput);
    return output.scaled(300,300);
}

int CTerminatorRobot::hit()
{
    return power;
}

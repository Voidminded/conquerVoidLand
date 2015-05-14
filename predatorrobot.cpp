#include "predatorrobot.h"

CPredatorRobot::CPredatorRobot()
{
    hp = 300;
    model = Predator;
}

CPredatorRobot::~CPredatorRobot()
{

}

QPixmap CPredatorRobot::draw(int color, int dir)
{
    QMap<int, QPixmap> robot;
    QMap<int, QPixmap> light;
    QMap<int, QPixmap> gun;
    QPixmap shadow;
    robot[Cyan] = QPixmap("./images/bot4/bot4");
    robot[Magenta] = QPixmap("./images/bot4/bot4");
    robot[Red] = QPixmap("./images/bot4/bot4");
    robot[Yellow] = QPixmap("./images/bot4/bot4");
    gun[Yellow] = QPixmap("./images/bot4/gun4yellow");
    gun[Red] = QPixmap("./images/bot4/gun4red");
    gun[Cyan] = QPixmap("./images/bot4/gun4blue");
    gun[Magenta] = QPixmap("./images/bot4/gun4pink");
    light[Red] = QPixmap("./images/bot4/red4");
    light[Cyan] = QPixmap("./images/bot4/blue4");
    light[Yellow] = QPixmap("./images/bot4/yellow4");
    light[Magenta] = QPixmap("./images/bot4/pink4");
    shadow = QPixmap("./images/bot4/shadow4");
    QPixmap output(360,360);
    output.fill(Qt::transparent);
    QPainter painter(&output);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(0,0,light[color]);
    painter.drawPixmap(0,0,robot[color]);
    painter.drawPixmap(111,105,gun[color]);
    QTransform t(1, 0, 0, 1, output.width()/2, output.height()/2);
    t.rotate(dir*(360/6));
    QPixmap tempOutput(450,450);
    tempOutput.fill(Qt::transparent);
    QPainter p(&tempOutput);
    p.drawPixmap(50,20,shadow.transformed(t));
    p.drawPixmap(0,0,output.transformed(t));
    return tempOutput.copy(abs(sin(dir*(360/6)*_DEG2RAD)*40),abs(cos(dir*(360/6)*_DEG2RAD)*40),450-abs(sin(dir*(360/6)*_DEG2RAD)*40),450-abs(cos(dir*(360/6)*_DEG2RAD)*40)).scaled(360, 360);
}

int CPredatorRobot::hit()
{
    return power;
}

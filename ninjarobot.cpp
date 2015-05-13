#include "ninjarobot.h"

CNinjaRobot::CNinjaRobot()
{
    hp = 120;
    model = Ninja;
    loadGraphics();
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 6; j++)
            pics[i][j] = draw(i,j);
}

CNinjaRobot::~CNinjaRobot()
{

}

void CNinjaRobot::loadGraphics()
{
    robot[Yellow] = QPixmap("./images/bot2/bot2");
    robot[Red] = QPixmap("./images/bot2/bot2");
    robot[Cyan] = QPixmap("./images/bot2/bot2");
    robot[Magenta] = QPixmap("./images/bot2/bot2");
    light[Red] = QPixmap("./images/bot2/red2");
    light[Cyan] = QPixmap("./images/bot2/blue2");
    light[Yellow] = QPixmap("./images/bot2/yellow2");
    light[Magenta] = QPixmap("./images/bot2/pink2");
    gun[Yellow] = QPixmap("./images/bot2/gun2yellow");
    gun[Red] = QPixmap("./images/bot2/gun2red");
    gun[Cyan] = QPixmap("./images/bot2/gun2blue");
    gun[Magenta] = QPixmap("./images/bot2/gun2pink");
    shadow = QPixmap("./images/bot2/shadow2");
}

QPixmap CNinjaRobot::draw(int color, int dir)
{
    QPixmap output(360,360);
    output.fill(Qt::transparent);
    QPainter painter(&output);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(0,0,light[color]);
    painter.drawPixmap(0,0,robot[color]);
    painter.drawPixmap(63,75,gun[color]);
    QTransform t(1, 0, 0, 1, output.width()/2, output.height()/2);
    t.rotate(dir*(360/6));
    QPixmap tempOutput = output.copy(0,0,light[color].width(),light[color].height()).transformed(t);
    output.fill(Qt::transparent);
    painter.drawPixmap(50,20,shadow.transformed(t));
    painter.drawPixmap(0,0,tempOutput);
    return output.scaled(300,300);
}

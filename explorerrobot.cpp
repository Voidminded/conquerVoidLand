#include "explorerrobot.h"

CExplorerRobot::CExplorerRobot()
{
    hp = 60;
    model = Explorer;
    loadGraphics();
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 6; j++)
            pics[i][j] = draw(i,j);
}

CExplorerRobot::~CExplorerRobot()
{

}

void CExplorerRobot::loadGraphics()
{
    robot[Yellow] = QPixmap("./images/bot1/bot1yellow");
    robot[Red] = QPixmap("./images/bot1/bot1red");
    robot[Cyan] = QPixmap("./images/bot1/bot1blue");
    robot[Magenta] = QPixmap("./images/bot1/bot1pink");
    light[Red] = QPixmap("./images/bot1/red1");
    light[Cyan] = QPixmap("./images/bot1/blue1");
    light[Yellow] = QPixmap("./images/bot1/yellow1");
    light[Magenta] = QPixmap("./images/bot1/pink1");
    gun[Yellow] = zirs.copy(0,0,30,210);
    gun[Red] = zirs.copy(0,0,30,210);
    gun[Cyan] = zirs.copy(0,0,30,210);
    gun[Magenta] = zirs.copy(0,0,30,210);
    shadow = QPixmap("./images/bot1/shadow1");
}

QPixmap CExplorerRobot::draw(int color , int dir)
{
    QPixmap output(360,360);
    output.fill(Qt::transparent);
    QPainter painter(&output);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(0,0,light[color]);
    painter.drawPixmap(0,0,robot[color]);
    painter.drawPixmap(99,60,gun[color]);
    QTransform t(1, 0, 0, 1, output.width()/2, output.height()/2);
    t.rotate(dir*(360/6));
    QPixmap tempOutput = output.copy(0,0,light[color].width(),light[color].height()).transformed(t);
    output.fill(Qt::transparent);
    painter.drawPixmap(50,20,shadow.transformed(t));
    painter.drawPixmap(0,0,tempOutput);
    return output.scaled(300,300);
}

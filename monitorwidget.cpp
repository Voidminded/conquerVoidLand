#include "monitorwidget.h"

CMonitorWidget::CMonitorWidget(QWidget *parent)
{
    // For test :
    testTimer = new QTimer();
    testTimer->setInterval(1000);
    testTimer->start();
    connect(testTimer, SIGNAL(timeout()),this, SLOT(testfunction()));

    this->setFocusPolicy(Qt::ClickFocus);
//    this->setMouseTracking(true);
//    this->setWindowState(Qt::WindowFullScreen);
    this->setFixedSize(690,390);
    mainTimer = new QTimer();
    mainTimer->setInterval(30);
    mainTimer->start();
    connect(mainTimer,SIGNAL(timeout()),this,SLOT(update()));
    cell = QPixmap("./images/hex/empty");

    //    this->setDisabl;
    zoomFactor = std::max((this->width()*1.0/cell.width())/knowledge->map->getWidth(), (this->height()*1.0/cell.height())/knowledge->map->getHeight());
    qDebug() << zoomFactor;
    screenPosX = screenPosY = 0;
    dragging = false;
    zirs = QPixmap("./images/pa.png");
    robot1[Yellow] = QPixmap("./images/bot1/bot1yellow");
    robot1[Red] = QPixmap("./images/bot1/bot1red");
    robot1[Cyan] = QPixmap("./images/bot1/bot1blue");
    robot1[Magenta] = QPixmap("./images/bot1/bot1pink");
    color1[Red] = QPixmap("./images/bot1/red1");
    color1[Cyan] = QPixmap("./images/bot1/blue1");
    color1[Yellow] = QPixmap("./images/bot1/yellow1");
    color1[Magenta] = QPixmap("./images/bot1/pink1");
    shadow1 = QPixmap("./images/bot1/shadow1");

    robot2 = QPixmap("./images/bot2/bot2");
    shadow2 = QPixmap("./images/bot2/shadow2");
    gun2[Yellow] = QPixmap("./images/bot2/gun2yellow");
    gun2[Red] = QPixmap("./images/bot2/gun2red");
    gun2[Cyan] = QPixmap("./images/bot2/gun2blue");
    gun2[Magenta] = QPixmap("./images/bot2/gun2pink");
    color2[Red] = QPixmap("./images/bot2/red2");
    color2[Cyan] = QPixmap("./images/bot2/blue2");
    color2[Yellow] = QPixmap("./images/bot2/yellow2");
    color2[Magenta] = QPixmap("./images/bot2/pink2");

    robot3[Yellow] = QPixmap("./images/bot3/bot3yellow");
    robot3[Red] = QPixmap("./images/bot3/bot3red");
    robot3[Cyan] = QPixmap("./images/bot3/bot3blue");
    robot3[Magenta] = QPixmap("./images/bot3/bot3pink");
    color3[Red] = QPixmap("./images/bot3/red3");
    color3[Cyan] = QPixmap("./images/bot3/blue3");
    color3[Yellow] = QPixmap("./images/bot3/yellow3");
    color3[Magenta] = QPixmap("./images/bot3/pink3");
    shadow3 = QPixmap("./images/bot3/shadow3");

    robot4 = QPixmap("./images/bot4/bot4");
    shadow4 = QPixmap("./images/bot4/shadow4");
    gun4[Yellow] = QPixmap("./images/bot4/gun4yellow");
    gun4[Red] = QPixmap("./images/bot4/gun4red");
    gun4[Cyan] = QPixmap("./images/bot4/gun4blue");
    gun4[Magenta] = QPixmap("./images/bot4/gun4pink");
    color4[Red] = QPixmap("./images/bot4/red4");
    color4[Cyan] = QPixmap("./images/bot4/blue4");
    color4[Yellow] = QPixmap("./images/bot4/yellow4");
    color4[Magenta] = QPixmap("./images/bot4/pink4");

    cellOwner[Cyan] = QPixmap("./images/hex/blue");
    cellOwner[Magenta] = QPixmap("./images/hex/pink");
    cellOwner[Yellow] = QPixmap("./images/hex/yellow");
    cellOwner[Red] = QPixmap("./images/hex/red");

    cellMine[Neutral][0] = QPixmap("./images/hex/empty");
    cellMine[Neutral][1] = QPixmap("./images/hex/empty");
    cellMine[Neutral][2] = QPixmap("./images/hex/empty");
    cellMine[Neutral][3] = QPixmap("./images/hex/empty");
    cellMine[Neutral][4] = QPixmap("./images/hex/empty");
    cellMine[Neutral][5] = QPixmap("./images/hex/empty");
    cellMine[Neutral][6] = QPixmap("./images/hex/empty");
    cellMine[Gold][0] = QPixmap("./images/hex/empty");
    cellMine[Gold][1] = QPixmap("./images/hex/gold1");
    cellMine[Gold][2] = QPixmap("./images/hex/gold2");
    cellMine[Gold][3] = QPixmap("./images/hex/gold3");
    cellMine[Gold][4] = QPixmap("./images/hex/gold4");
    cellMine[Gold][5] = QPixmap("./images/hex/gold5");
    cellMine[Gold][6] = QPixmap("./images/hex/gold6");
    cellMine[Platinum][0] = QPixmap("./images/hex/empty");
    cellMine[Platinum][1] = QPixmap("./images/hex/platinum1");
    cellMine[Platinum][2] = QPixmap("./images/hex/platinum2");
    cellMine[Platinum][3] = QPixmap("./images/hex/platinum3");
    cellMine[Platinum][4] = QPixmap("./images/hex/platinum4");
    cellMine[Platinum][5] = QPixmap("./images/hex/platinum5");
    cellMine[Platinum][6] = QPixmap("./images/hex/platinum6");
    cellMine[Rhodium][0] = QPixmap("./images/hex/empty");
    cellMine[Rhodium][1] = QPixmap("./images/hex/rhodium1");
    cellMine[Rhodium][2] = QPixmap("./images/hex/rhodium2");
    cellMine[Rhodium][3] = QPixmap("./images/hex/rhodium3");
    cellMine[Rhodium][4] = QPixmap("./images/hex/rhodium4");
    cellMine[Rhodium][5] = QPixmap("./images/hex/rhodium5");
    cellMine[Rhodium][6] = QPixmap("./images/hex/rhodium6");

    generateBots();
}

CMonitorWidget::~CMonitorWidget()
{

}



QPixmap CMonitorWidget::drawBot1(int color, int dir)
{
    static int rot=0;
    static float ocu = 0.3;
    static float oAdder = 0.001;
    if(ocu > 0.9 || ocu < 0.1)
        oAdder*= -1;
    ocu += oAdder;
    QPixmap output(360,360);
    output.fill(Qt::transparent);
    QPainter painter(&output);
    //    painter.setRenderHint(QPainter::Antialiasing);
    QPixmap leng = zirs.copy(562,164,86,86);
    QPixmap fang = zirs.copy(0,0,30,210);
    QTransform tr(1, 0, 0, 1, leng.width()/2, leng.height()/2 );
    tr.rotate(rot++);
    QPixmap leng2 = leng.transformed(tr);
    QPixmap leng1 = leng2.copy((sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,(sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,86,86);
    painter.setOpacity(0.6+0.5*(1-ocu));
    painter.setOpacity(1.0);
    painter.drawPixmap(0,0,color1[color]);
    painter.setOpacity(ocu);
    painter.drawPixmap(33,21,leng1);
    leng2 = leng.transformed(tr);
    leng1 = leng2.copy((sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,(sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,86,86);
    painter.drawPixmap(130,21,leng1);
    leng2 = leng.transformed(tr);
    leng1 = leng2.copy((sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,(sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,86,86);
    painter.drawPixmap(150,143,leng1);
    leng2 = leng.transformed(tr);
    leng1 = leng2.copy((sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,(sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,86,86);
    painter.drawPixmap(13,143,leng1);
    painter.setOpacity(1.0);
    painter.drawPixmap(0,0,robot1[color]);
    painter.drawPixmap(99,60,fang);
    QTransform t(1, 0, 0, 1, output.width()/2, output.height()/2);
    t.rotate(dir*(360/6));
    QPixmap tempOutput = output.copy(0,0,color1[color].width(),color1[color].height()).transformed(t);
    output.fill(Qt::transparent);
    painter.drawPixmap(50,20,shadow1.transformed(t));
    painter.drawPixmap(0,0,tempOutput);
    return output.scaled(300,300);
}

QPixmap CMonitorWidget::drawBot2(int color, int dir)
{
    static int rot=0;
    static float ocu = 0.3;
    static float oAdder = 0.001;
    if(ocu > 0.9 || ocu < 0.1)
        oAdder*= -1;
    ocu += oAdder;
    QPixmap output(360,360);
    output.fill(Qt::transparent);
    QPainter painter(&output);
    QPixmap leng = zirs.copy(562,164,86,86);
    QTransform tr(1, 0, 0, 1, leng.width()/2, leng.height()/2 );
    tr.rotate(rot++);
    QPixmap leng2 = leng.transformed(tr);
    QPixmap leng1 = leng2.copy((sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,(sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,86,86);
    painter.setOpacity(0.6+0.5*(1-ocu));
    painter.drawPixmap(50,20,shadow2);
    painter.setOpacity(1.0);
    painter.drawPixmap(0,0,color2[color]);
    painter.setOpacity(ocu);
    painter.drawPixmap(33,21,leng1);
    leng2 = leng.transformed(tr);
    leng1 = leng2.copy((sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,(sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,86,86);
    painter.drawPixmap(130,21,leng1);
    leng2 = leng.transformed(tr);
    leng1 = leng2.copy((sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,(sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,86,86);
    painter.drawPixmap(150,143,leng1);
    leng2 = leng.transformed(tr);
    leng1 = leng2.copy((sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,(sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,86,86);
    painter.drawPixmap(13,143,leng1);
    painter.setOpacity(1.0);
    painter.drawPixmap(0,0,robot2);
    painter.drawPixmap(63,75,gun2[color]);
    QTransform t(1, 0, 0, 1, output.width()/2, output.height()/2);
    t.rotate(dir*(360/6));
    QPixmap tempOutput = output.copy(0,0,color2[color].width(),color2[color].height()).transformed(t);
    output.fill(Qt::transparent);
    painter.drawPixmap(50,20,shadow2.transformed(t));
    painter.drawPixmap(0,0,tempOutput);
    return output.scaled(300,300);
}

QPixmap CMonitorWidget::drawBot3(int color, int dir)
{
    static int rot=0;
    static float ocu = 0.3;
    static float oAdder = 0.001;
    if(ocu > 0.9 || ocu < 0.1)
        oAdder*= -1;
    ocu += oAdder;
    QPixmap output(360,360);
    output.fill(Qt::transparent);
    QPainter painter(&output);
    QPixmap leng = zirs.copy(562,164,86,86);
    QPixmap fang = zirs.copy(36,0,60,116);
    QTransform tr(1, 0, 0, 1, leng.width()/2, leng.height()/2 );
    tr.rotate(++rot);
    QPixmap leng2 = leng.transformed(tr);
    QPixmap leng1 = leng2.copy((sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,(sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,86,86);
    painter.setOpacity(0.6+0.5*(1-ocu));
    painter.setOpacity(1.0);
    painter.drawPixmap(0,0,color3[color]);
    painter.setOpacity(ocu);
    leng1 = leng1.scaled(leng1.width()/2.0,leng1.height()/2.0);
    painter.drawPixmap(87,56,leng1);
    leng2 = leng.transformed(tr);
    leng1 = leng2.copy((sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,(sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,86,86);
    leng1 = leng1.scaled(leng1.width()/2.0,leng1.height()/2.0);
    painter.drawPixmap(169,56,leng1);
    leng2 = leng.transformed(tr);
    leng1 = leng2.copy((sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,(sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,86,86);
    painter.drawPixmap(186,189,leng1);
    leng2 = leng.transformed(tr);
    leng1 = leng2.copy((sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,(sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,86,86);
    painter.drawPixmap(27,189,leng1);
    painter.setOpacity(1.0);
    painter.drawPixmap(0,0,robot3[color]);
    painter.drawPixmap(129,90,fang);
    QTransform t(1, 0, 0, 1, output.width()/2, output.height()/2);
    t.rotate(dir*(360/6));
    QPixmap tempOutput = output.copy(0,0,color3[color].width(),color3[color].height()).transformed(t);
    output.fill(Qt::transparent);
    painter.drawPixmap(50,20,shadow3.transformed(t));
    painter.drawPixmap(0,0,tempOutput);
    return output.scaled(300,300);

}

QPixmap CMonitorWidget::drawBot4(int color, int dir)
{
    static int rot=0;
    static float ocu = 0.3;
    static float oAdder = 0.001;
    if(ocu > 0.9 || ocu < 0.1)
        oAdder*= -1;
    ocu += oAdder;
    QPixmap output(360,360);
    output.fill(Qt::transparent);
    QPainter painter(&output);
    QPixmap leng = zirs.copy(562,164,86,86);
    QTransform tr(1, 0, 0, 1, leng.width()/2, leng.height()/2 );
    tr.rotate(++rot);
    QPixmap leng2 = leng.transformed(tr);
    QPixmap leng1 = leng2.copy((sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,(sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,86,86);
    painter.setOpacity(0.6+0.5*(1-ocu));
    painter.drawPixmap(50,20,shadow4);
    painter.setOpacity(1.0);
    painter.drawPixmap(0,0,color4[color]);
    painter.setOpacity(ocu);
    painter.drawPixmap(81,75,leng1);
    leng2 = leng.transformed(tr);
    leng1 = leng2.copy((sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,(sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,86,86);
    painter.drawPixmap(162,75,leng1);
    leng2 = leng.transformed(tr);
    leng1 = leng2.copy((sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,(sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,86,86);
    painter.drawPixmap(219,208,leng1);
    leng2 = leng.transformed(tr);
    leng1 = leng2.copy((sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,(sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,86,86);
    painter.drawPixmap(22,208,leng1);
    leng2 = leng.transformed(tr);
    leng1 = leng2.copy((sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,(sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,86,86);
    leng1 = leng1.scaled(leng1.size()/1.5);
    painter.drawPixmap(21,120,leng1);
    leng2 = leng.transformed(tr);
    leng1 = leng2.copy((sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,(sqrt(leng2.transformed(tr).height()*leng2.transformed(tr).height()*2)-sqrt(leng.transformed(tr).height()*leng.transformed(tr).height()*2))/4,86,86);
    leng1 = leng1.scaled(leng1.size()/1.5);
    painter.drawPixmap(249,120,leng1);
    painter.setOpacity(1.0);
    painter.drawPixmap(0,0,robot4);
    painter.drawPixmap(111,105,gun4[color]);
    QTransform t(1, 0, 0, 1, output.width()/2, output.height()/2);
    t.rotate(dir*(360/6));
    QPixmap tempOutput(450,450);
    tempOutput.fill(Qt::transparent);
    QPainter p(&tempOutput);
    p.drawPixmap(50,20,shadow4.transformed(t));
    p.drawPixmap(0,0,output.transformed(t));
    return tempOutput.copy(abs(sin(dir*(360/6)*_DEG2RAD)*40),abs(cos(dir*(360/6)*_DEG2RAD)*40),450-abs(sin(dir*(360/6)*_DEG2RAD)*40),450-abs(cos(dir*(360/6)*_DEG2RAD)*40)).scaled(360, 360);
}

void CMonitorWidget::paintEvent(QPaintEvent */*event*/)
{
    //    swapBuffers();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    if(false)
    {
        this->setStyleSheet("background-color: black");
        painter.scale(0.6,0.6);
        painter.setOpacity(0.3);
        painter.drawPixmap(0,0,QPixmap("./images/planet.jpg"));
        mapGenerator(&painter);
        return;
    }
    painter.drawPixmap(0,0,QPixmap("./images/background.jpg"));
    painter.scale(zoomFactor,zoomFactor);
    painter.translate(screenPosX, screenPosY);
    QFont f(painter.font());
    f.setPointSize(18);
    painter.setFont(f);
    drawMap(&painter);
    drawScene(&painter);
}

void CMonitorWidget::drawScene(QPainter *painter)
{
    //    painter->translate(p.getXOffset(), p.getYOffset());
    painter->setRenderHint(QPainter::Antialiasing);
    int height = cell.height()-8;
    int width = cell.width()-8;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < knowledge->teams[i].explorers.count(); j++)
            drawRobot(painter, i, j, Explorer);
        for(int j = 0; j < knowledge->teams[i].ninjas.count(); j++)
            drawRobot(painter, i, j, Ninja);
        for(int j = 0; j < knowledge->teams[i].terminators.count(); j++)
            drawRobot(painter, i, j, Terminator);
        for(int j = 0; j < knowledge->teams[i].predators.count(); j++)
            drawRobot(painter, i, j, Predator);
        //            painter->drawPixmap(
        //                     knowledge->map->reversePos[knowledge->teams[i].explorers.at(j)->getPosition()].first*(width-100)+60
        //                    ,(knowledge->map->reversePos[knowledge->teams[i].explorers.at(j)->getPosition()].first%2?1:-1)*height/4+knowledge->map->reversePos[knowledge->teams[i].explorers.at(j)->getPosition()].second*height+60
        //                    ,knowledge->teams[i].explorers.at(j)->pics[knowledge->teams[i].color][knowledge->teams[i].explorers.at(j)->getDirection()]);
    }
    //    for(int i = 0; i < 24; i++)
    //        for(int j = 0; j < 16; j++)
    //            //            if(knowledge->map->getMap()[i][j])
    //            painter->drawPixmap(i*(width-100)+60,(i%2?1:-1)*height/4+j*height+60,bb[(i*8+j)%96]);
    //                painter->drawPixmap(i*(cell.width()-100),(i%2?1:-1)*cell.height()/4+j*cell.height(),bb[(i*8+j)%96]);
    //    painter->drawPixmap(0,0,drawBot2(3,3));
}

void CMonitorWidget::wheelEvent(QWheelEvent * event)
{
    event->setAccepted(true);
    if((zoomFactor<0.6 || event->delta()<0) && (zoomFactor>0.06 || event->delta()>0))
        zoomFactor += event->delta()/10000.0;
}

void CMonitorWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(dragging)
    {
        qDebug() << event->pos().x() << event->pos().y() << lockPosX << lockPosY;
        screenPosX += (event->pos().x()-lockPosX);
        screenPosY += (event->pos().y()-lockPosY);
        update();
    }
}

void CMonitorWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << true;
    dragging = true;
    lockPosX = event->pos().x();
    lockPosY = event->pos().y();
}

void CMonitorWidget::mouseReleaseEvent(QMouseEvent /*event*/)
{
    qDebug() << false;
    dragging = false;
}

void CMonitorWidget::drawMap(QPainter *painter)
{
    int height = cell.height()-8;
    int width = cell.width()-8;
    for(int i = 0; i < knowledge->map->getWidth(); i++)
        for(int j = 0; j < knowledge->map->getHeight(); j++)
        {
            if(knowledge->map->getMap()[i][j])
            {
                if(knowledge->map->cells.count(knowledge->map->getIndex()[i][j])
                        && knowledge->map->cells[knowledge->map->getIndex()[i][j]].owner >= 0)
                    painter->drawPixmap(i*(width-100),(i%2?1:-1)*height/4+j*height,cellOwner[knowledge->map->cells[knowledge->map->getIndex()[i][j]].owner]);
                painter->drawPixmap(i*(width-100),(i%2?1:-1)*height/4+j*height,cellMine[knowledge->map->cells[knowledge->map->getIndex()[i][j]].mineType][knowledge->map->cells[knowledge->map->getIndex()[i][j]].value]);
                painter->drawText(i*(width-100)+123,(i%2?1:-1)*height/4+j*height+96,QString::number(knowledge->map->getIndex()[i][j]));
            }
        }
}

void CMonitorWidget::mapGenerator(QPainter *painter)
{
    int row = 10;
    int col = 10;
    //    double zoom = 0.5

}

void CMonitorWidget::generateBots()
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 6; j++)
            //            bb[i*6+j] = drawBot1(i,j);
            bb[i*6+j] = knowledge->getRobotsPics()[i][Explorer][j];
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 6; j++)
            //            bb[24+i*6+j] = drawBot2(i,j);
            bb[24+i*6+j] = knowledge->getRobotsPics()[i][Ninja][j];
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 6; j++)
            //            bb[48+i*6+j] = drawBot3(i,j);
            bb[48+i*6+j] = knowledge->getRobotsPics()[i][Terminator][j];
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 6; j++)
            //            bb[72+i*6+j] = drawBot4(i,j);
            bb[72+i*6+j] = knowledge->getRobotsPics()[i][Predator][j];
}

void CMonitorWidget::testfunction()
{
    int t = rand() % 4;
    int r = rand() % 4;
    knowledge->teams[t].color = t;
    switch(r)
    {
    case 0:
    {
        CExplorerRobot* temp = new CExplorerRobot;
        temp->setDirection(rand()%6);
        temp->setPosition(rand()%knowledge->map->getNumberOfCells());
        knowledge->teams[t].explorers.append(temp);
        break;
    }
    case 1:
    {
        CNinjaRobot* tt = new CNinjaRobot;
        tt->setDirection(rand()%6);
        tt->setPosition(rand()%knowledge->map->getNumberOfCells());
        knowledge->teams[t].ninjas.append(tt);
        break;
    }
    case 2:
    {
        CTerminatorRobot* ttt = new CTerminatorRobot;
        ttt->setDirection(rand()%6);
        ttt->setPosition(rand()%knowledge->map->getNumberOfCells());
        knowledge->teams[t].terminators.append(ttt);
        break;
    }
    case 3:
    {
        CPredatorRobot* tttt = new CPredatorRobot;
        tttt->setDirection(rand()%6);
        tttt->setPosition(rand()%knowledge->map->getNumberOfCells());
        knowledge->teams[t].predators.append(tttt);
        break;
    }
    }
    knowledge->debug(QString("Add %1 robot to team %2 ").arg(r).arg(t), Qt::darkCyan);
}

void CMonitorWidget::drawRobot(QPainter *painter, int team, int robot, int model)
{
    int height = cell.height()-8;
    int width = cell.width()-8;
    if(model == Explorer)
    {
//        qDebug() << knowledge->teams[team].explorers.at(robot)->getXOffset() << knowledge->teams[team].explorers.at(robot)->getYOffset();
        painter->translate(knowledge->teams[team].explorers.at(robot)->getXOffset(), knowledge->teams[team].explorers.at(robot)->getYOffset());
        painter->drawPixmap(knowledge->map->reversePos[knowledge->teams[team].explorers.at(robot)->getPosition()].first*(width-100)+60
                ,(knowledge->map->reversePos[knowledge->teams[team].explorers.at(robot)->getPosition()].first%2?1:-1)*height/4+knowledge->map->reversePos[knowledge->teams[team].explorers.at(robot)->getPosition()].second*height+60
//                ,knowledge->teams[team].explorers.at(robot)->pics[knowledge->teams[team].color][knowledge->teams[team].explorers.at(robot)->getDirection()]);
                ,knowledge->getRobotsPics()[team][Explorer][knowledge->teams[team].explorers.at(robot)->getDirection()]);
        painter->translate(-knowledge->teams[team].explorers.at(robot)->getXOffset(), -knowledge->teams[team].explorers.at(robot)->getYOffset());
    }
    else if(model == Ninja)
    {
//        qDebug() << knowledge->teams[team].ninjas.at(robot)->getXOffset() << knowledge->teams[team].ninjas.at(robot)->getYOffset();
        painter->translate(knowledge->teams[team].ninjas.at(robot)->getXOffset(), knowledge->teams[team].ninjas.at(robot)->getYOffset());
        painter->drawPixmap(knowledge->map->reversePos[knowledge->teams[team].ninjas.at(robot)->getPosition()].first*(width-100)+60
                ,(knowledge->map->reversePos[knowledge->teams[team].ninjas.at(robot)->getPosition()].first%2?1:-1)*height/4+knowledge->map->reversePos[knowledge->teams[team].ninjas.at(robot)->getPosition()].second*height+60
//                ,knowledge->teams[team].ninjas.at(robot)->pics[knowledge->teams[team].color][knowledge->teams[team].ninjas.at(robot)->getDirection()]);
                ,knowledge->getRobotsPics()[team][Ninja][knowledge->teams[team].ninjas.at(robot)->getDirection()]);
        painter->translate(-knowledge->teams[team].ninjas.at(robot)->getXOffset(), -knowledge->teams[team].ninjas.at(robot)->getYOffset());
    }
    else if(model == Terminator)
    {
//        qDebug() << knowledge->teams[team].terminators.at(robot)->getXOffset() << knowledge->teams[team].terminators.at(robot)->getYOffset();
        painter->translate(knowledge->teams[team].terminators.at(robot)->getXOffset(), knowledge->teams[team].terminators.at(robot)->getYOffset());
        painter->drawPixmap(knowledge->map->reversePos[knowledge->teams[team].terminators.at(robot)->getPosition()].first*(width-100)+60
                ,(knowledge->map->reversePos[knowledge->teams[team].terminators.at(robot)->getPosition()].first%2?1:-1)*height/4+knowledge->map->reversePos[knowledge->teams[team].terminators.at(robot)->getPosition()].second*height+60
//                ,knowledge->teams[team].terminators.at(robot)->pics[knowledge->teams[team].color][knowledge->teams[team].terminators.at(robot)->getDirection()]);
                ,knowledge->getRobotsPics()[team][Terminator][knowledge->teams[team].terminators.at(robot)->getDirection()]);
        painter->translate(-knowledge->teams[team].terminators.at(robot)->getXOffset(), -knowledge->teams[team].terminators.at(robot)->getYOffset());
    }
    else if(model == Predator)
    {
//        qDebug() << knowledge->teams[team].predators.at(robot)->getXOffset() << knowledge->teams[team].predators.at(robot)->getYOffset();
        painter->translate(knowledge->teams[team].predators.at(robot)->getXOffset(), knowledge->teams[team].predators.at(robot)->getYOffset());
        painter->drawPixmap(knowledge->map->reversePos[knowledge->teams[team].predators.at(robot)->getPosition()].first*(width-100)+60
                ,(knowledge->map->reversePos[knowledge->teams[team].predators.at(robot)->getPosition()].first%2?1:-1)*height/4+knowledge->map->reversePos[knowledge->teams[team].predators.at(robot)->getPosition()].second*height+60
//                ,knowledge->teams[team].predators.at(robot)->pics[knowledge->teams[team].color][knowledge->teams[team].predators.at(robot)->getDirection()]);
                ,knowledge->getRobotsPics()[team][Predator][knowledge->teams[team].predators.at(robot)->getDirection()]);
        painter->translate(-knowledge->teams[team].predators.at(robot)->getXOffset(), -knowledge->teams[team].predators.at(robot)->getYOffset());
    }
}

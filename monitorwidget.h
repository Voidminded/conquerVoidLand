#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H

#include "base.h"
#include "robots.h"
#include "knowledge.h"
#include <QGLWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QBrush>
#include <QTimer>
#include <QPicture>
#include <QPixmap>
#include <QTransform>
#include <QWheelEvent>
#include <QMap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class CMonitorWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit CMonitorWidget(QWidget *parent = 0);
    ~CMonitorWidget();
private:
    QTimer* mainTimer;
    double zoomFactor;
    int screenPosX, screenPosY, lockPosX, lockPosY;
    bool dragging;
    QPixmap zirs;
    QPixmap cellOwner[4];
    QPixmap cell;
    QPixmap cellMine[4][7];
    QMap<int, QPixmap> robot1;
    QMap<int, QPixmap> color1;
    QPixmap shadow1;
    QMap<int, QPixmap> gun2;
    QMap<int, QPixmap> color2;
    QPixmap robot2,shadow2;
    QMap<int, QPixmap> robot3;
    QMap<int, QPixmap> color3;
    QPixmap shadow3;
    QMap<int, QPixmap> gun4;
    QMap<int, QPixmap> color4;
    QPixmap robot4,shadow4;
    //Functions :
    void drawScene(QPainter* painter);
    void drawMap(QPainter* painter);
    void generateBots();
    QPixmap drawBots(int model, int color);
    QPixmap drawBot1(int color, int dir);
    QPixmap drawBot2(int color, int dir);
    QPixmap drawBot3(int color, int dir);
    QPixmap drawBot4(int color, int dir);
    void mapGenerator(QPainter* painter);
    void drawRobot(QPainter* painter, int team, int robot, int model);
    //For test:
    QPixmap bb[96];
    QTimer *testTimer;

signals:

public slots:
private slots:
    void paintEvent(QPaintEvent *);
    void wheelEvent(QWheelEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent);

    void testfunction();
};

#endif // CMONITORWIDGET_H

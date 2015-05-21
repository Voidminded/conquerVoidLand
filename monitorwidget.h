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
    QTimer* mainTimer; /**< Update timer, connected to paintEvent */
    double zoomFactor; /**< Zoom factor of viewport */
    int screenPosX, screenPosY, lockPosX, lockPosY; /**< location of viewport in map */
    bool dragging; /**< used to detect the map is dragging */
    QPixmap zirs; /**< Image used for drawing robots */
    QPixmap cellOwner[4]; /**< the color which will be printed under cells image. (could draw polugon instead)*/
    QPixmap cellIMG; /**< image used for drawing map */
    QPixmap hud; /**< the scoreboard image */
    QPixmap cellMine[4][7]; /**< images of the cells cotaining resources */
    //Note the folowing images are not used in this version due drop of refresh rate
    QMap<int, QPixmap> robot1; /**< Image used for drawing robots */
    QMap<int, QPixmap> color1; /**< Image used for drawing robots */
    QPixmap shadow1; /**< Image used for drawing robots */
    QMap<int, QPixmap> gun2; /**< Image used for drawing robots */
    QMap<int, QPixmap> color2; /**< Image used for drawing robots */
    QPixmap robot2,shadow2; /**< Image used for drawing robots */
    QMap<int, QPixmap> robot3; /**< Image used for drawing robots */
    QMap<int, QPixmap> color3; /**< Image used for drawing robots */
    QPixmap shadow3; /**< Image used for drawing robots */
    QMap<int, QPixmap> gun4; /**< Image used for drawing robots */
    QMap<int, QPixmap> color4; /**< Image used for drawing robots */
    QPixmap robot4,shadow4; /**< Image used for drawing robots */
    //Functions :
    /**
     * @brief
     * Draws the robots on the map
     * @param painter
     */
    void drawScene(QPainter* painter);
    /**
     * @brief
     * draws the map on the background
     * @param painter
     */
    void drawMap(QPainter* painter);
    /**
     * @brief
     * High quality image of robot generator with a turning light under its engine
     * Not used in this version, due to drop of refresh rate
     * Just for test
     * @param color
     * @param dir
     * @return QPixmap
     */
    QPixmap drawBot1(int color, int dir);
    /**
     * @brief
     * High quality image of robot generator with a turning light under its engine
     * Not used in this version, due to drop of refresh rate
     * Just for test
     * @param color
     * @param dir
     * @return QPixmap
     */
    QPixmap drawBot2(int color, int dir);
    /**
     * @brief
     * High quality image of robot generator with a turning light under its engine
     * Not used in this version, due to drop of refresh rate
     * Just for test
     * @param color
     * @param dir
     * @return QPixmap
     */
    QPixmap drawBot3(int color, int dir);
    /**
     * @brief
     * High quality image of robot generator with a turning light under its engine
     * Not used in this version, due to drop of refresh rate
     * Just for test
     * @param color
     * @param dir
     * @return QPixmap
     */
    QPixmap drawBot4(int color, int dir);
    /**
     * @brief
     * Gets the robot pixmap for each robot from knowledge and draws that on screen
     * @param painter
     * @param team = team ID
     * @param robot = the robot ID
     * @param model = the robot type
     */
    void drawRobot(QPainter* painter, int team, int robot, int model);
    //For test:
    QTimer *testTimer; /**< TODO */

signals:

public slots:
    /**
     * @brief
     * Resizes the screen when map updates
     */
    void updateSize();
private slots:
    void paintEvent(QPaintEvent *);
    /**
     * @brief
     * Used for zooming
     * @param event
     */
    void wheelEvent(QWheelEvent * event);
    /**
     * @brief
     * used for dragging
     * @param event
     */
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent);
    /**
     * @brief
     * Just a test function creates random robots and place them on random part of the map
     */
    void testfunction();
};

#endif // CMONITORWIDGET_H

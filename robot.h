#ifndef CROBOT_H
#define CROBOT_H

#include "base.h"
#include <QPixmap>
#include <QMap>
#include <QPainter>
#include <QTimer>
#include <QObject>
#include <QPixmap>

class CRobot: public QObject
{
    Q_OBJECT
public:
    explicit CRobot(QObject *parent = 0);
//    CRobot(const CRobot &obj);
    ~CRobot();
protected:
    int rot;
    float ocu;
    float oAdder;
    //Funtions :
//    virtual void loadGraphics(){}
//    static virtual QPixmap draw(){}
private:
    float xAdder;
    float yAdder;
    QTimer *shiftTimer;
    Property(int, Position, position);
    Property(int, Direction, dir);
    Property(int, HitPoint, hp);
    PropertyGet(int, Model, model);
    PropertyGet(float, XOffset, xOffset);
    PropertyGet(float, YOffset, yOffset);
private slots:
    void shifting();
};

#endif // CROBOT_H

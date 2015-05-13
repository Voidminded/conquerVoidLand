#ifndef CROBOT_H
#define CROBOT_H

#include "base.h"
#include "knowledge.h"
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
    ~CRobot();
    QPixmap zirs;
protected:
    int rot;
    float ocu;
    float oAdder;
    QMap<int, QPixmap> robot;
    QMap<int, QPixmap> light;
    QMap<int, QPixmap> gun;
    QPixmap shadow;
    //Funtions :
    virtual void loadGraphics(){}
    virtual QPixmap draw(){}    
private:
    float xAdder;
    float yAdder;
    QTimer *shiftTimer;
    Property(int, HitPoint, hp);
    PropertyGet(int, Model, model);
    PropertyGet(float, XOffset, xOffset);
    PropertyGet(float, YOffset, yOffset);
private slots:
    void shifting();
};

#endif // CROBOT_H

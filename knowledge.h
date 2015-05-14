#ifndef CKNOWLEDGE_H
#define CKNOWLEDGE_H

#include "base.h"
#include "map.h"
#include "robots.h"
#include <QObject>

//union Robots{
//    CExplorerRobot e();
//    CTerminatorRobot t();
//    CNinjaRobot n();
//    CPredatorRobot p();
//};

class team
{
public:
    int color;
    QList<CExplorerRobot*> explorers;
    QList<CNinjaRobot*> ninjas;
    QList<CTerminatorRobot*> terminators;
    QList<CPredatorRobot*> predators;
};

class CKnowledge : public QObject
{
    Q_OBJECT
public:
    explicit CKnowledge(QObject *parent = 0);
    ~CKnowledge();

    CMap *map;
//    QList<Robots> robots;
    team teams[4];
    inline QPixmap getRobotsPic(int team, int model, int direction){return robotsPics[team][model][direction];}
    PropertyGet(QPixmap***, RobotsPics, robotsPics);//Usage [Team][Robot][Direction]
signals:

public slots:
};

extern CKnowledge* knowledge;

#endif // CKNOWLEDGE_H

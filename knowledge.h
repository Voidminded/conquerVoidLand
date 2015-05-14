#ifndef CKNOWLEDGE_H
#define CKNOWLEDGE_H

#include "base.h"
#include "map.h"
#include "robots.h"
#include "statuswidget.h"
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
    int rhadium = 0;
    int platinum = 0;
    int gold = 0;
};

class CKnowledge : public QObject
{
    Q_OBJECT
public:
    explicit CKnowledge(CStatusPrinter *_printer, QObject *parent = 0);
    ~CKnowledge();

    inline QPixmap getRobotsPic(int team, int model, int direction){return robotsPics[team][model][direction];}
    void debug(QString text, QColor color = QColor(0,0,0));
    CMap *map;
//    QList<Robots> robots;
    team teams[4];
    Property(int, ActiveTeams, activeTeams);
    PropertyGet(QPixmap***, RobotsPics, robotsPics);//Usage [Team][Robot][Direction]

private:
    CStatusPrinter *printer;
signals:

public slots:
};

extern CKnowledge* knowledge;

#endif // CKNOWLEDGE_H

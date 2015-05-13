#ifndef CKNOWLEDGE_H
#define CKNOWLEDGE_H

#include "base.h"
#include "map.h"
#include <QObject>

//union Robots{
//    CExplorerRobot e();
//    CTerminatorRobot t();
//    CNinjaRobot n();
//    CPredatorRobot p();
//};

class CKnowledge : public QObject
{
    Q_OBJECT
public:
    explicit CKnowledge(QObject *parent = 0);
    ~CKnowledge();

    CMap *map;
//    QList<Robots> robots;
signals:

public slots:
};

extern CKnowledge* knowledge;

#endif // CKNOWLEDGE_H

#include "knowledge.h"

CKnowledge *knowledge;

CKnowledge::CKnowledge(CStatusPrinter *_printer, QObject *parent) : QObject(parent)
{
    activeTeams = 0;
//    map = new CMap(27,60, 30,300,900);
    map = new CMap(9,30, 9,27,300);
//    map = new CMap(4,5, 0,0,0);

    printer = _printer;

//    for(int i = 0; i < map->activeCells.count(); i++)
//        debug(QString("Active : %1 %2").arg(map->activeCells.at(i).first).arg(map->activeCells.at(i).second), Qt::magenta);
    //Generating robots images :
    robotsPics = new QPixmap**[4];
    for(int i = 0; i < 4; i++)
    {
        robotsPics[i] = new QPixmap*[4];
        for(int j = 0; j < 4; j++)
            robotsPics[i][j] = new QPixmap[6];
    }
    //Explorers :
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 6; j++)
            robotsPics[i][Explorer][j] = QPixmap(CExplorerRobot::draw(i,j));
    //Ninjas :
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 6; j++)
            robotsPics[i][Ninja][j] = QPixmap(CNinjaRobot::draw(i,j));
    //Terminators :
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 6; j++)
            robotsPics[i][Terminator][j] = QPixmap(CTerminatorRobot::draw(i,j));
    //Predators :
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 6; j++)
            robotsPics[i][Predator][j] = QPixmap(CPredatorRobot::draw(i,j));

}

CKnowledge::~CKnowledge()
{

}

void CKnowledge::debug(QString text, QColor color)
{
    printer->textBuffer.enqueue(CStatusText(text,color));
}

bool CKnowledge::canBuy(int id, int num, int model, int pos, QString &error)
{
    CTerminatorRobot t;
    CExplorerRobot e;
    CNinjaRobot n;
    CPredatorRobot p;
    price removeP;
    if(model == Explorer)
    {
        removeP.gold = e.getPrice().gold*num;
        removeP.platinum = e.getPrice().platinum*num;
        removeP.rhodium = e.getPrice().rhodium*num;
        if(!(teams[id].gold <= e.getPrice().gold*num)
                || !(teams[id].platinum <= e.getPrice().platinum*num)
                || !(teams[id].rhodium <= e.getPrice().rhodium*num))
            error = "Insufficient budget";
        if(map->cells[pos].owner != id)
            error = "Invalid position";
    }
    else if(model == Terminator)
    {
        removeP.gold = t.getPrice().gold*num;
        removeP.platinum = t.getPrice().platinum*num;
        removeP.rhodium = t.getPrice().rhodium*num;
        if(!(teams[id].gold <= t.getPrice().gold*num)
                || !(teams[id].platinum <= t.getPrice().platinum*num)
                || !(teams[id].rhodium <= t.getPrice().rhodium*num))
            error = "Insufficient budget";
        if(map->cells[pos].owner != id)
            error = "Invalid position";
    }
    else if(model == Ninja)
    {
        removeP.gold = n.getPrice().gold*num;
        removeP.platinum = n.getPrice().platinum*num;
        removeP.rhodium = n.getPrice().rhodium*num;
        if(!(teams[id].gold <= n.getPrice().gold*num)
                || !(teams[id].platinum <= n.getPrice().platinum*num)
                || !(teams[id].rhodium <= n.getPrice().rhodium*num))
            error = "Insufficient budget";
        if(map->cells[pos].owner != id)
            error = "Invalid position";
    }
    else if(model == Predator)
    {
        removeP.gold = p.getPrice().gold*num;
        removeP.platinum = p.getPrice().platinum*num;
        removeP.rhodium = p.getPrice().rhodium*num;
        if(!(teams[id].gold <= p.getPrice().gold*num)
                || !(teams[id].platinum <= p.getPrice().platinum*num)
                || !(teams[id].rhodium <= p.getPrice().rhodium*num))
            error = "Insufficient budget";
        if(map->cells[pos].owner != id)
            error = "Invalid position";
    }
    if(error.isEmpty())
    {
        teams[id].gold -= removeP.gold;
        teams[id].platinum -= removeP.platinum;
        teams[id].rhodium -= removeP.rhodium;
        return true;
    }
    else
        return false;
}

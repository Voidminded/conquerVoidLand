#include "knowledge.h"

CKnowledge *knowledge;

CKnowledge::CKnowledge(CStatusPrinter *_printer, QObject *parent) : QObject(parent)
{
    activeTeams = 0;
    for(int i = 0; i < 4; i++)
    {
        teams[i].active = false;
        teams[i].color = i;
        teams[i].explorers.clear();
        teams[i].gold = 60;
        teams[i].ninjas.clear();
        teams[i].platinum = 0;
        teams[i].predators.clear();
        teams[i].rhodium = 0;
        teams[i].terminators.clear();
        teams[i].protectedCells.clear();
    }
    map = new CMap(9,27, 9,27,300);

    printer = _printer;

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
        if(!(teams[id].gold >= e.getPrice().gold*num)
                || !(teams[id].platinum >= e.getPrice().platinum*num)
                || !(teams[id].rhodium >= e.getPrice().rhodium*num))
            error = "Insufficient budget";
        if(map->cells[pos].owner != id)
            error = "Invalid position";
    }
    else if(model == Terminator)
    {
        removeP.gold = t.getPrice().gold*num;
        removeP.platinum = t.getPrice().platinum*num;
        removeP.rhodium = t.getPrice().rhodium*num;
        if(!(teams[id].gold >= t.getPrice().gold*num)
                || !(teams[id].platinum >= t.getPrice().platinum*num)
                || !(teams[id].rhodium >= t.getPrice().rhodium*num))
            error = "Insufficient budget";
        if(map->cells[pos].owner != id)
            error = "Invalid position";
    }
    else if(model == Ninja)
    {
        removeP.gold = n.getPrice().gold*num;
        removeP.platinum = n.getPrice().platinum*num;
        removeP.rhodium = n.getPrice().rhodium*num;
        if(!(teams[id].gold >= n.getPrice().gold*num)
                || !(teams[id].platinum >= n.getPrice().platinum*num)
                || !(teams[id].rhodium >= n.getPrice().rhodium*num))
            error = "Insufficient budget";
        if(map->cells[pos].owner != id)
            error = "Invalid position";
    }
    else if(model == Predator)
    {
        removeP.gold = p.getPrice().gold*num;
        removeP.platinum = p.getPrice().platinum*num;
        removeP.rhodium = p.getPrice().rhodium*num;
        if(!(teams[id].gold >= p.getPrice().gold*num)
                || !(teams[id].platinum >= p.getPrice().platinum*num)
                || !(teams[id].rhodium >= p.getPrice().rhodium*num))
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

bool CKnowledge::canGo(int id, int num, int model, int from, int to, QString &error)
{
    if(!(map->links.contains(QPair<int,int>(from,to)) || map->links.contains(QPair<int,int>(to,from))))
        error = QString("There is no link between %1 and %2").arg(from).arg(to);
    if(map->cells[from].robots[id][model] < num)
        error = QString("You dont have enough robots in %1").arg(from);
    if(error.isEmpty())
        return true;
    else
        return false;
}

void CKnowledge::activateSlot(int i, bool s)
{
    teams[i].active = s;
}

void CKnowledge::generateMap(int _r, int _c, int _rh, int _pl, int _gl)
{
    delete map;
    map = new CMap(_r, _c, _rh, _pl, _gl);
    if(map->getError() != "")
        debug("!!! Error : " + map->getError() + " !!!", Qt::red);
    emit updateMonitorView();
}

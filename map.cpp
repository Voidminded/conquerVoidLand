#include "map.h"

CMap::CMap(int _h, int _w, int _rad, int _plot, int _gold)
{
    height = _h;
    width = _w;
    numberOfCells = 0;
    map = new int*[width];
    for(int i = 0; i <width; i++)
        map[i] = new int[height];
    index = new int*[width];
    for(int i = 0; i <width; i++)
        index[i] = new int[height];
    reversePos.clear();
    cells.clear();
    activeCells.clear();
    forwardPos.clear();
    for(int i = 0; i <width; i++)
        for(int j = 0; j < height; j++)
        {
            map[i][j] = (i+j)%3;
            if(map[i][j])
            {
                index[i][j] = numberOfCells;
                cells[numberOfCells].owner = -1;
                cells[numberOfCells].mineType = Neutral;
                cells[numberOfCells].value = 0;
                reversePos[numberOfCells] = QPair<int,int>(i,j);
                forwardPos[QPair<int,int>(i,j)] = numberOfCells;
                activeCells.append(QPair<int,int>(i,j));
                numberOfCells++;
            }
        }
    links.clear();
    {
        QSet< QPair<int, int> > mySet;
        mySet.clear();
        for(QMap<int, QPair<int, int> >::iterator it = reversePos.begin(); it!=reversePos.end(); ++it)
        {
            if(activeCells.contains(QPair<int, int>(it->first+1, it->second)))
                mySet.insert(QPair<int, int>(it.key(), forwardPos[QPair<int,int>(it->first+1,it->second)]));
            if(it->first%2 && activeCells.contains(QPair<int, int>(it->first+1, it->second+1)))
                mySet.insert(QPair<int, int>(it.key(), forwardPos[QPair<int,int>(it->first+1,it->second+1)]));
            if(!it->first%2 && activeCells.contains(QPair<int, int>(it->first+1, it->second-1)))
                mySet.insert(QPair<int, int>(it.key(), forwardPos[QPair<int,int>(it->first+1,it->second-1)]));
            if(activeCells.contains(QPair<int, int>(it->first, it->second+1)))
                mySet.insert(QPair<int, int>(it.key(), forwardPos[QPair<int,int>(it->first,it->second+1)]));
            if(activeCells.contains(QPair<int, int>(it->first, it->second-1)))
                mySet.insert(QPair<int, int>(it.key(), forwardPos[QPair<int,int>(it->first,it->second-1)]));
            if(activeCells.contains(QPair<int, int>(it->first-1, it->second)))
                mySet.insert(QPair<int, int>(it.key(), forwardPos[QPair<int,int>(it->first-1,it->second)]));
            if(it->first%2 && activeCells.contains(QPair<int, int>(it->first-1, it->second+1)))
                mySet.insert(QPair<int, int>(it.key(), forwardPos[QPair<int,int>(it->first-1,it->second+1)]));
            if(!it->first%2 && activeCells.contains(QPair<int, int>(it->first-1, it->second-1)))
                mySet.insert(QPair<int, int>(it.key(), forwardPos[QPair<int,int>(it->first-1,it->second-1)]));
        }
        for(QSet< QPair<int, int> >::iterator it = mySet.begin(); it != mySet.end(); ++it)
            if(!links.contains(QPair<int, int>(it->second, it->first)))
                links.append(*it);
    }
    while(_rad && checkCells())
    {
        int selected = rand()%(height*width);
        if( cells.count(selected) && cells[selected].mineType == Neutral)
        {
            int toAdd = std::min(_rad, rand()%6+1);
            _rad -= toAdd;
            cells[selected].mineType = Rhodium;
            cells[selected].value = toAdd;
        }
        qDebug() << "Rad : " << _rad << selected;
    }
    while(_plot && checkCells())
    {
        int selected = rand()%(height*width);
        if( cells.count(selected) && cells[selected].mineType == Neutral)
        {
            int toAdd = std::min(_plot, rand()%6+1);
            _plot -= toAdd;
            cells[selected].mineType = Platinum;
            cells[selected].value = toAdd;
        }
        qDebug() << "Plat : " << _plot<< selected;
    }
    while(_gold && checkCells())
    {
        int selected = rand()%(height*width);
        if( cells.count(selected) && cells[selected].mineType == Neutral)
        {
            int toAdd = std::min(_gold, rand()%6+1);
            _gold -= toAdd;
            cells[selected].mineType = Gold;
            cells[selected].value = toAdd;
        }
        qDebug() << "Gold : " << _gold << selected;
    }
    error = "";
    if(!checkCells())
        error = "Could'nt fit all the resources in the map !";
}

CMap::~CMap()
{

}

bool CMap::checkCells(bool player)
{
    for(QMap<int, cell>::iterator it = cells.begin(); it != cells.end(); ++it)
        if(it->mineType == Neutral && (player?(it->owner == -1):true))
            return true;
    return false;
}

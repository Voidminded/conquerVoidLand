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
                numberOfCells++;
            }
        }
    while(_rad)
    {
        int selected = rand()%(height*width);
        if( cells.count(selected) && cells[selected].mineType == Neutral)
        {
            int toAdd = std::min(_rad, rand()%7);
            _rad -= toAdd;
            cells[selected].mineType = Rhodium;
            cells[selected].value = toAdd;
        }
        qDebug() << "Rad : " << _rad << selected;
    }
    while(_plot)
    {
        int selected = rand()%(height*width);
        if( cells.count(selected) && cells[selected].mineType == Neutral)
        {
            int toAdd = std::min(_plot, rand()%7);
            _plot -= toAdd;
            cells[selected].mineType = Platinum;
            cells[selected].value = toAdd;
        }
        qDebug() << "Plat : " << _plot<< selected;
    }
    while(_gold)
    {
        int selected = rand()%(height*width);
        if( cells.count(selected) && cells[selected].mineType == Neutral)
        {
            int toAdd = std::min(_gold, rand()%7);
            _gold -= toAdd;
            cells[selected].mineType = Gold;
            cells[selected].value = toAdd;
        }
        qDebug() << "Gold : " << _gold << selected;
    }
}

CMap::~CMap()
{

}


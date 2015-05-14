#ifndef CMAP_H
#define CMAP_H

#include "base.h"
#include <QList>
#include <QPair>

struct cell{
    int owner;
    int mineType;
    int value;
    int robots[4][4];//[team][robot]
};

class CMap
{
public:
    CMap(int _h, int _w, int _rad, int _plot, int _gold);
    ~CMap();
    QList<QPair<int, int> > links;
    QMap<int, cell> cells;
    QMap<int, QPair<int, int> > reversePos;
    QMap<QPair<int, int>, int> forwardPos;
    PropertyGet(int, Width, width);
    PropertyGet(int, Height, height);
    PropertyGet(int**, Map, map);
    PropertyGet(int**, Index, index);
    PropertyGet(int, NumberOfCells, numberOfCells);
private:
    QList<QPair<int, int> > activeCells;

};

#endif // CMAP_H

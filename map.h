#ifndef CMAP_H
#define CMAP_H

#include "base.h"
#include <QList>
#include <QPair>

struct cell{
    int owner;
    int mineType;
    int value;
};

class CMap
{
public:
    CMap(int _h, int _w, int _rad, int _plot, int _gold);
    ~CMap();
    QList<QPair<int, int> > links;
    QMap<int, cell> cells;
    PropertyGet(int, Width, width);
    PropertyGet(int, Height, height);
    PropertyGet(int**, Map, map);
    PropertyGet(int**, Index, index);
};

#endif // CMAP_H

#ifndef CMAP_H
#define CMAP_H

#include "base.h"
#include <QList>
#include <QPair>

/**
 * @brief
 * Cell structure to store the map data
 */
struct cell{
    int owner; /**< owner of the cell ID */
    int mineType; /**< type of resource available in cell */
    int value; /**< power of mine in the cell [0 6] */
    int robots[4][4]; /**< robots currently on the cell Usage : [teamID][robotType] */
};

class CMap
{
public:
    /**
     * @brief
     * When ever we update the map a new instance of that will be created by following parameters
     * @param _h = Height of the map
     * @param _w = Width
     * @param _rad = number of Rhadium in map
     * @param _plot = number of Platinum
     * @param _gold = Number of gold
     */
    CMap(int _h, int _w, int _rad, int _plot, int _gold);
    ~CMap();
    /**
     * @brief
     * checks if the cell is empty for placing resources on it
     * OR
     * the game class uses it to place the players on Neitral cells
     * @param player = if it is filled (by game class) will check to be sure have not gave this place to other player already
     * @return bool
     */
    bool checkCells(bool player = false);
    QList<QPair<int, int> > links; /**< Links available on the map */
    QMap<int, cell> cells; /**< maps the cell Number to it's object */
    QMap<int, QPair<int, int> > reversePos; /**< converts the cell number to (x,y) position on grid map */
    QMap<QPair<int, int>, int> forwardPos; /**< converts the (x,y) position on grid map to cell number */
    PropertyGet(int, Width, width); /**< map width */
    PropertyGet(int, Height, height); /**< map height */
    PropertyGet(int**, Map, map); /**< the Grid map */
    PropertyGet(int**, Index, index); /**< the Index for each cell (could be store in the map itself but added later in hurry when was needed without thinking) */
    PropertyGet(QString, Error, error); /**< If it can not fit all the resources will return an error ot caller*/
    PropertyGet(int, NumberOfCells, numberOfCells); /**< number of cells in map (obvously NOT equal to height*width) */
private:
    QList<QPair<int, int> > activeCells; /**< List of active cells in the map*/


};

#endif // CMAP_H

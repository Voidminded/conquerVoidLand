#ifndef CKNOWLEDGE_H
#define CKNOWLEDGE_H

#include "base.h"
#include "map.h"
#include "robots.h"
#include "statuswidget.h"
#include <QObject>

/**
 * @brief
 *Is created to save all the robots in one signle data structure
 */
union Robots{
    CExplorerRobot *e; /**< Explorer Robots */
    CTerminatorRobot *t; /**< Terminator  Robots */
    CNinjaRobot *n; /**<  Ninja Robots */
    CPredatorRobot *p; /**< Predator  Robots */
};

/**
 * @brief
 *Saves all the information about a team that game needs to handle
 */
class team
{
public:
    int color; /**< TODO */
    QList<CExplorerRobot*> explorers; /**< TODO */
    QList<CNinjaRobot*> ninjas; /**< TODO */
    QList<CTerminatorRobot*> terminators; /**< TODO */
    QList<CPredatorRobot*> predators; /**< TODO */
    int rhodium; /**< TODO */
    int platinum; /**< TODO */
    int gold; /**< TODO */
    bool active; /**< TODO */
    QList<int> protectedCells; /**< TODO */
};

/**
 * @brief
 * The brain of the game, all the information needed to be shared between classes in the program are stored here
 */
class CKnowledge : public QObject
{
    Q_OBJECT
public:
    explicit CKnowledge(CStatusPrinter *_printer, QObject *parent = 0);
    ~CKnowledge();

    /**
     * @brief
     *  Returns the image of the robot considering following parameters
     * @param id = Id of team
     * @param model = Type of the robot
     * @param direction = direction of the robot
     * @return QPixmap
     */
    inline QPixmap getRobotsPic(int id, int model, int direction){return robotsPics[id][model][direction];}
    /**
     * @brief
     * For printing any text with any color in Status bar
     * @param text = text you want to print
     * @param color = selected color for text, default is black
     */
    void debug(QString text, QColor color = QColor(0,0,0));
    /**
     * @brief
     * Checks if a robot purchase is valid for team requested the purchase
     * @param id = team id of the buyer
     * @param num = number of robots team wants to buy
     * @param model = type of robot requested for purchase
     * @param pos = position that robot should be played on
     * @param error = in case of invalid purchase request, returns why it is invalid
     * @return bool
     */
    bool canBuy(int id, int num, int model, int pos, QString &error);
    /**
     * @brief
     * checks if a requested movement is valid
     * @param id = Team id
     * @param num = number of robots team wants to move
     * @param model = type of robot
     * @param from = curent position of robots
     * @param to = destination
     * @param error = in case of invalid move request, returns why it is invalid
     * @return bool
     */
    bool canGo(int id, int num, int model, int from, int to, QString &error);
    QMap< int, price> robotsPrice; /**< prices of the robots map to the robot enum */
    CMap *map; /**< The instance of map class */
    QList<Robots> robots; /**< Not being used for now */
    team teams[4]; /**< The 4 teams playing this game made of Team class */
    Property(int, ActiveTeams, activeTeams); /**< Number of active teams */
    PropertyGet(QPixmap***, RobotsPics, robotsPics); /**< pictures of robots, Usage: [Team][Robot][Direction] */

private:
    CStatusPrinter *printer; /**< the pointer of printer is passed to this class which writes the data in Status Widget */
signals:
    /**
     * @brief
     * If user creates a new map, it will tell the monitor widget to resize it's view port to fit all the map in
     */
    void updateMonitorView();
public slots:
    /**
     * @brief
     * Activate od deactivate a team due request of CGame
     * @param i = team ID
     * @param s = True(Activate) , False(Deactivate)
     */
    void activateSlot(int i, bool s);
    /**
     * @brief
     * Creates a new map with information sent from CLoadMapWdiget by mapGenerationSignal(int,int,int,int,int) signal
     * @param _r = number of rows
     * @param _c = number of columns
     * @param _rh = Rhodium source available on map
     * @param _pl = Platinum source available on map
     * @param _gl = Gold source available on map
     */
    void generateMap(int _r, int _c, int _rh, int _pl, int _gl);
};

extern CKnowledge* knowledge; /**< Extern the pointer to this class to be accesible for any class includes this file */

#endif // CKNOWLEDGE_H

#ifndef CROBOT_H
#define CROBOT_H

#include "base.h"
#include <QPixmap>
#include <QMap>
#include <QPainter>
#include <QTimer>
#include <QObject>
#include <QPixmap>

/**
 * @brief
 * An structure to save different robots prices in
 */
struct price{
    int rhodium;
    int platinum;
    int gold;
};

/**
 * @brief
 * The main Robot class which will be inherited in all kinds of robots
 */
class CRobot: public QObject
{
    Q_OBJECT
public:
    explicit CRobot(QObject *parent = 0);
//    CRobot(const CRobot &obj); // We can not have copy constructor as this class derived from QObject
    ~CRobot();
    /**
     * @brief
     * Damages the robots by given paameter and reduces that from it's hitpoint
     * @param _hp = How much hitpoint should be reduced
     */
    inline void damage(int _hp){hp-=_hp;}
protected:
    //Funtions :
    /**
     * @brief
     * Returns the power of robot to be entered as damage of other tobots
     * This function is defined virtual to be overwriten by the children in case of need
     * @return int
     */
    virtual int hit(){return 0;}
private:
    float xAdder; /**< For simulating the robot hovering */
    float yAdder; /**< For simulating the robot hovering */
    QTimer *shiftTimer; /**< For simulating the robot hovering */
    Property(int, Position, position); /**< Position of the robot in map (cell ID) */
    Property(int, Direction, dir); /**< Direction of the robot, will be updated in CGame class when a robot moves toward a new direction */
    Property(int, HitPoint, hp); /**< Hitpoint of robot */
    Property(int, Power, power); /**< Damaginf power of robot (weapon power) */
    PropertyGet(int, Model, model); /**< Type of robot (will be filled by children) */
    PropertyGet(int, MultiTargetGun, multiTarget); /**< True: Multi target weapon, False: Single target */
    PropertyGet(price, Price, pr); /**< prica of buying robot (will be filled by children) */
    PropertyGet(float, XOffset, xOffset); /**< Will be read by the QPainter when draws the robot for simulating the robot hovering */
    PropertyGet(float, YOffset, yOffset); /**< Will be read by the QPainter when draws the robot for simulating the robot hovering  */
private slots:
    /**
     * @brief
     * A timer in sonnected to this slut to move a robot a bit for simulating the robot hovering
     */
    void shifting();
};

#endif // CROBOT_H

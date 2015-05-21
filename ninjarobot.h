#ifndef CNINJAROBOT_H
#define CNINJAROBOT_H

#include "robot.h"

/**
 * @brief
 * The ninja robot class
 * Derived from CRobot
 */
class CNinjaRobot : public CRobot
{
    Q_OBJECT
public:
    CNinjaRobot();
    ~CNinjaRobot();
    /**
     * @brief
     * Generate robots pictures
     * Will be called once for seach kind of possible robot (by parameters below)
     * @param color = color of the team = team ID
     * @param dir = Direction of robot
     * @return QPixmap
     */
    static QPixmap draw(int color, int dir);
    /**
     * @brief
     * Overrided the parent hit() function, They are the same for now
     * @return int
     */
    int hit();
private:
signals:

public slots:
};

#endif // CNINJAROBOT_H

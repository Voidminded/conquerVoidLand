#ifndef CEXPLORERROBOT_H
#define CEXPLORERROBOT_H

#include "robot.h"

/**
 * @brief
 * The explorer robot class
 * Derived from CRobot
 */
class CExplorerRobot : public CRobot
{
public:
    CExplorerRobot();
    ~CExplorerRobot();
    //Functions :
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

#endif // CEXPLORERROBOT_H

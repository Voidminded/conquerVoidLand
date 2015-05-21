#ifndef CTERMINATORROBOT_H
#define CTERMINATORROBOT_H

#include "robot.h"
#include <QObject>

/**
 * @brief
 * The terminator robot class
 * Derived from CRobot
 */
class CTerminatorRobot : public CRobot
{
public:
    CTerminatorRobot();
    ~CTerminatorRobot();
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

#endif // CTERMINATORROBOT_H

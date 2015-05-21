#ifndef CGAME_H
#define CGAME_H

#include "knowledge.h"
#include <stdio.h>
#include <QProcess>
#include <QObject>
#include <QTimer>
#include <iostream>
#include <string>
#include <sstream>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>

/**
 * @brief
 * The game driver
 */
class CGame : public QObject
{
    Q_OBJECT
public:
    CGame(QObject *parent = 0);
    ~CGame();

private:
    QTimer *p1CTimer, *p2CTimer, *p3CTimer, *p4CTimer; /**< Separated timers for players */
    QProcess *p1, *p2, *p3, *p4; /**< Separated processes for players which runs the players codes */
    QTimer *playTimer; /**< Every _COMMAND_INTERVAL (defined in base.h) time will do one round of game */
    bool inited1,inited2,inited3,inited4; /**< is used to check if players are initialized, otherwise will send the initialization commands to players */
    /**
     * @brief
     * Adds robots to a team after checking with "canBuy" function in knowledge
     * If purchase is unsucessfull will print the reason in Status bar
     * @param team = team id requested to buy robots
     * @param numbers = number of robots team wants to buy
     * @param model = type of robot team wants to buy
     * @param pos = position the robots should place (cell number)
     */
    void addRobot( int team, int numbers, char model, int pos);
    /**
     * @brief
     * Moves robots and updates its direction for a team after checking with "canGo" function in knowledge
     * If movement is unsucessfull will print the reason in Status bar
     * @param id = team id requested to move robots
     * @param numbers = number of robots team wants to move
     * @param model = type of robot team wants to move
     * @param from = current position of robot
     * @param to = destination
     */
    void moveRobot(int id, int numbers, char model, int from, int to);
    /**
     * @brief
     * Sends command to player #1(ID : 0)
     */
    void sendPlayer1();
    /**
     * @brief
     * Sends command to player #2(ID : 1)
     */
    void sendPlayer2();
    /**
     * @brief
     * Sends command to player #3(ID : 2)
     */
    void sendPlayer3();
    /**
     * @brief
     * Sends command to player #4(ID : 3)
     */
    void sendPlayer4();
    /**
     * @brief
     * Initiates the fighting protocol every round
     */
    void fight();
    /**
     * @brief
     * Will be called from "fiht()" function
     * In given position of map for given team ID does all the possible damages
     * @param pos = cell number
     * @param id = team ID
     */
    void destroyRobs(int pos, int id);
    /**
     * @brief
     * Changes the ownership of the cells after fight in each game round
     */
    void updateOwnership();
    /**
     * @brief
     * Just a Dummy wait function, used to be sure the process is started ( I didn't trust "waitForStarted()" function in QProcess"
     * @param millisecondsToWait
     */
    void delay( int millisecondsToWait );
private slots:
    /**
     * @brief
     * This slot is connected to "readyReadStandardOutput()" of QProcess for player #1
     */
    void receivePlayer1();
    /**
     * @brief
     * This slot is connected to "readyReadStandardOutput()" of QProcess for player #2
     */
    void receivePlayer2();
    /**
     * @brief
     * This slot is connected to "readyReadStandardOutput()" of QProcess for player #3
     */
    void receivePlayer3();
    /**
     * @brief
     * This slot is connected to "readyReadStandardOutput()" of QProcess for player #4
     */
    void receivePlayer4();
    /**
     * @brief
     * Playing timer is connected to this slot to run each round of the game
     */
    void playing();
public slots:
    /**
     * @brief
     * Compiles the code for player #1 and activates it if the compilation is successful
     * In case of unsuccessful compilation shows the GCC error in Status bar
     */
    void compilePlayer1();
    /**
     * @brief
     * Compiles the code for player #2 and activates it if the compilation is successful
     * In case of unsuccessful compilation shows the GCC error in Status bar
     */
    void compilePlayer2();
    /**
     * @brief
     * Compiles the code for player #3 and activates it if the compilation is successful
     * In case of unsuccessful compilation shows the GCC error in Status bar
     */
    void compilePlayer3();
    /**
     * @brief
     * Compiles the code for player #4 and activates it if the compilation is successful
     * In case of unsuccessful compilation shows the GCC error in Status bar
     */
    void compilePlayer4();
    /**
     * @brief
     * Start the QProcesses for active players to play
     */
    void initiateGame();
signals:
    /**
     * @brief
     * Will be emited to activate a team in knowledge
     * @param int = team ID
     * @param bool = True: Activate, False: Deactivate
     */
    void activateTeam(int, bool);
    /**
     * @brief
     * Changes the label of team #1 in player widget to "Enable" or "Disable"
     * @param QString
     */
    void activateTeam1Label(QString);
    /**
     * @brief
     * Changes the label of team #2 in player widget to "Enable" or "Disable"
     * @param QString
     */
    void activateTeam2Label(QString);
    /**
     * @brief
     * Changes the label of team #3 in player widget to "Enable" or "Disable"
     * @param QString
     */
    void activateTeam3Label(QString);
    /**
     * @brief
     * Changes the label of team #4 in player widget to "Enable" or "Disable"
     * @param QString
     */
    void activateTeam4Label(QString);
};

#endif // CGAME_H

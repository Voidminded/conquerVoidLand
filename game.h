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

class CGame : public QObject
{
    Q_OBJECT
public:
    CGame(QObject *parent = 0);
    ~CGame();
    void compileCode();

private:
    QTimer *p1CTimer, *p2CTimer, *p3CTimer, *p4CTimer;
    QProcess *p1, *p2, *p3, *p4;
    QTimer *playTimer;
    bool inited1;
    void addRobot( int team, int numbers, char model, int pos);
    void moveRobot(int id, int numbers, char model, int from, int to);
    void sendPlayer1();
    void sendPlayer2();
    void sendPlayer3();
    void sendPlayer4();
    void fight();
    void destroyRobs(int pos, int id);
    void updateOwnership();
    void delay( int millisecondsToWait );
private slots:
    void receivePlayer1();
    void receivePlayer2();
    void receivePlayer3();
    void receivePlayer4();
    void playing();
public slots:
    void compilePlayer1();
    void compilePlayer2();
    void compilePlayer3();
    void compilePlayer4();
    void initiateGame();
signals:
    void activateTeam(int, bool);
    void activateTeam1Label(QString);
    void activateTeam2Label(QString);
    void activateTeam3Label(QString);
    void activateTeam4Label(QString);
};

#endif // CGAME_H

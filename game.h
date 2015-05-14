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

class CGame : public QObject
{
    Q_OBJECT
public:
    CGame(QObject *parent = 0);
    ~CGame();
    void compileCode();

private:
    QTimer *testTimer;
    QProcess *p1, *p2, *p3, *p4;
    QTimer *player1Time;
    QTimer *player2Time;
    QTimer *player3Time;
    QTimer *player4Time;
    bool inited1;
    void addRobot( int team, int numbers, char model, int pos);
    void moveRobot(int id, int numbers, char model, int from, int to);
private slots:
    void read();
    void write();
    void sendPlayer1();
    void sendPlayer2();
    void sendPlayer3();
    void sendPlayer4();
    void receivePlayer1();
    void receivePlayer2();
    void receivePlayer3();
    void receivePlayer4();
public slots:
    void compilePlayer1();
    void compilePlayer2();
    void compilePlayer3();
    void compilePlayer4();
};

#endif // CGAME_H

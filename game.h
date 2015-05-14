#ifndef CGAME_H
#define CGAME_H

#include "knowledge.h"
#include <stdio.h>
#include <QProcess>
#include <QObject>
#include <QTimer>

class CGame : public QObject
{
    Q_OBJECT
public:
    CGame(QObject *parent = 0);
    ~CGame();
    void compileCode();
    QProcess *p1;

private:
    QTimer *testTimer;
private slots:
    void read();
    void write();
public slots:
    void compilePlayer1();
    void compilePlayer2();
    void compilePlayer3();
    void compilePlayer4();
};

#endif // CGAME_H

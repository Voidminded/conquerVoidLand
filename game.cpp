#include "game.h"

CGame::CGame(QObject *parent)  : QObject(parent)
{
    compileCode();

//    p1 = new QProcess(this);
//    p1->setProcessChannelMode(QProcess::MergedChannels);
//    connect(p1,SIGNAL(readyReadStandardOutput()), this, SLOT(read()));
//    p1->start("./player1.out", QProcess::ReadWrite);
//    p1->write("963");

    testTimer = new QTimer();
    testTimer->setInterval(500);
    testTimer->start();
//    connect(testTimer, SIGNAL(timeout()), this, SLOT(write()));
}

CGame::~CGame()
{

}

void CGame::compileCode()
{
//    FILE *fp = popen("g++ test.cpp -o player1.out", "rt");
////    FILE *fp = popen("ls *", "r");
//    char buf[102400];
////    buf[0] = 'h';
////    knowledge->debug(QString::fromStdString(buf),Qt::red);
//    while (fgets(buf, 1024, fp)) {
////        buf[0] = 'h';
//        knowledge->debug(QString::fromStdString(buf),Qt::red);
//    }

//    fclose(fp);
//    system("g++ test.cpp -o player1.out");



}

void CGame::read()
{
//    qDebug() << "reading !" ;
//    knowledge->debug(p1->readAllStandardError(),Qt::red);
//    knowledge->debug(p1->readAllStandardOutput(),Qt::green);
}

void CGame::write()
{
    static int a=0;
    qDebug() << "writing";
//    if(p1->state() == QProcess::Running)
//        p1->write(QString("%1\n").arg(a++).toStdString().c_str());
}

void CGame::compilePlayer1()
{
    knowledge->debug("Compiling Player 1 .........",Qt::darkMagenta);
    QProcess process;
    process.start("g++ player1.cpp -o player1.out");
    process.waitForFinished(-1); // will wait forever until finished

    QString error = process.readAllStandardError();
    if(!error.isEmpty())
        knowledge->debug(error,Qt::red);
    else
        knowledge->debug("Player 1 code compiled Successfully !",Qt::green);
}

void CGame::compilePlayer2()
{
    knowledge->debug("Compiling Player 2 .........",Qt::red);
    QProcess process;
    process.start("g++ player2.cpp -o player2.out");
    process.waitForFinished(-1); // will wait forever until finished

    QString error = process.readAllStandardError();
    if(!error.isEmpty())
        knowledge->debug(error,Qt::red);
    else
        knowledge->debug("Player 2 code compiled Successfully !",Qt::green);
}

void CGame::compilePlayer3()
{
    knowledge->debug("Compiling Player 3 .........",Qt::darkYellow);
    QProcess process;
    process.start("g++ player3.cpp -o player3.out");
    process.waitForFinished(-1); // will wait forever until finished

    QString error = process.readAllStandardError();
    if(!error.isEmpty())
        knowledge->debug(error,Qt::red);
    else
        knowledge->debug("Player 3 code compiled Successfully !",Qt::green);
}

void CGame::compilePlayer4()
{
    knowledge->debug("Compiling Player 4 .........",Qt::darkCyan);
    QProcess process;
    process.start("g++ player4.cpp -o player4.out");
    process.waitForFinished(-1); // will wait forever until finished

    QString error = process.readAllStandardError();
    if(!error.isEmpty())
        knowledge->debug(error,Qt::red);
    else
        knowledge->debug("Player 4 code compiled Successfully !",Qt::green);
}

#include "game.h"

CGame::CGame(QObject *parent)  : QObject(parent)
{
    inited1 = false;

    compileCode();

    p1 = new QProcess(this);
    p1->setProcessChannelMode(QProcess::SeparateChannels);
    connect(p1,SIGNAL(readyReadStandardOutput()), this, SLOT(receivePlayer1()));
    //    p1->start("./player1.out", QProcess::ReadWrite);

    testTimer = new QTimer();
    testTimer->setInterval(500);
    testTimer->start();
    connect(testTimer, SIGNAL(timeout()), this, SLOT(sendPlayer1()));
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
    p1->start("./player1.out", QProcess::ReadWrite);
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

void CGame::sendPlayer1()
{
    if(p1->state() != QProcess::Running)
        return;
    int id = 0;
    if(!inited1)
    {
        inited1 = true;
        if(p1->state() == QProcess::Running)
        {
            p1->write(QString("%1 %2 %3 %4\n")
                      .arg(knowledge->getActiveTeams())
                      .arg(id)
                      .arg(knowledge->map->getNumberOfCells())
                      .arg(knowledge->map->links.count())
                      .toStdString().c_str());
            p1->waitForBytesWritten();
            for(QMap<int, cell>::iterator it = knowledge->map->cells.begin(); it != knowledge->map->cells.end(); ++it)
            {
                p1->write(QString("%1 %2 %3\n")
                          .arg(it.key())
                          .arg(it->mineType)
                          .arg(it->value)
                          .toStdString().c_str());
                p1->waitForBytesWritten();
            }
            for(int i = 0; i < knowledge->map->links.count(); i++)
            {
                p1->write(QString("%1 %2\n")
                          .arg(knowledge->map->links.at(i).first)
                          .arg(knowledge->map->links.at(i).second)
                          .toStdString().c_str());
                p1->waitForBytesWritten();
            }
        }
    }
    if(p1->state() == QProcess::Running)
    {
        p1->write(QString("%1 %2 %3\n")
                  .arg(knowledge->teams[id].rhodium)
                  .arg(knowledge->teams[id].platinum)
                  .arg(knowledge->teams[id].gold)
                  .toStdString().c_str());
        p1->waitForBytesWritten();
        for(QMap<int, cell>::iterator it = knowledge->map->cells.begin(); it != knowledge->map->cells.end(); ++it)
        {
            p1->write(QString("%1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 %14 %15 %16 %17 %18\n")
                      .arg(it.key())
                      .arg(it->owner)
                      .arg(it->robots[0][Explorer])
                    .arg(it->robots[0][Ninja])
                    .arg(it->robots[0][Terminator])
                    .arg(it->robots[0][Predator])
                    .arg(it->robots[1][Explorer])
                    .arg(it->robots[1][Ninja])
                    .arg(it->robots[1][Terminator])
                    .arg(it->robots[1][Predator])
                    .arg(it->robots[2][Explorer])
                    .arg(it->robots[2][Ninja])
                    .arg(it->robots[2][Terminator])
                    .arg(it->robots[2][Predator])
                    .arg(it->robots[3][Explorer])
                    .arg(it->robots[3][Ninja])
                    .arg(it->robots[3][Terminator])
                    .arg(it->robots[3][Predator])
                    .toStdString().c_str());
            p1->waitForBytesWritten();
        }
    }
}

void CGame::sendPlayer2()
{
    int id = 1;
    if(!inited1)
    {
        inited1 = true;
        if(p1->state() == QProcess::Running)
        {
            p1->write(QString("%1 %2 %3 %4\n")
                      .arg(knowledge->getActiveTeams())
                      .arg(id)
                      .arg(knowledge->map->getNumberOfCells())
                      .arg(knowledge->map->links.count())
                      .toStdString().c_str());
            p1->waitForBytesWritten();
            for(QMap<int, cell>::iterator it = knowledge->map->cells.begin(); it != knowledge->map->cells.end(); ++it)
            {
                p1->write(QString("%1 %2 %3\n")
                          .arg(it.key())
                          .arg(it->mineType)
                          .arg(it->value)
                          .toStdString().c_str());
                p1->waitForBytesWritten();
            }
            for(int i = 0; i < knowledge->map->links.count(); i++)
            {
                p1->write(QString("%1 %2\n")
                          .arg(knowledge->map->links.at(i).first)
                          .arg(knowledge->map->links.at(i).second)
                          .toStdString().c_str());
                p1->waitForBytesWritten();
            }
        }
    }
    if(p1->state() == QProcess::Running)
    {
        p1->write(QString("%1 %2 %3\n")
                  .arg(knowledge->teams[id].rhodium)
                  .arg(knowledge->teams[id].platinum)
                  .arg(knowledge->teams[id].gold)
                  .toStdString().c_str());
        p1->waitForBytesWritten();
        for(QMap<int, cell>::iterator it = knowledge->map->cells.begin(); it != knowledge->map->cells.end(); ++it)
        {
            p1->write(QString("%1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 %14 %15 %16 %17 %18\n")
                      .arg(it.key())
                      .arg(it->owner)
                      .arg(it->robots[0][Explorer])
                    .arg(it->robots[0][Ninja])
                    .arg(it->robots[0][Terminator])
                    .arg(it->robots[0][Predator])
                    .arg(it->robots[1][Explorer])
                    .arg(it->robots[1][Ninja])
                    .arg(it->robots[1][Terminator])
                    .arg(it->robots[1][Predator])
                    .arg(it->robots[2][Explorer])
                    .arg(it->robots[2][Ninja])
                    .arg(it->robots[2][Terminator])
                    .arg(it->robots[2][Predator])
                    .arg(it->robots[3][Explorer])
                    .arg(it->robots[3][Ninja])
                    .arg(it->robots[3][Terminator])
                    .arg(it->robots[3][Predator])
                    .toStdString().c_str());
            p1->waitForBytesWritten();
        }
    }
}

void CGame::sendPlayer3()
{
    int id = 2;
    if(!inited1)
    {
        inited1 = true;
        if(p1->state() == QProcess::Running)
        {
            p1->write(QString("%1 %2 %3 %4\n")
                      .arg(knowledge->getActiveTeams())
                      .arg(id)
                      .arg(knowledge->map->getNumberOfCells())
                      .arg(knowledge->map->links.count())
                      .toStdString().c_str());
            p1->waitForBytesWritten();
            for(QMap<int, cell>::iterator it = knowledge->map->cells.begin(); it != knowledge->map->cells.end(); ++it)
            {
                p1->write(QString("%1 %2 %3\n")
                          .arg(it.key())
                          .arg(it->mineType)
                          .arg(it->value)
                          .toStdString().c_str());
                p1->waitForBytesWritten();
            }
            for(int i = 0; i < knowledge->map->links.count(); i++)
            {
                p1->write(QString("%1 %2\n")
                          .arg(knowledge->map->links.at(i).first)
                          .arg(knowledge->map->links.at(i).second)
                          .toStdString().c_str());
                p1->waitForBytesWritten();
            }
        }
    }
    if(p1->state() == QProcess::Running)
    {
        p1->write(QString("%1 %2 %3\n")
                  .arg(knowledge->teams[id].rhodium)
                  .arg(knowledge->teams[id].platinum)
                  .arg(knowledge->teams[id].gold)
                  .toStdString().c_str());
        p1->waitForBytesWritten();
        for(QMap<int, cell>::iterator it = knowledge->map->cells.begin(); it != knowledge->map->cells.end(); ++it)
        {
            p1->write(QString("%1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 %14 %15 %16 %17 %18\n")
                      .arg(it.key())
                      .arg(it->owner)
                      .arg(it->robots[0][Explorer])
                    .arg(it->robots[0][Ninja])
                    .arg(it->robots[0][Terminator])
                    .arg(it->robots[0][Predator])
                    .arg(it->robots[1][Explorer])
                    .arg(it->robots[1][Ninja])
                    .arg(it->robots[1][Terminator])
                    .arg(it->robots[1][Predator])
                    .arg(it->robots[2][Explorer])
                    .arg(it->robots[2][Ninja])
                    .arg(it->robots[2][Terminator])
                    .arg(it->robots[2][Predator])
                    .arg(it->robots[3][Explorer])
                    .arg(it->robots[3][Ninja])
                    .arg(it->robots[3][Terminator])
                    .arg(it->robots[3][Predator])
                    .toStdString().c_str());
            p1->waitForBytesWritten();
        }
    }
}

void CGame::sendPlayer4()
{
    int id = 3;
    if(!inited1)
    {
        inited1 = true;
        if(p1->state() == QProcess::Running)
        {
            p1->write(QString("%1 %2 %3 %4\n")
                      .arg(knowledge->getActiveTeams())
                      .arg(id)
                      .arg(knowledge->map->getNumberOfCells())
                      .arg(knowledge->map->links.count())
                      .toStdString().c_str());
            p1->waitForBytesWritten();
            for(QMap<int, cell>::iterator it = knowledge->map->cells.begin(); it != knowledge->map->cells.end(); ++it)
            {
                p1->write(QString("%1 %2 %3\n")
                          .arg(it.key())
                          .arg(it->mineType)
                          .arg(it->value)
                          .toStdString().c_str());
                p1->waitForBytesWritten();
            }
            for(int i = 0; i < knowledge->map->links.count(); i++)
            {
                p1->write(QString("%1 %2\n")
                          .arg(knowledge->map->links.at(i).first)
                          .arg(knowledge->map->links.at(i).second)
                          .toStdString().c_str());
                p1->waitForBytesWritten();
            }
        }
    }
    if(p1->state() == QProcess::Running)
    {
        p1->write(QString("%1 %2 %3\n")
                  .arg(knowledge->teams[id].rhodium)
                  .arg(knowledge->teams[id].platinum)
                  .arg(knowledge->teams[id].gold)
                  .toStdString().c_str());
        p1->waitForBytesWritten();
        for(QMap<int, cell>::iterator it = knowledge->map->cells.begin(); it != knowledge->map->cells.end(); ++it)
        {
            p1->write(QString("%1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 %14 %15 %16 %17 %18\n")
                      .arg(it.key())
                      .arg(it->owner)
                      .arg(it->robots[0][Explorer])
                    .arg(it->robots[0][Ninja])
                    .arg(it->robots[0][Terminator])
                    .arg(it->robots[0][Predator])
                    .arg(it->robots[1][Explorer])
                    .arg(it->robots[1][Ninja])
                    .arg(it->robots[1][Terminator])
                    .arg(it->robots[1][Predator])
                    .arg(it->robots[2][Explorer])
                    .arg(it->robots[2][Ninja])
                    .arg(it->robots[2][Terminator])
                    .arg(it->robots[2][Predator])
                    .arg(it->robots[3][Explorer])
                    .arg(it->robots[3][Ninja])
                    .arg(it->robots[3][Terminator])
                    .arg(it->robots[3][Predator])
                    .toStdString().c_str());
            p1->waitForBytesWritten();
        }
    }
}

void CGame::addRobot(int team, int numbers, char model, int pos)
{
    switch(model)
    {
    case 'E':
    {
        for(int i = 0; i < numbers; i++)
        {
            CExplorerRobot* temp = new CExplorerRobot;
            temp->setDirection(rand()%6);
            temp->setPosition(pos);
            knowledge->teams[team].explorers.append(temp);
        }
        break;
    }
    case 'N':
    {
        for(int i = 0; i < numbers; i++)
        {
            CNinjaRobot* tt = new CNinjaRobot;
            tt->setDirection(rand()%6);
            tt->setPosition(pos);
            knowledge->teams[team].ninjas.append(tt);
        }
        break;
    }
    case 'T':
    {
        for(int i = 0; i < numbers; i++)
        {
            CTerminatorRobot* ttt = new CTerminatorRobot;
            ttt->setDirection(rand()%6);
            ttt->setPosition(pos);
            knowledge->teams[team].terminators.append(ttt);
        }
        break;
    }
    case 'P':
    {
        for(int i = 0; i < numbers; i++)
        {
            CPredatorRobot* tttt = new CPredatorRobot;
            tttt->setDirection(rand()%6);
            tttt->setPosition(pos);
            knowledge->teams[team].predators.append(tttt);
        }
        break;
    }
    }
}

void CGame::receivePlayer1()
{
    int id = 0;
    QString errors = p1->readAllStandardError();
    if(!errors.isEmpty())
        knowledge->debug(errors,Qt::red);
    QString movment = p1->readLine();
    QString purchase = p1->readLine();
    QString rest = p1->readAllStandardOutput();
    if(purchase != "WAIT")
    {
        std::stringstream stream;
        stream << purchase.toStdString();
        char model;
        while(stream >> model)
        {
            int number, pos, m;
            if( model == 'T')
                m = Terminator;
            else if( model == 'N')
                m = Ninja;
            else if( model == 'E')
                m = Explorer;
            else if(model == 'P')
                m = Predator;
            else
                m = -1;
            stream >> number;
            stream >> pos;
            QString buyErr;
            if(knowledge->canBuy(id, number,m, pos, buyErr))
                addRobot(id, number, model, pos);
            else
            {
                buyErr.prepend(QString("Invalid purchase Buying %1 of %2 in %3 : ").arg(number).arg(model).arg(pos));
                knowledge->debug(buyErr, Qt::darkRed);
            }
        }
    }
    movment.prepend("Player 1 Moves : ");
    purchase.prepend("Player 1 purchases : ");
    knowledge->debug(movment,Qt::darkMagenta);
    knowledge->debug(purchase,Qt::magenta);
    if(!rest.isEmpty())
        knowledge->debug(rest,Qt::darkRed);
}

void CGame::receivePlayer2()
{
    //    knowledge->debug(p1->readAllStandardError(),Qt::red);
    //    knowledge->debug(p1->readAllStandardOutput(),Qt::green);
}

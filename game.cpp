#include "game.h"

CGame::CGame(QObject *parent)  : QObject(parent)
{
    inited1 = false;
    inited2 = false;
    inited3 = false;
    inited4 = false;

    p1 = new QProcess(this);
    p1->setProcessChannelMode(QProcess::SeparateChannels);
    p2 = new QProcess(this);
    p2->setProcessChannelMode(QProcess::SeparateChannels);
    p3 = new QProcess(this);
    p3->setProcessChannelMode(QProcess::SeparateChannels);
    p4 = new QProcess(this);
    p4->setProcessChannelMode(QProcess::SeparateChannels);


    playTimer = new QTimer();
    playTimer->setInterval(_COMMAND_INTERVAL);
    playTimer->stop();

    // Connections :
    connect(p1,SIGNAL(readyReadStandardOutput()), this, SLOT(receivePlayer1()));
    connect(p2,SIGNAL(readyReadStandardOutput()), this, SLOT(receivePlayer2()));
    connect(p3,SIGNAL(readyReadStandardOutput()), this, SLOT(receivePlayer3()));
    connect(p4,SIGNAL(readyReadStandardOutput()), this, SLOT(receivePlayer4()));
    connect(playTimer, SIGNAL(timeout()), this, SLOT(playing()));

}

CGame::~CGame()
{

}

void CGame::compilePlayer1()
{
    knowledge->debug("Compiling Player 1 .........",Qt::darkMagenta);
    QProcess process;
    process.start("g++ player1.cpp -o player1.out");
    process.waitForFinished(-1); // will wait forever until finished

    QString error = process.readAllStandardError();
    if(!error.isEmpty())
    {
        knowledge->debug(error,Qt::red);
        emit activateTeam(0, false);
        emit activateTeam1Label("Disbaled");
    }
    else
    {
        knowledge->debug("Player 1 code compiled Successfully !",Qt::green);
        emit activateTeam(0, true);
        emit activateTeam1Label("Enabled");
    }
}

void CGame::compilePlayer2()
{
    knowledge->debug("Compiling Player 2 .........",Qt::red);
    QProcess process;
    process.start("g++ player2.cpp -o player2.out");
    process.waitForFinished(-1); // will wait forever until finished

    QString error = process.readAllStandardError();
    if(!error.isEmpty())
    {
        knowledge->debug(error,Qt::red);
        emit activateTeam(1, false);
        emit activateTeam2Label("Disbaled");
    }
    else
    {
        knowledge->debug("Player 2 code compiled Successfully !",Qt::green);
        emit activateTeam(1, true);
        emit activateTeam2Label("Enabled");
    }
}

void CGame::compilePlayer3()
{
    knowledge->debug("Compiling Player 3 .........",Qt::darkYellow);
    QProcess process;
    process.start("g++ player3.cpp -o player3.out");
    process.waitForFinished(-1); // will wait forever until finished

    QString error = process.readAllStandardError();
    if(!error.isEmpty())
    {
        knowledge->debug(error,Qt::red);
        emit activateTeam(2, false);
        emit activateTeam3Label("Disbaled");
    }
    else
    {
        knowledge->debug("Player 3 code compiled Successfully !",Qt::green);
        emit activateTeam(2, true);
        emit activateTeam3Label("Enabled");
    }
}

void CGame::compilePlayer4()
{
    knowledge->debug("Compiling Player 4 .........",Qt::darkCyan);
    QProcess process;
    process.start("g++ player4.cpp -o player4.out");
    process.waitForFinished(-1); // will wait forever until finished

    QString error = process.readAllStandardError();
    if(!error.isEmpty())
    {
        knowledge->debug(error,Qt::red);
        emit activateTeam(3, false);
        emit activateTeam4Label("Disbaled");
    }
    else
    {
        knowledge->debug("Player 4 code compiled Successfully !",Qt::green);
        emit activateTeam(3, true);
        emit activateTeam4Label("Enabled");
    }
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
    if(!inited2)
    {
        inited2 = true;
        if(p2->state() == QProcess::Running)
        {
            p2->write(QString("%1 %2 %3 %4\n")
                      .arg(knowledge->getActiveTeams())
                      .arg(id)
                      .arg(knowledge->map->getNumberOfCells())
                      .arg(knowledge->map->links.count())
                      .toStdString().c_str());
            p2->waitForBytesWritten();
            for(QMap<int, cell>::iterator it = knowledge->map->cells.begin(); it != knowledge->map->cells.end(); ++it)
            {
                p2->write(QString("%1 %2 %3\n")
                          .arg(it.key())
                          .arg(it->mineType)
                          .arg(it->value)
                          .toStdString().c_str());
                p2->waitForBytesWritten();
            }
            for(int i = 0; i < knowledge->map->links.count(); i++)
            {
                p2->write(QString("%1 %2\n")
                          .arg(knowledge->map->links.at(i).first)
                          .arg(knowledge->map->links.at(i).second)
                          .toStdString().c_str());
                p2->waitForBytesWritten();
            }
        }
    }
    if(p2->state() == QProcess::Running)
    {
        p2->write(QString("%1 %2 %3\n")
                  .arg(knowledge->teams[id].rhodium)
                  .arg(knowledge->teams[id].platinum)
                  .arg(knowledge->teams[id].gold)
                  .toStdString().c_str());
        p2->waitForBytesWritten();
        for(QMap<int, cell>::iterator it = knowledge->map->cells.begin(); it != knowledge->map->cells.end(); ++it)
        {
            p2->write(QString("%1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 %14 %15 %16 %17 %18\n")
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
            p2->waitForBytesWritten();
        }
    }
}

void CGame::sendPlayer3()
{
    int id = 2;
    if(!inited3)
    {
        inited3 = true;
        if(p3->state() == QProcess::Running)
        {
            p3->write(QString("%1 %2 %3 %4\n")
                      .arg(knowledge->getActiveTeams())
                      .arg(id)
                      .arg(knowledge->map->getNumberOfCells())
                      .arg(knowledge->map->links.count())
                      .toStdString().c_str());
            p3->waitForBytesWritten();
            for(QMap<int, cell>::iterator it = knowledge->map->cells.begin(); it != knowledge->map->cells.end(); ++it)
            {
                p3->write(QString("%1 %2 %3\n")
                          .arg(it.key())
                          .arg(it->mineType)
                          .arg(it->value)
                          .toStdString().c_str());
                p3->waitForBytesWritten();
            }
            for(int i = 0; i < knowledge->map->links.count(); i++)
            {
                p3->write(QString("%1 %2\n")
                          .arg(knowledge->map->links.at(i).first)
                          .arg(knowledge->map->links.at(i).second)
                          .toStdString().c_str());
                p3->waitForBytesWritten();
            }
        }
    }
    if(p3->state() == QProcess::Running)
    {
        p3->write(QString("%1 %2 %3\n")
                  .arg(knowledge->teams[id].rhodium)
                  .arg(knowledge->teams[id].platinum)
                  .arg(knowledge->teams[id].gold)
                  .toStdString().c_str());
        p3->waitForBytesWritten();
        for(QMap<int, cell>::iterator it = knowledge->map->cells.begin(); it != knowledge->map->cells.end(); ++it)
        {
            p3->write(QString("%1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 %14 %15 %16 %17 %18\n")
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
            p3->waitForBytesWritten();
        }
    }
}

void CGame::sendPlayer4()
{
    int id = 3;
    if(!inited4)
    {
        inited4 = true;
        if(p4->state() == QProcess::Running)
        {
            p4->write(QString("%1 %2 %3 %4\n")
                      .arg(knowledge->getActiveTeams())
                      .arg(id)
                      .arg(knowledge->map->getNumberOfCells())
                      .arg(knowledge->map->links.count())
                      .toStdString().c_str());
            p4->waitForBytesWritten();
            for(QMap<int, cell>::iterator it = knowledge->map->cells.begin(); it != knowledge->map->cells.end(); ++it)
            {
                p4->write(QString("%1 %2 %3\n")
                          .arg(it.key())
                          .arg(it->mineType)
                          .arg(it->value)
                          .toStdString().c_str());
                p4->waitForBytesWritten();
            }
            for(int i = 0; i < knowledge->map->links.count(); i++)
            {
                p4->write(QString("%1 %2\n")
                          .arg(knowledge->map->links.at(i).first)
                          .arg(knowledge->map->links.at(i).second)
                          .toStdString().c_str());
                p4->waitForBytesWritten();
            }
        }
    }
    if(p4->state() == QProcess::Running)
    {
        p4->write(QString("%1 %2 %3\n")
                  .arg(knowledge->teams[id].rhodium)
                  .arg(knowledge->teams[id].platinum)
                  .arg(knowledge->teams[id].gold)
                  .toStdString().c_str());
        p4->waitForBytesWritten();
        for(QMap<int, cell>::iterator it = knowledge->map->cells.begin(); it != knowledge->map->cells.end(); ++it)
        {
            p4->write(QString("%1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 %14 %15 %16 %17 %18\n")
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
            p4->waitForBytesWritten();
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
            knowledge->map->cells[pos].robots[team][Explorer]++;
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
            knowledge->map->cells[pos].robots[team][Ninja]++;
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
            knowledge->map->cells[pos].robots[team][Terminator]++;
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
            knowledge->map->cells[pos].robots[team][Predator]++;
        }
        break;
    }
    }
}

void CGame::moveRobot(int id, int numbers, char model, int from, int to)
{
    if(model == 'E')
        for(int i = 0; i < numbers; i++)
            for(int j = 0; j < knowledge->teams[id].explorers.count(); j++)
                if(knowledge->teams[id].explorers.at(j)->getPosition() == from)
                {
                    knowledge->teams[id].explorers.at(j)->setPosition(to);
                    knowledge->map->cells[from].robots[id][Explorer]--;
                    knowledge->map->cells[to].robots[id][Explorer]++;
                    if(knowledge->map->reversePos[from].first == knowledge->map->reversePos[to].first)
                    {
                        if(knowledge->map->reversePos[from].second < knowledge->map->reversePos[to].second)
                            knowledge->teams[id].explorers.at(j)->setDirection(0);
                        else
                            knowledge->teams[id].explorers.at(j)->setDirection(3);
                    }
                    else if(knowledge->map->reversePos[from].first < knowledge->map->reversePos[to].first)
                    {
                        if(knowledge->map->reversePos[from].second == knowledge->map->reversePos[to].second)
                        {
                            if(from%2)
                                knowledge->teams[id].explorers.at(j)->setDirection(4);
                            else
                                knowledge->teams[id].explorers.at(j)->setDirection(5);
                        }
                        else if(knowledge->map->reversePos[from].second > knowledge->map->reversePos[to].second)
                            knowledge->teams[id].explorers.at(j)->setDirection(4);
                        else
                            knowledge->teams[id].explorers.at(j)->setDirection(5);
                    }
                    else
                    {
                        if(knowledge->map->reversePos[from].second == knowledge->map->reversePos[to].second)
                        {
                            if(from%2)
                                knowledge->teams[id].explorers.at(j)->setDirection(2);
                            else
                                knowledge->teams[id].explorers.at(j)->setDirection(1);
                        }
                        else if(knowledge->map->reversePos[from].second > knowledge->map->reversePos[to].second)
                            knowledge->teams[id].explorers.at(j)->setDirection(2);
                        else
                            knowledge->teams[id].explorers.at(j)->setDirection(1);
                    }
                }
    if(model == 'T')
        for(int i = 0; i < numbers; i++)
            for(int j = 0; j < knowledge->teams[id].terminators.count(); j++)
                if(knowledge->teams[id].terminators.at(j)->getPosition() == from)
                {
                    knowledge->teams[id].terminators.at(j)->setPosition(to);
                    knowledge->map->cells[from].robots[id][Terminator]--;
                    knowledge->map->cells[to].robots[id][Terminator]++;
                    if(knowledge->map->reversePos[from].first == knowledge->map->reversePos[to].first)
                    {
                        if(knowledge->map->reversePos[from].second < knowledge->map->reversePos[to].second)
                            knowledge->teams[id].terminators.at(j)->setDirection(0);
                        else
                            knowledge->teams[id].terminators.at(j)->setDirection(3);
                    }
                    else if(knowledge->map->reversePos[from].first < knowledge->map->reversePos[to].first)
                    {
                        if(knowledge->map->reversePos[from].second == knowledge->map->reversePos[to].second)
                        {
                            if(from%2)
                                knowledge->teams[id].terminators.at(j)->setDirection(4);
                            else
                                knowledge->teams[id].terminators.at(j)->setDirection(5);
                        }
                        else if(knowledge->map->reversePos[from].second > knowledge->map->reversePos[to].second)
                            knowledge->teams[id].terminators.at(j)->setDirection(4);
                        else
                            knowledge->teams[id].terminators.at(j)->setDirection(5);
                    }
                    else
                    {
                        if(knowledge->map->reversePos[from].second == knowledge->map->reversePos[to].second)
                        {
                            if(from%2)
                                knowledge->teams[id].terminators.at(j)->setDirection(2);
                            else
                                knowledge->teams[id].terminators.at(j)->setDirection(1);
                        }
                        else if(knowledge->map->reversePos[from].second > knowledge->map->reversePos[to].second)
                            knowledge->teams[id].terminators.at(j)->setDirection(2);
                        else
                            knowledge->teams[id].terminators.at(j)->setDirection(1);
                    }
                }
    if(model == 'N')
        for(int i = 0; i < numbers; i++)
            for(int j = 0; j < knowledge->teams[id].ninjas.count(); j++)
                if(knowledge->teams[id].ninjas.at(j)->getPosition() == from)
                {
                    knowledge->teams[id].ninjas.at(j)->setPosition(to);
                    knowledge->map->cells[from].robots[id][Ninja]--;
                    knowledge->map->cells[to].robots[id][Ninja]++;
                    if(knowledge->map->reversePos[from].first == knowledge->map->reversePos[to].first)
                    {
                        if(knowledge->map->reversePos[from].second < knowledge->map->reversePos[to].second)
                            knowledge->teams[id].ninjas.at(j)->setDirection(0);
                        else
                            knowledge->teams[id].ninjas.at(j)->setDirection(3);
                    }
                    else if(knowledge->map->reversePos[from].first < knowledge->map->reversePos[to].first)
                    {
                        if(knowledge->map->reversePos[from].second == knowledge->map->reversePos[to].second)
                        {
                            if(from%2)
                                knowledge->teams[id].ninjas.at(j)->setDirection(4);
                            else
                                knowledge->teams[id].ninjas.at(j)->setDirection(5);
                        }
                        else if(knowledge->map->reversePos[from].second > knowledge->map->reversePos[to].second)
                            knowledge->teams[id].ninjas.at(j)->setDirection(4);
                        else
                            knowledge->teams[id].ninjas.at(j)->setDirection(5);
                    }
                    else
                    {
                        if(knowledge->map->reversePos[from].second == knowledge->map->reversePos[to].second)
                        {
                            if(from%2)
                                knowledge->teams[id].ninjas.at(j)->setDirection(2);
                            else
                                knowledge->teams[id].ninjas.at(j)->setDirection(1);
                        }
                        else if(knowledge->map->reversePos[from].second > knowledge->map->reversePos[to].second)
                            knowledge->teams[id].ninjas.at(j)->setDirection(2);
                        else
                            knowledge->teams[id].ninjas.at(j)->setDirection(1);
                    }
                }
    if(model == 'P')
        for(int i = 0; i < numbers; i++)
            for(int j = 0; j < knowledge->teams[id].predators.count(); j++)
                if(knowledge->teams[id].predators.at(j)->getPosition() == from)
                {
                    knowledge->teams[id].predators.at(j)->setPosition(to);
                    knowledge->map->cells[from].robots[id][Predator]--;
                    knowledge->map->cells[to].robots[id][Predator]++;
                    if(knowledge->map->reversePos[from].first == knowledge->map->reversePos[to].first)
                    {
                        if(knowledge->map->reversePos[from].second < knowledge->map->reversePos[to].second)
                            knowledge->teams[id].predators.at(j)->setDirection(0);
                        else
                            knowledge->teams[id].predators.at(j)->setDirection(3);
                    }
                    else if(knowledge->map->reversePos[from].first < knowledge->map->reversePos[to].first)
                    {
                        if(knowledge->map->reversePos[from].second == knowledge->map->reversePos[to].second)
                        {
                            if(from%2)
                                knowledge->teams[id].predators.at(j)->setDirection(4);
                            else
                                knowledge->teams[id].predators.at(j)->setDirection(5);
                        }
                        else if(knowledge->map->reversePos[from].second > knowledge->map->reversePos[to].second)
                            knowledge->teams[id].predators.at(j)->setDirection(4);
                        else
                            knowledge->teams[id].predators.at(j)->setDirection(5);
                    }
                    else
                    {
                        if(knowledge->map->reversePos[from].second == knowledge->map->reversePos[to].second)
                        {
                            if(from%2)
                                knowledge->teams[id].predators.at(j)->setDirection(2);
                            else
                                knowledge->teams[id].predators.at(j)->setDirection(1);
                        }
                        else if(knowledge->map->reversePos[from].second < knowledge->map->reversePos[to].second)
                            knowledge->teams[id].predators.at(j)->setDirection(2);
                        else
                            knowledge->teams[id].predators.at(j)->setDirection(1);
                    }
                }

}

void CGame::receivePlayer1()
{
    QProcess * sourceProcess = dynamic_cast<QProcess *>(sender());
    if(sourceProcess != p1)
        return;
    int id = 0;
    QString errors = p1->readAllStandardError();
    if(!errors.isEmpty())
        knowledge->debug(errors,Qt::red);
    QString movment = p1->readLine();
    QString purchase = p1->readLine();
    QString rest = p1->readAllStandardOutput();
    if(movment != "WAIT")
    {
        std::stringstream stream;
        stream << movment.toStdString();
        int number;
        while(stream >> number)
        {
            char model;
            stream >> model;
            int from, to, m;
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
            stream >> from;
            stream >> to;
            QString mvErr;
            if(knowledge->canGo(id, number,m, from, to, mvErr))
                moveRobot(id, number, model, from, to);
            else
            {
                mvErr.prepend(QString("Invalid Move %1 of %2 from %3 to %4 : ").arg(number).arg(model).arg(from).arg(to));
                knowledge->debug(mvErr, Qt::darkBlue);
            }
        }
    }
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
                knowledge->debug(buyErr, Qt::blue);
            }
        }
    }
    movment.prepend("Player 1 Moves : ");
    purchase.prepend("Player 1 purchases : ");
    knowledge->debug(movment,Qt::darkMagenta);
    knowledge->debug(purchase,Qt::magenta);
//    if(!rest.isEmpty())
//        knowledge->debug(rest);
}

void CGame::receivePlayer2()
{
    QProcess * sourceProcess = dynamic_cast<QProcess *>(sender());
    if(sourceProcess != p2)
        return;
    int id = 1;
    QString errors = p2->readAllStandardError();
    if(!errors.isEmpty())
        knowledge->debug(errors,Qt::red);
    QString movment = p2->readLine();
    QString purchase = p2->readLine();
    QString rest = p2->readAllStandardOutput();
    if(movment != "WAIT")
    {
        std::stringstream stream;
        stream << movment.toStdString();
        int number;
        while(stream >> number)
        {
            char model;
            stream >> model;
            int from, to, m;
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
            stream >> from;
            stream >> to;
            QString mvErr;
            if(knowledge->canGo(id, number,m, from, to, mvErr))
                moveRobot(id, number, model, from, to);
            else
            {
                mvErr.prepend(QString("Invalid Move %1 of %2 from %3 to %4 : ").arg(number).arg(model).arg(from).arg(to));
                knowledge->debug(mvErr, Qt::darkBlue);
            }
        }
    }
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
                knowledge->debug(buyErr, Qt::blue);
            }
        }
    }
    movment.prepend("Player 2 Moves : ");
    purchase.prepend("Player 2 purchases : ");
    knowledge->debug(movment,Qt::darkRed);
    knowledge->debug(purchase,Qt::red);
//    if(!rest.isEmpty())
//        knowledge->debug(rest);
}

void CGame::receivePlayer3()
{
    QProcess * sourceProcess = dynamic_cast<QProcess *>(sender());
    if(sourceProcess != p3)
        return;
    int id = 2;
    QString errors = p3->readAllStandardError();
    if(!errors.isEmpty())
        knowledge->debug(errors,Qt::red);
    QString movment = p3->readLine();
    QString purchase = p3->readLine();
    QString rest = p3->readAllStandardOutput();
    if(movment != "WAIT")
    {
        std::stringstream stream;
        stream << movment.toStdString();
        int number;
        while(stream >> number)
        {
            char model;
            stream >> model;
            int from, to, m;
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
            stream >> from;
            stream >> to;
            QString mvErr;
            if(knowledge->canGo(id, number,m, from, to, mvErr))
                moveRobot(id, number, model, from, to);
            else
            {
                mvErr.prepend(QString("Invalid Move %1 of %2 from %3 to %4 : ").arg(number).arg(model).arg(from).arg(to));
                knowledge->debug(mvErr, Qt::darkBlue);
            }
        }
    }
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
                knowledge->debug(buyErr, Qt::blue);
            }
        }
    }
    movment.prepend("Player 3 Moves : ");
    purchase.prepend("Player 3 purchases : ");
    knowledge->debug(movment,Qt::darkYellow);
    knowledge->debug(purchase,Qt::yellow);
    if(!rest.isEmpty())
        knowledge->debug(rest);
}

void CGame::receivePlayer4()
{
    QProcess * sourceProcess = dynamic_cast<QProcess *>(sender());
    if(sourceProcess != p4)
        return;
    int id = 3;
    QString errors = p4->readAllStandardError();
    if(!errors.isEmpty())
        knowledge->debug(errors,Qt::red);
    QString movment = p4->readLine();
    QString purchase = p4->readLine();
    QString rest = p4->readAllStandardOutput();
    if(movment != "WAIT")
    {
        std::stringstream stream;
        stream << movment.toStdString();
        int number;
        while(stream >> number)
        {
            char model;
            stream >> model;
            int from, to, m;
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
            stream >> from;
            stream >> to;
            QString mvErr;
            if(knowledge->canGo(id, number,m, from, to, mvErr))
                moveRobot(id, number, model, from, to);
            else
            {
                mvErr.prepend(QString("Invalid Move %1 of %2 from %3 to %4 : ").arg(number).arg(model).arg(from).arg(to));
                knowledge->debug(mvErr, Qt::darkBlue);
            }
        }
    }
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
                knowledge->debug(buyErr, Qt::blue);
            }
        }
    }
    movment.prepend("Player 4 Moves : ");
    purchase.prepend("Player 4 purchases : ");
    knowledge->debug(movment,Qt::darkCyan);
    knowledge->debug(purchase,Qt::cyan);
    if(!rest.isEmpty())
        knowledge->debug(rest);
}

void CGame::initiateGame()
{
    for(int i = 0; i < 4; i++)
    {
        if(knowledge->teams[i].active)
        {
            if(knowledge->map->checkCells(true))
                while(1)
                {
                    int selected = rand()%(knowledge->map->getNumberOfCells());
                    if( knowledge->map->cells.count(selected) && knowledge->map->cells[selected].mineType == Neutral && knowledge->map->cells[selected].owner == -1)
                    {
                        knowledge->map->cells[selected].owner = i;
                        break;
                    }
                }
            else
            {
                int selected = rand()%(knowledge->map->getNumberOfCells());
                knowledge->map->cells[selected].owner = i;
            }
        }
    }
    if(knowledge->teams[0].active)
    {
        p1->start("./player1.out", QProcess::ReadWrite);
        p1->waitForStarted();
        delay(30);
    }
    if(knowledge->teams[1].active)
    {
        p2->start("./player2.out", QProcess::ReadWrite);
        p2->waitForStarted();
        delay(30);
    }
    if(knowledge->teams[2].active)
    {
        p3->start("./player3.out", QProcess::ReadWrite);
        p3->waitForStarted();
        delay(30);
    }
    if(knowledge->teams[3].active)
    {
        p4->start("./player4.out", QProcess::ReadWrite);
        p4->waitForStarted();
        delay(30);
    }

    playTimer->start();
}

void CGame::playing()
{
    //Distribution :
    for(QMap<int, cell>::iterator it = knowledge->map->cells.begin(); it != knowledge->map->cells.end(); ++it)
    {
        if(it->owner != -1 && it->value > 0)
        {
            if(it->mineType == Gold)
                knowledge->teams[it->owner].gold += it->value;
            else if(it->mineType == Platinum)
                knowledge->teams[it->owner].platinum += it->value;
            else if(it->mineType == Rhodium)
                knowledge->teams[it->owner].rhodium += it->value;
        }
    }

    //Moving and Buying :
    if(knowledge->teams[0].active)
    {
        sendPlayer1();
        if(!p1->waitForReadyRead(_PLAYER_RESPONSE_TIME))
        {
            knowledge->debug("Player 1 did not provide result in time, Not playing anymore");
            p1->close();
        }
    }
    if(knowledge->teams[1].active)
    {
        sendPlayer2();
        if(!p2->waitForReadyRead(_PLAYER_RESPONSE_TIME))
        {
            knowledge->debug("Player 2 did not provide result in time, Not playing anymore");
            p2->close();
        }
    }
    if(knowledge->teams[2].active)
    {
        sendPlayer3();
        if(!p3->waitForReadyRead(_PLAYER_RESPONSE_TIME))
        {
            knowledge->debug("Player 3 did not provide result in time, Not playing anymore");
            p3->close();
        }
    }
    if(knowledge->teams[3].active)
    {
        sendPlayer4();
        if(!p4->waitForReadyRead(_PLAYER_RESPONSE_TIME))
        {
            knowledge->debug("Player 4 did not provide result in time, Not playing anymore");
            p4->close();
        }
    }
    //Fighting :
    fight();

    //Ownership update:
    updateOwnership();

}

void CGame::updateOwnership()
{
    for(int i = 0; i < 4; i++)
    {
        knowledge->teams[i].protectedCells.clear();
        for(int j = 0; j < knowledge->teams[i].explorers.count(); j++)
            knowledge->teams[i].protectedCells.append(knowledge->teams[i].explorers.at(j)->getPosition());
        for(int j = 0; j < knowledge->teams[i].ninjas.count(); j++)
            knowledge->teams[i].protectedCells.append(knowledge->teams[i].ninjas.at(j)->getPosition());
        for(int j = 0; j < knowledge->teams[i].terminators.count(); j++)
            knowledge->teams[i].protectedCells.append(knowledge->teams[i].terminators.at(j)->getPosition());
        for(int j = 0; j < knowledge->teams[i].predators.count(); j++)
            knowledge->teams[i].protectedCells.append(knowledge->teams[i].predators.at(j)->getPosition());
//        for(int j = 0; j < knowledge->teams[i].protectedCells.count(); j++)
//            knowledge->debug(QString::number(knowledge->teams[i].protectedCells.at(j)));
    }
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < knowledge->teams[i].protectedCells.count(); j++)
        {
            for(int k = 0; k < 4; k++)
            {
                if(k != j && knowledge->teams[k].protectedCells.contains(knowledge->teams[i].protectedCells.at(j)))
                    break;
            }
            knowledge->map->cells[knowledge->teams[i].protectedCells.at(j)].owner = i;
        }
    }
}

void CGame::fight()
{
    for(QMap<int, cell>::iterator it = knowledge->map->cells.begin(); it!= knowledge->map->cells.end(); ++it)
    {
        for(int i = 0;  i < 4; i++)
        {
            destroyRobs(it.key(), i);
        }
    }
    //Destroying the robots :
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < knowledge->teams[i].explorers.count(); j++)
            if(knowledge->teams[i].explorers.at(j)->getHitPoint() <= 0)
            {
                CExplorerRobot *bot = knowledge->teams[i].explorers[j];
                knowledge->teams[i].explorers.removeAt(j);
                j--;
                delete bot;
            }
        for(int j = 0; j < knowledge->teams[i].ninjas.count(); j++)
            if(knowledge->teams[i].ninjas.at(j)->getHitPoint() <= 0)
            {
                CNinjaRobot *bot = knowledge->teams[i].ninjas[j];
                knowledge->teams[i].ninjas.removeAt(j);
                j--;
                delete bot;
            }
        for(int j = 0; j < knowledge->teams[i].terminators.count(); j++)
            if(knowledge->teams[i].terminators.at(j)->getHitPoint() <= 0)
            {
                CTerminatorRobot *bot = knowledge->teams[i].terminators[j];
                knowledge->teams[i].terminators.removeAt(j);
                j--;
                delete bot;
            }
        for(int j = 0; j < knowledge->teams[i].predators.count(); j++)
            if(knowledge->teams[i].predators.at(j)->getHitPoint() <= 0)
            {
                CPredatorRobot *bot = knowledge->teams[i].predators[j];
                knowledge->teams[i].predators.removeAt(j);
                j--;
                delete bot;
            }
    }
}

void CGame::destroyRobs(int pos, int id)
{
//    for(int i = 0; i < 4; i++)
    int i = id;
    {
        for(int j = 0; j < knowledge->teams[id].terminators.count(); j++)
        {
            if(knowledge->teams[i].terminators.at(j)->getPosition() == pos)
            {
                for(int k = 0; k < 4; k++)
                {
                    if( k != id)
                    {
                        for(int l = 0; l < knowledge->teams[k].predators.count(); l++)
                        {
                            if(knowledge->teams[k].predators.at(l)->getPosition() == pos && knowledge->teams[k].predators.at(l)->getHitPoint() > 0)
                            {
                                knowledge->teams[k].predators.at(l)->damage(knowledge->teams[i].terminators.at(j)->hit());
                            }
                        }
                        for(int l = 0; l < knowledge->teams[k].terminators.count(); l++)
                        {
                            if(knowledge->teams[k].terminators.at(l)->getPosition() == pos && knowledge->teams[k].terminators.at(l)->getHitPoint() > 0)
                            {
                                knowledge->teams[k].terminators.at(l)->damage(knowledge->teams[i].terminators.at(j)->hit());
                            }
                        }
                        for(int l = 0; l < knowledge->teams[k].ninjas.count(); l++)
                        {
                            if(knowledge->teams[k].ninjas.at(l)->getPosition() == pos && knowledge->teams[k].ninjas.at(l)->getHitPoint() > 0)
                            {
                                knowledge->teams[k].ninjas.at(l)->damage(knowledge->teams[i].terminators.at(j)->hit());
                            }
                        }
                        for(int l = 0; l < knowledge->teams[k].explorers.count(); l++)
                        {
                            if(knowledge->teams[k].explorers.at(l)->getPosition() == pos && knowledge->teams[k].explorers.at(l)->getHitPoint() > 0)
                            {
                                knowledge->teams[k].explorers.at(l)->damage(knowledge->teams[i].terminators.at(j)->hit());
                            }
                        }
                    }
                }
            }
        }
        for(int j = 0; j < knowledge->teams[i].predators.count(); j++)
        {
            if(knowledge->teams[i].predators.at(j)->getPosition() == pos)
            {
                for(int k = 0; k < 4; k++)
                {
                    if( k != id)
                    {
                        for(int l = 0; l < knowledge->teams[k].predators.count(); l++)
                        {
                            if(knowledge->teams[k].predators.at(l)->getPosition() == pos && knowledge->teams[k].predators.at(l)->getHitPoint() > 0)
                            {
                                knowledge->teams[k].predators.at(l)->damage(knowledge->teams[i].predators.at(j)->hit());
                            }
                        }
                        for(int l = 0; l < knowledge->teams[k].terminators.count(); l++)
                        {
                            if(knowledge->teams[k].terminators.at(l)->getPosition() == pos && knowledge->teams[k].terminators.at(l)->getHitPoint() > 0)
                            {
                                knowledge->teams[k].terminators.at(l)->damage(knowledge->teams[i].predators.at(j)->hit());
                            }
                        }
                        for(int l = 0; l < knowledge->teams[k].ninjas.count(); l++)
                        {
                            if(knowledge->teams[k].ninjas.at(l)->getPosition() == pos && knowledge->teams[k].ninjas.at(l)->getHitPoint() > 0)
                            {
                                knowledge->teams[k].ninjas.at(l)->damage(knowledge->teams[i].predators.at(j)->hit());
                            }
                        }
                        for(int l = 0; l < knowledge->teams[k].explorers.count(); l++)
                        {
                            if(knowledge->teams[k].explorers.at(l)->getPosition() == pos && knowledge->teams[k].explorers.at(l)->getHitPoint() > 0)
                            {
                                knowledge->teams[k].explorers.at(l)->damage(knowledge->teams[i].predators.at(j)->hit());
                            }
                        }
                    }
                }
            }
        }
        for(int j = 0; j < knowledge->teams[i].ninjas.count(); j++)
        {
            if(knowledge->teams[i].ninjas.at(j)->getPosition() == pos)
            {
                for(int k = 0; k < 4; k++)
                {
                    if( k != id)
                    {
                        for(int l = 0; l < knowledge->teams[k].predators.count(); l++)
                        {
                            if(knowledge->teams[k].predators.at(l)->getPosition() == pos && knowledge->teams[k].predators.at(l)->getHitPoint() > 0)
                            {
                                knowledge->teams[k].predators.at(l)->damage(knowledge->teams[i].ninjas.at(j)->hit());
                                return;
                            }
                        }
                        for(int l = 0; l < knowledge->teams[k].terminators.count(); l++)
                        {
                            if(knowledge->teams[k].terminators.at(l)->getPosition() == pos && knowledge->teams[k].terminators.at(l)->getHitPoint() > 0)
                            {
                                knowledge->teams[k].terminators.at(l)->damage(knowledge->teams[i].ninjas.at(j)->hit());
                                return;
                            }
                        }
                        for(int l = 0; l < knowledge->teams[k].ninjas.count(); l++)
                        {
                            if(knowledge->teams[k].ninjas.at(l)->getPosition() == pos && knowledge->teams[k].ninjas.at(l)->getHitPoint() > 0)
                            {
                                knowledge->teams[k].ninjas.at(l)->damage(knowledge->teams[i].ninjas.at(j)->hit());
                                return;
                            }
                        }
                        for(int l = 0; l < knowledge->teams[k].explorers.count(); l++)
                        {
                            if(knowledge->teams[k].explorers.at(l)->getPosition() == pos && knowledge->teams[k].explorers.at(l)->getHitPoint() > 0)
                            {
                                knowledge->teams[k].explorers.at(l)->damage(knowledge->teams[i].ninjas.at(j)->hit());
                                return;
                            }
                        }
                    }
                }
            }
        }
        for(int j = 0; j < knowledge->teams[i].explorers.count(); j++)
        {
            if(knowledge->teams[i].explorers.at(j)->getPosition() == pos)
            {
                for(int k = 0; k < 4; k++)
                {
                    if( k != id)
                    {
                        for(int l = 0; l < knowledge->teams[k].predators.count(); l++)
                        {
                            if(knowledge->teams[k].predators.at(l)->getPosition() == pos && knowledge->teams[k].predators.at(l)->getHitPoint() > 0)
                            {
                                knowledge->teams[k].predators.at(l)->damage(knowledge->teams[i].explorers.at(j)->hit());
                                return;
                            }
                        }
                        for(int l = 0; l < knowledge->teams[k].terminators.count(); l++)
                        {
                            if(knowledge->teams[k].terminators.at(l)->getPosition() == pos && knowledge->teams[k].terminators.at(l)->getHitPoint() > 0)
                            {
                                knowledge->teams[k].terminators.at(l)->damage(knowledge->teams[i].explorers.at(j)->hit());
                                return;
                            }
                        }
                        for(int l = 0; l < knowledge->teams[k].ninjas.count(); l++)
                        {
                            if(knowledge->teams[k].ninjas.at(l)->getPosition() == pos && knowledge->teams[k].ninjas.at(l)->getHitPoint() > 0)
                            {
                                knowledge->teams[k].ninjas.at(l)->damage(knowledge->teams[i].explorers.at(j)->hit());
                                return;
                            }
                        }
                        for(int l = 0; l < knowledge->teams[k].explorers.count(); l++)
                        {
                            if(knowledge->teams[k].explorers.at(l)->getPosition() == pos && knowledge->teams[k].explorers.at(l)->getHitPoint() > 0)
                            {
                                knowledge->teams[k].explorers.at(l)->damage(knowledge->teams[i].explorers.at(j)->hit());
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}

void CGame::delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

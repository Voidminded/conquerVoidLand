#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    /* Widgets */
    workspace = new QMdiArea(this);
    setCentralWidget(workspace);

    tabWidget = new CTabDockWidget(0 , true);
    addDockWidget(Qt::LeftDockWidgetArea,tabWidget);

    loadWidget = new CLoadPlayersWidget(this);
    tabWidget->tabs->addTab(loadWidget, "Players");

    mapWidget = new CLoadMapWidget(this);
    tabWidget->tabs->addTab(mapWidget, "Map");

    gameWidget = new CGameWidget(this);
    tabWidget->tabs->addTab(gameWidget, "Game");

    info = new CInfoWidget(this);
    tabWidget->tabs->addTab(info, "Info");

    printer = new CStatusPrinter();

    statusWidget = new CStatusWidget(printer );
    addDockWidget(Qt::BottomDockWidgetArea, statusWidget);
    printer->textBuffer.enqueue(CStatusText("Initializing..."));
    statusUpdateTimer = new QTimer();
    statusUpdateTimer->setInterval(_RATE);
    statusUpdateTimer->start();

    knowledge = new CKnowledge(printer);
    game = new CGame();

    monitorWidget = new CMonitorWidget(this);
    monitorWidget->setWindowTitle(tr("Monitor"));
    workspace->addSubWindow(monitorWidget, Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    monitorWidget->setWindowState(Qt::WindowMaximized );

    /* Connections */
    connect(statusUpdateTimer, SIGNAL(timeout()), statusWidget, SLOT(update()));
    connect(loadWidget->compileButt[0],SIGNAL(clicked()),game,SLOT(compilePlayer1()));
    connect(loadWidget->compileButt[1],SIGNAL(clicked()),game,SLOT(compilePlayer2()));
    connect(loadWidget->compileButt[2],SIGNAL(clicked()),game,SLOT(compilePlayer3()));
    connect(loadWidget->compileButt[3],SIGNAL(clicked()),game,SLOT(compilePlayer4()));
    connect(game,SIGNAL(activateTeam1Label(QString)),loadWidget->activeLabels[0],SLOT(setText(QString)));
    connect(game,SIGNAL(activateTeam2Label(QString)),loadWidget->activeLabels[1],SLOT(setText(QString)));
    connect(game,SIGNAL(activateTeam3Label(QString)),loadWidget->activeLabels[2],SLOT(setText(QString)));
    connect(game,SIGNAL(activateTeam4Label(QString)),loadWidget->activeLabels[3],SLOT(setText(QString)));
    connect(game,SIGNAL(activateTeam(int,bool)),knowledge,SLOT(activateSlot(int,bool)));
    connect(mapWidget,SIGNAL(mapGenerationSignal(int,int,int,int,int)),knowledge,SLOT(generateMap(int,int,int,int,int)));
    connect(knowledge,SIGNAL(updateMonitorView()),monitorWidget,SLOT(updateSize()));
    connect(gameWidget->playPB,SIGNAL(clicked()),game,SLOT(initiateGame()));
}

MainWindow::~MainWindow()
{

}

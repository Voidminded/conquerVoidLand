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
    tabWidget->tabs->addTab(loadWidget, "Load");

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
    workspace->addSubWindow(monitorWidget, Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    monitorWidget->setWindowState(Qt::WindowMaximized );
    /* Connections */
    connect(statusUpdateTimer, SIGNAL(timeout()), statusWidget, SLOT(update()));
    connect(loadWidget->compileButt[0],SIGNAL(clicked()),game,SLOT(compilePlayer1()));
    connect(loadWidget->compileButt[1],SIGNAL(clicked()),game,SLOT(compilePlayer2()));
    connect(loadWidget->compileButt[2],SIGNAL(clicked()),game,SLOT(compilePlayer3()));
    connect(loadWidget->compileButt[3],SIGNAL(clicked()),game,SLOT(compilePlayer4()));
    //test :
}

MainWindow::~MainWindow()
{

}

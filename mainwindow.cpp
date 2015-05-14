#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    /* Widgets */
    workspace = new QMdiArea(this);
    setCentralWidget(workspace);

    printer = new CStatusPrinter();

    statusWidget = new CStatusWidget(printer );
    addDockWidget(Qt::BottomDockWidgetArea, statusWidget);
    printer->textBuffer.enqueue(CStatusText("Initializing..."));
    statusUpdateTimer = new QTimer();
    statusUpdateTimer->setInterval(_RATE);
    statusUpdateTimer->start();

    knowledge = new CKnowledge(printer);

    monitorWidget = new CMonitorWidget(this);
    monitorWidget->setWindowTitle(tr("Monitor"));
    workspace->addSubWindow(monitorWidget, Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    monitorWidget->setWindowState(Qt::WindowMaximized );
    /* Connections */
    connect(statusUpdateTimer, SIGNAL(timeout()), statusWidget, SLOT(update()));
}

MainWindow::~MainWindow()
{

}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "monitorwidget.h"
#include "statuswidget.h"
#include "game.h"
#include "widgets.h"
#include <QMainWindow>
#include <QMdiArea>
#include <QTimer>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QMdiArea *workspace; /**< The workspace to add widgets to it */
    CMonitorWidget *monitorWidget; /**< The monitor widget instance */
    CStatusPrinter *printer; /**< The pointer to status bar printer which will be sent to knowledge constructor */
    CStatusWidget *statusWidget; /**< Status bar */
    CTabDockWidget *tabWidget; /**< The tab widget which you can add regular widgets to it and will make them Doc Tab widget*/
    CLoadPlayersWidget *loadWidget; /**< Player loading widget */
    CLoadMapWidget *mapWidget; /**< Map generation widget */
    CGameWidget *gameWidget; /**< Just have a simple play button FOR NOW! */
    CInfoWidget *info; /**< Game information widget */
    QTimer* statusUpdateTimer; /**< a timer to update the status bar texts */
    CGame* game; /**< Game driver class instance */
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "monitorwidget.h"
#include "statuswidget.h"
#include <QMainWindow>
#include <QMdiArea>
#include <QTimer>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QMdiArea *workspace;
    CMonitorWidget *monitorWidget;
    CStatusPrinter *printer;
    CStatusWidget *statusWidget;
    QTimer* statusUpdateTimer;
};

#endif // MAINWINDOW_H

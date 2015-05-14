#ifndef WIDGETS_H
#define WIDGETS_H

#include "base.h"
#include "knowledge.h"
#include <QTabWidget>
#include <QPushButton>
#include <QWidget>
#include <QDockWidget>
#include <QGridLayout>
#include <QTimer>
#include <QLabel>
#include <QCheckBox>
#include <QFileDialog>

class CTabDockWidget : public QDockWidget
{
    Q_OBJECT
public:
        CTabDockWidget(QWidget* parent , bool autoHideAbility);
        ~CTabDockWidget();
        QTabWidget *tabs;
        QPushButton *btnAutoHide;
        QWidget* w;
        QTimer *hideShowTimer;
        const bool autoHideBool;
        bool isHide , hideable;
signals:
        void closeSignal(bool);
protected:
        void closeEvent(QEvent*);
    public slots:
        void autoHide();
        void setHideable();
};

class CLoadPlayersWidget : public QWidget
{
    Q_OBJECT
public:
    CLoadPlayersWidget(QWidget* parent = 0);
    ~CLoadPlayersWidget();
    QPushButton *compileButt[4];
protected:
    QLabel labels[4];
    QPushButton buttons[4];
    QCheckBox cBoxes[4];
public slots:
    void load1();
    void load2();
    void load3();
    void load4();
};



#endif // WIDGETS_H

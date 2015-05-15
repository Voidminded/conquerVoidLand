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
#include <QComboBox>
#include <QLineEdit>

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
    QLabel *activeLabels[4];
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

class CLoadMapWidget : public QWidget
{
    Q_OBJECT
public:
    CLoadMapWidget(QWidget* parent = 0);
    ~CLoadMapWidget();
    QComboBox *row, *col;
    QLabel *rLabel, *cLabel;
    QLineEdit *gEdit, *pEdit, *rEdit;
    QPushButton *generateMap;
private slots:
    void pbSlot();
signals:
    void mapGenerationSignal(int,int,int,int,int);
};

class CGameWidget : public QWidget
{
    Q_OBJECT
public:
    CGameWidget(QWidget* parent = 0);
    ~CGameWidget();
    QPushButton *playPB;
};


#endif // WIDGETS_H

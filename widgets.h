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

/**
 * @brief
 * Costum widget used to make any widget Docable and add them as new Tab to itself
 */
class CTabDockWidget : public QDockWidget
{
    Q_OBJECT
public:
        /**
         * @brief
         *
         * @param parent
         * @param autoHideAbility = have the auto hide ability or not (as it is still shitty)
         */
        CTabDockWidget(QWidget* parent , bool autoHideAbility);
        ~CTabDockWidget();
        QTabWidget *tabs;
        QPushButton *btnAutoHide; /**< Auto hide button */
        QWidget* w;
        QTimer *hideShowTimer; /**< Used for Auto hide */
        const bool autoHideBool; /**< Used for Auto hide */
        bool isHide , hideable; /**< Used for Auto hide */
signals:
        void closeSignal(bool);
protected:
        void closeEvent(QEvent*);
    public slots:
        void autoHide();
        void setHideable();
};

/**
 * @brief
 * The player's loading widget
 */
class CLoadPlayersWidget : public QWidget
{
    Q_OBJECT
public:
    CLoadPlayersWidget(QWidget* parent = 0);
    ~CLoadPlayersWidget();
    QPushButton *compileButt[4]; /**< Compiling buttons */
    QLabel *activeLabels[4]; /**< The label shows if the player is active */
protected:
    QLabel labels[4];
    QPushButton buttons[4];
    QCheckBox cBoxes[4]; /**< Check boxes */
public slots:
    /**
     * @brief
     * Loads player code and saves it as a new code (the 4 functions should be merged)
     */
    void load1();
    /**
     * @brief
     * Loads player code and saves it as a new code (the 4 functions should be merged)
     */
    void load2();
    /**
     * @brief
     * Loads player code and saves it as a new code (the 4 functions should be merged)
     */
    void load3();
    /**
     * @brief
     * Loads player code and saves it as a new code (the 4 functions should be merged)
     */
    void load4();
};

/**
 * @brief
 * The map loading eidget
 */
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
    /**
     * @brief
     * Update push button slot
     */
    void pbSlot();
signals:
    /**
     * @brief
     * This signal will be sent when we want to update the map and carry the information with itself
     * @param int Row
     * @param int Column
     * @param int Rhodium
     * @param int Platinum
     * @param int Gold
     */
    void mapGenerationSignal(int,int,int,int,int);
};

/**
 * @brief
 * Just have a play button for now
 * Should add pause, Restart, and log the game for play it here
 */
class CGameWidget : public QWidget
{
    Q_OBJECT
public:
    CGameWidget(QWidget* parent = 0);
    ~CGameWidget();
    QPushButton *playPB;
};

/**
 * @brief
 * Information Widget
 */
class CInfoWidget : public QWidget
{
    Q_OBJECT
public:
    CInfoWidget(QWidget* parent = 0);
    ~CInfoWidget();
private:
    QLabel *gLab[4], *pLab[4], *rLab[4], *eR[4], *pR[4], *tR[4], *nR[4];
    QLabel *gLabL[4], *pLabL[4], *rLabL[4], *eRL[4], *pRL[4], *tRL[4], *nRL[4];
    QTimer *updateTimer;
private slots:
    void updateSlot();
};


#endif // WIDGETS_H

#include "widgets.h"

CTabDockWidget::CTabDockWidget(QWidget* parent , bool autoHide)
    : QDockWidget(parent) , autoHideBool(autoHide)
{
    w = new QWidget(this);
    tabs = new QTabWidget(w);
    QGridLayout *layout = new QGridLayout(w);
    tabs->setTabPosition(QTabWidget::East);

    if( autoHide ){
        isHide = hideable = false;
        btnAutoHide = new QPushButton(this);
        hideShowTimer = new QTimer(this);
        btnAutoHide->setText("AutoHide");
        hideShowTimer->setInterval(50);
        connect(hideShowTimer , SIGNAL(timeout()) , this , SLOT(autoHide()));
        connect(btnAutoHide , SIGNAL(clicked()) , this , SLOT(setHideable()));
        layout->addWidget(btnAutoHide , 0 , 0);
        layout->addWidget(tabs , 1 , 0);
    }
    else
        layout->addWidget(tabs,0,0);
    w->setLayout(layout);
//    w->setFixedWidth(300);
    setWidget(w);
}


CTabDockWidget::~CTabDockWidget()
{
    if( autoHideBool ){
        delete hideShowTimer;
        delete btnAutoHide;
    }
    delete tabs;
    delete w;
}

void CTabDockWidget::closeEvent(QEvent*)
{
    emit closeSignal(false);
}

void CTabDockWidget::autoHide(){
    if( !underMouse() && isHide == false ){
        if( tabs->width() > 50 ){
            tabs->setMaximumSize(tabs->width()-40 , height());
            setMaximumSize(tabs->width()+30,height());
        }
        else
            isHide = true;
    }
    else if( underMouse() && isHide ){
        if( width() < 500 ){
            setMaximumSize(tabs->width()+70,height());
            tabs->setMaximumSize(tabs->width()+40,height());
        }
        else
            isHide = false;
    }
}

void CTabDockWidget::setHideable(){
    if( hideable ){
        btnAutoHide->setText("AutoHide");
        hideable = false;
        hideShowTimer->stop();
    }
    else{
        btnAutoHide->setText("AlwaysShow");
        hideable = true;
        hideShowTimer->start();
    }
}

// -------------- Load Players Widget ---------------

CLoadPlayersWidget::CLoadPlayersWidget( QWidget* parent)
    : QWidget(parent)
{
    for(int i = 0; i < 4; i++)
        labels[i].setText(QString("Player %1 :").arg(i+1));
    labels[Cyan].setStyleSheet("QLabel {color : darkcyan}");
    labels[Magenta].setStyleSheet("QLabel {color : darkmagenta}");
    labels[Yellow].setStyleSheet("QLabel {color : orange}");
    labels[Red].setStyleSheet(" QLabel {color : red}");
    QGridLayout *lOut = new QGridLayout(this);
    this->setLayout(lOut);
    for(int i = 0; i < 4; i++)
    {
        lOut->addWidget(&labels[i],(i+1)*2-1,1);
        cBoxes[i].setChecked(false);
        buttons[i].setDisabled(true);
        buttons[i].setText("Browse");
        lOut->addWidget(&cBoxes[i],(i+1)*2-1,0);
        lOut->addWidget(&buttons[i],(i+1)*2-1,2);
        compileButt[i] = new QPushButton("Compile !");
        compileButt[i]->setDisabled(true);
        lOut->addWidget(compileButt[i],(i+1)*2-1,3);
        activeLabels[i] = new QLabel("Disabled");
        lOut->addWidget(activeLabels[i],(i+1)*2,1);
    }

    for(int i = 0; i < 4; i++)
        connect(&cBoxes[i],SIGNAL(clicked(bool)),&buttons[i],SLOT(setEnabled(bool)));
    connect(&buttons[0], SIGNAL(clicked()), this, SLOT(load1()));
    connect(&buttons[1], SIGNAL(clicked()), this, SLOT(load2()));
    connect(&buttons[2], SIGNAL(clicked()), this, SLOT(load3()));
    connect(&buttons[3], SIGNAL(clicked()), this, SLOT(load4()));
}

CLoadPlayersWidget::~CLoadPlayersWidget()
{

}

void CLoadPlayersWidget::load1()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Load Coade"), "./", tr("C++ Files (*.cpp)"));
    if(path != "")
    {
        path.prepend("cp ");
        path.append(" ./player1.cpp");
        system(path.toStdString().c_str());
        compileButt[0]->setEnabled(true);
    }
}

void CLoadPlayersWidget::load2()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Load Coade"), "./", tr("C++ Files (*.cpp)"));
    if(path != "")
    {
        path.prepend("cp ");
        path.append(" ./player2.cpp");
        system(path.toStdString().c_str());
        compileButt[1]->setEnabled(true);
    }
}

void CLoadPlayersWidget::load3()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Load Coade"), "./", tr("C++ Files (*.cpp)"));
    if(path != "")
    {
        path.prepend("cp ");
        path.append(" ./player3.cpp");
        system(path.toStdString().c_str());
        compileButt[2]->setEnabled(true);
    }
}

void CLoadPlayersWidget::load4()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Load Coade"), "./", tr("C++ Files (*.cpp)"));
    if(path != "")
    {
        path.prepend("cp ");
        path.append(" ./player4.cpp");
        system(path.toStdString().c_str());
        compileButt[3]->setEnabled(true);
    }
}

// -------------- Load Map Widget ---------------

CLoadMapWidget::CLoadMapWidget( QWidget* parent)
    : QWidget(parent)
{
    QGridLayout *lOut = new QGridLayout(this);
    this->setLayout(lOut);
    rLabel = new QLabel("Rows : ");
    cLabel = new QLabel("Columns : ");
    row = new QComboBox();
    for(int i = 1; i <= 30; i++)
        row->addItem(QString::number(i));
    col = new QComboBox();
    for(int i = 1; i <= 60; i++)
        col->addItem(QString::number(i));
    col->setCurrentIndex(26);
    row->setCurrentIndex(8);
    lOut->addWidget(rLabel,1,0);
    lOut->addWidget(row,1,1);
    lOut->addWidget(cLabel,1,2);
    lOut->addWidget(col,1,3);
    QLabel *rLab = new QLabel("Rhodium : ");
    rLab->setStyleSheet("QLabel {color : coral}");
    lOut->addWidget(rLab, 3,0);
    rEdit = new QLineEdit("9");
    rEdit->setStyleSheet("QLineEdit {color : coral; background-color : black}");
    lOut->addWidget(rEdit, 3,1);
    QLabel *pLab = new QLabel("Platinum : ");
    pLab->setStyleSheet("QLabel {color : slategray}");
    lOut->addWidget(pLab, 4,0);
    pEdit = new QLineEdit("27");
    pEdit->setStyleSheet("QLineEdit {color : slategray; background-color : black}");
    lOut->addWidget(pEdit, 4,1);
    QLabel *gLab = new QLabel("Gold : ");
    gLab->setStyleSheet("QLabel {color : goldenrod}");
    lOut->addWidget(gLab, 5,0);
    gEdit = new QLineEdit("300");
    gEdit->setStyleSheet("QLineEdit {color : goldenrod; background-color : black}");
    lOut->addWidget(gEdit, 5,1);
    generateMap = new QPushButton("Update");
    lOut->addWidget(generateMap, 6,1);

    connect(generateMap, SIGNAL(clicked()), this,SLOT(pbSlot()));
}

CLoadMapWidget::~CLoadMapWidget()
{

}

void CLoadMapWidget::pbSlot()
{
    emit mapGenerationSignal(
                row->currentIndex()+1
                ,col->currentIndex()+1
                ,rEdit->text().toInt()
                ,pEdit->text().toInt()
                ,gEdit->text().toInt());
}

// -------------- Game Widget ---------------

CGameWidget::CGameWidget( QWidget* parent)
    : QWidget(parent)
{
    QGridLayout *lOut = new QGridLayout(this);
    this->setLayout(lOut);
    playPB = new QPushButton("Play");
    lOut->addWidget(playPB);
}

CGameWidget::~CGameWidget()
{

}

// -------------- Info Widget ---------------

CInfoWidget::CInfoWidget( QWidget* parent)
{
    QGridLayout *lOut = new QGridLayout(this);
    this->setLayout(lOut);
    for(int i = 0; i < 4; i++)
    {
        rLabL[i] = new QLabel("Rhodium : ");
        gLabL[i] = new QLabel("Gold : ");
        pLabL[i] = new QLabel("Platinum : ");
        rLab[i] = new QLabel("0");
        gLab[i] = new QLabel("0");
        pLab[i] = new QLabel("0");
        eRL[i] = new QLabel("Explorers : ");
        eR[i] = new QLabel("0");
        pRL[i] = new QLabel("Predators : ");
        pR[i] = new QLabel("0");
        tRL[i] = new QLabel("Terminators : ");
        tR[i] = new QLabel("0");
        nRL[i] = new QLabel("Ninjas : ");
        nR[i] = new QLabel("0");
    }
    rLabL[Cyan]->setStyleSheet("QLabel {color : darkcyan}");
    gLabL[Cyan]->setStyleSheet("QLabel {color : darkcyan}");
    pLabL[Cyan]->setStyleSheet("QLabel {color : darkcyan}");
    rLab[Cyan]->setStyleSheet("QLabel {color : darkcyan}");
    gLab[Cyan]->setStyleSheet("QLabel {color : darkcyan}");
    pLab[Cyan]->setStyleSheet("QLabel {color : darkcyan}");
    eRL[Cyan]->setStyleSheet("QLabel {color : darkcyan}");
    eR[Cyan]->setStyleSheet("QLabel {color : darkcyan}");
    pRL[Cyan]->setStyleSheet("QLabel {color : darkcyan}");
    pR[Cyan]->setStyleSheet("QLabel {color : darkcyan}");
    tRL[Cyan]->setStyleSheet("QLabel {color : darkcyan}");
    tR[Cyan]->setStyleSheet("QLabel {color : darkcyan}");
    nRL[Cyan]->setStyleSheet("QLabel {color : darkcyan}");
    nR[Cyan]->setStyleSheet("QLabel {color : darkcyan}");

    rLabL[Magenta]->setStyleSheet("QLabel {color : darkmagenta}");
    gLabL[Magenta]->setStyleSheet("QLabel {color : darkmagenta}");
    pLabL[Magenta]->setStyleSheet("QLabel {color : darkmagenta}");
    rLab[Magenta]->setStyleSheet("QLabel {color : darkmagenta}");
    gLab[Magenta]->setStyleSheet("QLabel {color : darkmagenta}");
    pLab[Magenta]->setStyleSheet("QLabel {color : darkmagenta}");
    eRL[Magenta]->setStyleSheet("QLabel {color : darkmagenta}");
    eR[Magenta]->setStyleSheet("QLabel {color : darkmagenta}");
    pRL[Magenta]->setStyleSheet("QLabel {color : darkmagenta}");
    pR[Magenta]->setStyleSheet("QLabel {color : darkmagenta}");
    tRL[Magenta]->setStyleSheet("QLabel {color : darkmagenta}");
    tR[Magenta]->setStyleSheet("QLabel {color : darkmagenta}");
    nRL[Magenta]->setStyleSheet("QLabel {color : darkmagenta}");
    nR[Magenta]->setStyleSheet("QLabel {color : darkmagenta}");

    rLabL[Yellow]->setStyleSheet("QLabel {color : orange}");
    gLabL[Yellow]->setStyleSheet("QLabel {color : orange}");
    pLabL[Yellow]->setStyleSheet("QLabel {color : orange}");
    rLab[Yellow]->setStyleSheet("QLabel {color : orange}");
    gLab[Yellow]->setStyleSheet("QLabel {color : orange}");
    pLab[Yellow]->setStyleSheet("QLabel {color : orange}");
    eRL[Yellow]->setStyleSheet("QLabel {color : orange}");
    eR[Yellow]->setStyleSheet("QLabel {color : orange}");
    pRL[Yellow]->setStyleSheet("QLabel {color : orange}");
    pR[Yellow]->setStyleSheet("QLabel {color : orange}");
    tRL[Yellow]->setStyleSheet("QLabel {color : orange}");
    tR[Yellow]->setStyleSheet("QLabel {color : orange}");
    nRL[Yellow]->setStyleSheet("QLabel {color : orange}");
    nR[Yellow]->setStyleSheet("QLabel {color : orange}");

    rLabL[Red]->setStyleSheet(" QLabel {color : red}");
    gLabL[Red]->setStyleSheet(" QLabel {color : red}");
    pLabL[Red]->setStyleSheet(" QLabel {color : red}");
    rLab[Red]->setStyleSheet(" QLabel {color : red}");
    gLab[Red]->setStyleSheet(" QLabel {color : red}");
    pLab[Red]->setStyleSheet(" QLabel {color : red}");
    eRL[Red]->setStyleSheet(" QLabel {color : red}");
    eR[Red]->setStyleSheet(" QLabel {color : red}");
    pRL[Red]->setStyleSheet(" QLabel {color : red}");
    pR[Red]->setStyleSheet(" QLabel {color : red}");
    tRL[Red]->setStyleSheet(" QLabel {color : red}");
    tR[Red]->setStyleSheet(" QLabel {color : red}");
    nRL[Red]->setStyleSheet(" QLabel {color : red}");
    nR[Red]->setStyleSheet(" QLabel {color : red}");

    for(int i = 0; i < 2; i++)
    {
        lOut->addWidget(rLabL[i],0,i*2);
        lOut->addWidget(rLab[i],0,(i*2)+1);
        lOut->addWidget(pLabL[i],1,i*2);
        lOut->addWidget(pLab[i],1,(i*2)+1);
        lOut->addWidget(gLabL[i],2,i*2);
        lOut->addWidget(gLab[i],2,(i*2)+1);
        lOut->addWidget(eRL[i],3,i*2);
        lOut->addWidget(eR[i],3,(i*2)+1);
        lOut->addWidget(nRL[i],4,i*2);
        lOut->addWidget(nR[i],4,(i*2)+1);
        lOut->addWidget(tRL[i],5,i*2);
        lOut->addWidget(tR[i],5,(i*2)+1);
        lOut->addWidget(pRL[i],6,i*2);
        lOut->addWidget(pR[i],6,(i*2)+1);
    }

    for(int i = 0; i < 2; i++)
    {
        lOut->addWidget(rLabL[i+2],7,i*2);
        lOut->addWidget(rLab[i+2],7,(i*2)+1);
        lOut->addWidget(pLabL[i+2],8,i*2);
        lOut->addWidget(pLab[i+2],8,(i*2)+1);
        lOut->addWidget(gLabL[i+2],9,i*2);
        lOut->addWidget(gLab[i+2],9,(i*2)+1);
        lOut->addWidget(eRL[i+2],10,i*2);
        lOut->addWidget(eR[i+2],10,(i*2)+1);
        lOut->addWidget(nRL[i+2],11,i*2);
        lOut->addWidget(nR[i+2],11,(i*2)+1);
        lOut->addWidget(tRL[i+2],12,i*2);
        lOut->addWidget(tR[i+2],12,(i*2)+1);
        lOut->addWidget(pRL[i+2],13,i*2);
        lOut->addWidget(pR[i+2],13,(i*2)+1);
    }
    updateTimer = new QTimer();
    updateTimer->setInterval(_RATE);
    updateTimer->start();
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(updateSlot()));
}

CInfoWidget::~CInfoWidget()
{

}

void CInfoWidget::updateSlot()
{
    for(int i = 0; i < 4; i++)
    {
        rLab[i]->setText(QString::number(knowledge->teams[i].rhodium));
        gLab[i]->setText(QString::number(knowledge->teams[i].gold));
        pLab[i]->setText(QString::number(knowledge->teams[i].platinum));
        eR[i]->setText(QString::number(knowledge->teams[i].explorers.count()));
        pR[i]->setText(QString::number(knowledge->teams[i].predators.count()));
        tR[i]->setText(QString::number(knowledge->teams[i].terminators.count()));
        nR[i]->setText(QString::number(knowledge->teams[i].ninjas.count()));
    }
}

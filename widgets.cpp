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

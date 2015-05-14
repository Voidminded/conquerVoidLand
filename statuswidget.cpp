#include "statuswidget.h"

CStatusWidget::CStatusWidget(CStatusPrinter* _statusPrinter)
{
    statusPrinter = _statusPrinter;
    logTime.start();
    this->setAllowedAreas(Qt::BottomDockWidgetArea);
    this->setFeatures(QDockWidget::NoDockWidgetFeatures);
    statusText = new QTextEdit(this);
    titleLbl = new QLabel(tr("Messages"));
    statusText->setMaximumWidth(1000);
    QWidget* w = new QWidget(this);
    statusText->setFixedSize(600, 200);
    QGridLayout* layout = new QGridLayout(w);
    layout->addWidget(statusText, 0, 0);
    layout->setAlignment(statusText, Qt::AlignLeft);
    layout->setColumnMinimumWidth(0, 500);
    statusText->resize(1000, 200);
    w->setLayout(layout);
    this->setSizeIncrement(this->width(), 100);
    statusText->setReadOnly(true);

//    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setWidget(w);
}

CStatusWidget::~CStatusWidget()
{
    delete statusText;
    delete titleLbl;
}

void CStatusWidget::write(QString str, QColor color)
{
    if( statusText->textCursor().blockNumber() > 1000 )
        statusText->clear();

    statusText->setTextColor(color);
    statusText->append(QString::number(logTime.elapsed()) + " : " + str);
    statusText->setTextColor(QColor("black"));
}

void CStatusWidget::update()
{
    CStatusText text;
    while(!statusPrinter->textBuffer.isEmpty())
    {
        text = statusPrinter->textBuffer.dequeue();
        write(text.text, text.color);
    }
}

void CStatusWidget::closeEvent(QEvent*)
{
    emit closeSignal(false);
}


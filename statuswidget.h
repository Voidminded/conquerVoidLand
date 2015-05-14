#ifndef CSTATUSWIDGET_H
#define CSTATUSWIDGET_H

#include <QDockWidget>
#include <QTextEdit>
#include <QTime>
#include <QLabel>
#include <QGridLayout>
#include <QQueue>

class CStatusText
{
    public:
    CStatusText(QString _text = "", QColor _color = QColor("black"), int _size = 12)
    {
        text= _text;
        color = _color;
        size = _size;
    }

    QString text;
    QColor color;
    int size;
};

class CStatusPrinter
{
    public:
    CStatusPrinter() {}

    QQueue<CStatusText> textBuffer;
};

class CStatusWidget : public QDockWidget
{
    Q_OBJECT
public:
    CStatusWidget(CStatusPrinter* _statusPrinter);
    ~CStatusWidget();
    QTextEdit *statusText;
    QLabel *titleLbl;
    QTextDocument content;

public slots:
    void write(QString str, QColor color = QColor("black"));
    void update();

private:
    CStatusPrinter *statusPrinter;
    QTime logTime;

signals:
    void closeSignal(bool);

protected:
    void closeEvent(QEvent*);
};

#endif // CSTATUSWIDGET_H

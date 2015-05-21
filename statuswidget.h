#ifndef CSTATUSWIDGET_H
#define CSTATUSWIDGET_H

#include <QDockWidget>
#include <QTextEdit>
#include <QTime>
#include <QLabel>
#include <QGridLayout>
#include <QQueue>

/**
 * @brief
 * A class as a data type for texts used in Status Widget
 */
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

/**
 * @brief
 * Just a queue, implemeted as class so that I can add 4 different Queues for each player later (that was the idea)
 */
class CStatusPrinter
{
    public:
    CStatusPrinter() {}

    QQueue<CStatusText> textBuffer; /**< TODO */
};

class CStatusWidget : public QDockWidget
{
    Q_OBJECT
public:
    CStatusWidget(CStatusPrinter* _statusPrinter);
    ~CStatusWidget();
    QTextEdit *statusText; /**< Text area */
    QLabel *titleLbl;
    QTextDocument content; /**< Text is stored in this document */

public slots:
    void write(QString str, QColor color = QColor("black"));
    /**
     * @brief
     * updates the status bar information
     */
    void update();

private:
    CStatusPrinter *statusPrinter;
    QTime logTime; /**< Time from start of program, is printed before each output in status bar */

signals:
    /**
     * @brief
     * Not used in this version
     * @param bool
     */
    void closeSignal(bool);

protected:
    /**
     * @brief
     * emmits the closeSignal
     * @param
     */
    void closeEvent(QEvent*);
};

#endif // CSTATUSWIDGET_H

#ifndef CLOGMSGBOX_H
#define CLOGMSGBOX_H

#include <QWidget>
#include <QTextEdit>
#include <QColor>

class CLogMsgBox : public QTextEdit
{
    Q_OBJECT


    Q_PROPERTY(QColor color_time READ _getTimeColor WRITE _setTimeColor)

public:
    enum NEXTLINE {LINE_CURRENT = 0, LINE_NEWLINE};

public:
    CLogMsgBox(QWidget *parent = 0);
    void _putMsg(const QString& msg, const QColor& color = QColor(0,0,0), NEXTLINE newLine = LINE_NEWLINE);
    void _setTimeColor(const QColor& color);
    QColor _getTimeColor();
private:
    void append(const QString &text);
    QColor color_time;

};

#endif

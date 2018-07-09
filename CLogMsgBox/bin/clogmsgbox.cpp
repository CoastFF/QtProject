#include "clogmsgbox.h"
#include <QTime>
#include <QApplication>
CLogMsgBox::CLogMsgBox(QWidget *parent) :
    QTextEdit(parent)
{
    color_time = QColor(0,0,255);
}

void CLogMsgBox::_putMsg(const QString &msg, const QColor &color, NEXTLINE newLine)
{
    moveCursor(QTextCursor::End);
    if(msg.contains("\n"))
    {
        QStringList strlst = msg.split('\n');
        foreach(QString str,strlst)
        {
            _putMsg(str, color, NEXTLINE::LINE_NEWLINE);
        }
    }
    else
    {
        if((qint32)newLine != 0)
        {
            QString tmp = QTime::currentTime().toString("HH:mm:ss ");
            setTextColor(color_time);
            QTextEdit::append(tmp);
        }
        setTextColor(color);
        append(msg);
    }
}

void CLogMsgBox::_setTimeColor(const QColor &color)
{
    color_time = color;
}

QColor CLogMsgBox::_getTimeColor()
{
    return color_time;
}

void CLogMsgBox::append(const QString &text)
{
    QTextEdit::append(text);
    setEnabled(false);
    QApplication::processEvents();
    moveCursor(QTextCursor::StartOfLine);
    textCursor().deletePreviousChar();
    moveCursor(QTextCursor::EndOfLine);
    setEnabled(true);
}

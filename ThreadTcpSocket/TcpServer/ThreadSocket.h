#ifndef THREADSOCKET_H
#define THREADSOCKET_H

#include <QThread>
#include <QTcpSocket>
#include <QMutex>

class ThreadSocket : public QThread
{
    Q_OBJECT
public:
    ThreadSocket(QTcpSocket *socket);
    void run();
private:
    QTcpSocket* m_socket;
    ThreadSocket* m_thread;
    bool m_can_stop;
    QMutex mutex;

private slots:
    void slot_socket_readyRead();
    void slot_thread_run_finished();
    void slot_emit_signal(QByteArray ba);
    void slot_stop_thread();

signals:
    void newMsg(QByteArray msg);
};

#endif // THREADSOCKET_H

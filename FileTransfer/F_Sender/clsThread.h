#ifndef CLSTHREAD_H
#define CLSTHREAD_H

#include <QObject>
#include <QThread>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include "clsTransaction.h"
#include <QTcpSocket>
class clsThread : public QThread
{
    Q_OBJECT
public:
    clsThread();
    ~clsThread();
    addTransaction(clsTransaction* ts);
signals:
    void AllTransactionEnd();
    void sig_out(clsTransaction::SIGNALS sig);
    void sig_out_connected();
public slots:
    void on_transaction_finished(clsTransaction* ts);
protected:
    void run();
private:
    QQueue<clsTransaction*> queue;
    QMutex mutex;
    QWaitCondition wc_QueueIsNotEmpty;
    QTcpSocket* socket;
    clsTransaction* ts;
};



#endif // CLSTHREAD_H

#include "clsThread.h"
#include <QDebug>
clsThread::clsThread()
{

}

clsThread::~clsThread()
{
    if(socket)
    {
        socket->deleteLater();
    }
}

clsThread::addTransaction(clsTransaction *ts)
{
    mutex.lock();
    queue.enqueue(ts);//qDebug()<<"ts:"<<ts->getEndThread();
    wc_QueueIsNotEmpty.wakeAll();
    mutex.unlock();
    //qDebug()<<"added ts";
}

void clsThread::run()
{
    socket = new QTcpSocket;
    qDebug()<<socket->thread();
    qDebug()<<"run:"<<QThread::currentThread();
    while(true)
    {
        mutex.lock();
        if(queue.count() == 0)
        {
            wc_QueueIsNotEmpty.wait(&mutex);
        }
        ts = queue.dequeue();
        bool is_stop = ts->getEndThread();qDebug()<<"is_stop"<<is_stop;
        //connect(ts,SIGNAL(TransactionEnd(clsTransaction*)),this,SLOT(on_transaction_finished(clsTransaction*)));
        connect(ts,SIGNAL(sig_out(clsTransaction::SIGNALS)),this,SIGNAL(sig_out(clsTransaction::SIGNALS)));
        connect(ts,SIGNAL(sig_out_connected()),this,SIGNAL(sig_out_connected()));
        if(is_stop)
        {
            qDebug()<<"end transaction detected";
            break;
        }
        ts->execute(socket);qDebug()<<"executed finished";
        if(queue.count() == 0)
        {
            emit AllTransactionEnd();
        }
        mutex.unlock();
        //delete ts;
    }
}

void clsThread::on_transaction_finished(clsTransaction *ts)
{
    qDebug()<<"delete ts";
    delete ts;
}

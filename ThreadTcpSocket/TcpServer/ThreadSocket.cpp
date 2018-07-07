#include "ThreadSocket.h"
#include <QDebug>
#include <QApplication>
#include <QMetaType>
#include <QMutexLocker>
ThreadSocket::ThreadSocket(QTcpSocket *socket)
{
    this->m_socket = socket;
    connect(this,SIGNAL(finished()),this,SLOT(slot_thread_run_finished()));
    //qRegisterMetaType<QByteArray>("QByteArray");
    moveToThread(this);
    m_can_stop = false;

}

void ThreadSocket::run()
{
    qDebug()<<"thread->run functon, threadId"<<QThread::currentThreadId();
    connect(m_socket,SIGNAL(readyRead()),this,SLOT(slot_socket_readyRead()));
    exec();
    /*forever
    {
        QApplication::processEvents();
        QMutexLocker locker(&mutex);
        if(m_can_stop)
        {
            break;
        }
    }*/
}

void ThreadSocket::slot_socket_readyRead()
{
    qDebug()<<"readyread thread id"<<QThread::currentThreadId();
    QByteArray msg = m_socket->readAll();
    emit newMsg(msg);
}

void ThreadSocket::slot_thread_run_finished()
{
    qDebug()<<"finished thread id"<<QThread::currentThreadId();
}

void ThreadSocket::slot_emit_signal(QByteArray ba)
{
    emit newMsg(ba);
}

void ThreadSocket::slot_stop_thread()
{
    exit(0);

    QMutexLocker locker(&mutex);
    m_can_stop = true;
    qDebug()<<"terminate thread id"<<QThread::currentThreadId();
    this->terminate();
    //moveToThread(NULL);
}

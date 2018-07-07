#include "clsTransaction.h"
#include <QFile>
#include <QFileInfo>
#include <QDataStream>
#include <QCoreApplication>
#include <QHostAddress>
#include <QThread>
clsTransaction::clsTransaction(QString filePath, clsTransaction::Option opt, QString reserved, bool endThread)
{
    //this->socket = socket;
    this->filePath = filePath;
    this->opt = opt;
    this->endThread = endThread;
    this->reserved = reserved;
    /*if(socket)
    {
        connect(socket,SIGNAL(bytesWritten(qint64)),this,SLOT(on_socket_bytesWritten(qint64)));
    }*/
    leftBytes = 0;
    totalBytes = 0;
    writtenBytes = 0;
}

clsTransaction::~clsTransaction()
{
    qDebug()<<"delete---------------------------------------------";
    //disconnect(socket,SIGNAL(bytesWritten(qint64)),this,SLOT(on_socket_bytesWritten(qint64)));
}

bool clsTransaction::getEndThread()
{
    return endThread;
}

QString clsTransaction::execute(QTcpSocket *socket)
{
    connect(socket,SIGNAL(bytesWritten(qint64)),this,SLOT(on_socket_bytesWritten(qint64)));
    switch(opt)
    {
    case SEND:
        sendFile(socket);
        break;
    case DELETE:
        qDebug()<<"move to thread";
        socket->moveToThread(qApp->thread());
        qDebug()<<"move finished";
        break;
    case CLOSE:
        qDebug()<<"disconnectformhost";
        socket->disconnectFromHost();
        //socket->close();
        qDebug()<<"disconnectformhost finished";
    case CONNECT:
        connectToHost(socket,reserved);
        break;
    default:
        break;
    }
    QString str= "a";
    qDebug()<<"return execute with a str";
    return str;
}

void clsTransaction::on_socket_bytesWritten(qint64 bw)
{
    writtenBytes += bw;
    emit ProcessStatus(writtenBytes, totalBytes);
    qDebug()<<"for now"<<writtenBytes;
    if(writtenBytes == totalBytes)
    {
        qDebug()<<"all total";
        emit TransactionEnd(this);
    }
}

void clsTransaction::sendFile(QTcpSocket *socket)
{
    QFile file(this->filePath);
    if(!file.open(QFile::ReadOnly))
    {
        return;
    }
    QFileInfo fi(file);
    QByteArray ba;
    QDataStream ds(&ba,QIODevice::WriteOnly);
    ds<<(qint64)0<<(qint64)0<<fi.fileName();

    qint64 length_fileName = ba.size() - 2 * sizeof(qint64);
    //ds<<file.readAll();
    totalBytes = leftBytes = ba.size() + fi.size();
    ds.device()->seek(0);
    ds<<totalBytes<<length_fileName;


    leftBytes -= socket->write(ba);

    QByteArray block_tmp;
    while(leftBytes > 0)
    {
        qint64 BytesWait = qMin(leftBytes,C_PAYLOAD_SIZE);
        block_tmp = file.read(BytesWait);
        leftBytes -= socket->write(block_tmp);

        block_tmp.resize(0);
    }
    socket->waitForBytesWritten(30000);
    //file.close();
    qDebug()<<"currThr"<<socket->thread();
}

void clsTransaction::connectToHost(QTcpSocket *socket, QString str)
{
    QStringList lst = reserved.split("#@@#");
    QString ip = lst.at(0);
    int port = lst.at(1).toInt();
    this->soc_ket = socket;
    connect(soc_ket,SIGNAL(connected()),this,SIGNAL(sig_out_connected()));
    soc_ket->connectToHost(ip,port);
    soc_ket->waitForConnected(1000);
    qDebug()<<ip<<"--------"<<QThread::currentThread()<<"------------------"<<port;
}























#ifndef CLSTRANSACTION_H
#define CLSTRANSACTION_H

#include <QObject>
#include <QTcpSocket>
//#include <clsThread.h>
class clsTransaction : public QObject
{
    Q_OBJECT
public:
    enum Option{SEND = 1,DELETE = 2,CLOSE = 3,CONNECT = 4};
    enum SIGNALS{CONNECTED = 1,WRITE_FINISHED = 2};
    explicit clsTransaction(QString filePath, Option opt = SEND, QString reserved = QString(""), bool endThread = false);
    ~clsTransaction();
    bool getEndThread();

signals:
    void ProcessStatus(qint64 bw, qint64 total);
    void TransactionEnd(clsTransaction* ts);

    void sig_out(clsTransaction::SIGNALS sig);
    void sig_out_connected();
public slots:
    QString execute(QTcpSocket* socket);
    void on_socket_bytesWritten(qint64 bw);
private:
    QTcpSocket* soc_ket;
    QString filePath;
    Option opt;
    bool endThread;

    void sendFile(QTcpSocket *socket);
    void connectToHost(QTcpSocket* socket,QString str);
    const qint64 C_PAYLOAD_SIZE = 64*1024;
    qint64 totalBytes;
    qint64 leftBytes;
    qint64 writtenBytes;
    QString reserved;

};

#endif // CLSTRANSACTION_H

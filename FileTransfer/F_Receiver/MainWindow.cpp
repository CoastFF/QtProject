#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDataStream>
#include <QFile>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&socket_server,SIGNAL(newConnection()),this,SLOT(on_socket_server_newConnection()));
    totalBytes = leftBytes = fileLength = 0;
    readyReadFileContent = false;
    folder = "i:\\tmp";
    setGeometry(125,200,width(),height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BtnP_Listen_clicked()
{
    if(ui->BtnP_Listen->text()!="Close")
    {
        int port = ui->EdtL_Port->text().toInt();
        socket_server.listen(QHostAddress::Any, port);
        ui->BtnP_Listen->setText("Close");
    }else
    {
        if(socket_client)
        {
            socket_client->deleteLater();
        }
        socket_server.close();
        ui->BtnP_Listen->setText("Listen");
        setWindowTitle("closed");
    }

}

void MainWindow::on_socket_server_newConnection()
{
    socket_client = socket_server.nextPendingConnection();
    connect(socket_client,SIGNAL(readyRead()),this,SLOT(on_socket_client_readRead()));
    connect(socket_client,SIGNAL(disconnected()),this,SLOT(on_socket_client_disconnected()));
    setWindowTitle("someone is connected to this host");
}

void MainWindow::on_socket_client_readRead()
{
    qDebug()<<"rey";
    if(!readyReadFileContent)
    {
        if(socket_client->bytesAvailable() < sizeof(qint64) * 2 && fileLength == 0)
        {
            return;
        }

        if(fileLength == 0)
        {
            QDataStream ds(socket_client);
            ds>>totalBytes>>fileLength;
            leftBytes = totalBytes - sizeof(qint64) * 2;
        }
        if(socket_client->bytesAvailable() >= fileLength)
        {
            QDataStream ds(socket_client);
            ds>>fileName;
            leftBytes = leftBytes - fileLength;
            file = new QFile(folder +"\\" +fileName);
            if(file->open(QFile::WriteOnly))
            {
                readyReadFileContent = true;
            }
            else
            {
                return;
            }
        }
    }else
    {
        while(leftBytes > 0)
        {
            qint64 bufferCount = socket_client->bytesAvailable();
            if(bufferCount == 0) return;//qDebug()<<leftBytes<<"---"<<bufferCount;
            QByteArray tmp = socket_client->read(bufferCount);
            leftBytes -= bufferCount;
            file->write(tmp);
            if(leftBytes == 0)
            {
                file->close();
                readyReadFileContent = false;
                fileLength = 0;
                setWindowTitle("file saved to:" + file->fileName());
            }
        }
    }
}

void MainWindow::on_socket_client_disconnected()
{
    setWindowTitle("someone disconnected");
}















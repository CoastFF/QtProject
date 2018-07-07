#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <QMetaMethod>
#include <QLabel>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->BtnP_Send->setEnabled(false);
    //connect(&socket,SIGNAL(connected()),this,SLOT(on_socket_connected()));
    //connect(&socket,SIGNAL(disconnected()),this,SLOT(on_socket_disconnected()));
    setGeometry(750,200,width(),height());
    totalBytes = leftBytes = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BtnP_Connect_clicked()
{
    if(ui->BtnP_Connect->text()!= "Connect")
    {
        //clsTransaction* ts = new clsTransaction(NULL,NULL,clsTransaction::CLOSE);
        //clsTransaction* ts = new clsTransaction(NULL,NULL,clsTransaction::DELETE);
        //thread.addTransaction(ts);
        //socket.moveToThread(QThread::currentThread());
        //socket.close();
        setWindowTitle("disconnected");
        //ui->BtnP_Connect->setText("Connect");
        return;
    }
    QString ip = ui->EdtL_ip->text().trimmed();
    QString port = ui->EdtL_port->text().trimmed();
    if(ip.length() >0 && port.length() > 0)
    {
        clsTransaction* ts = new clsTransaction(NULL,clsTransaction::CONNECT,ip +"#@@#"+ port);
        thread.addTransaction(ts);
        connect(&thread,SIGNAL(sig_out(clsTransaction::SIGNALS)),this,SLOT(on_thread_sigout(clsTransaction::SIGNALS)));
        connect(&thread,SIGNAL(sig_out_connected()),this,SLOT(on_socket_connected()));
        thread.start();
        qDebug()<<"Main"<<QThread::currentThread();
    }    
}

void MainWindow::on_BtnP_Send_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"select a file to send:");
    QFile file(fileName);
    if(file.exists())
    {
        QFileInfo fi(file);
        clsTransaction* ts = new clsTransaction(fi.absoluteFilePath(),clsTransaction::SEND);
        thread.addTransaction(ts);





        /*if(!file.open(QFile::ReadOnly))
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

        leftBytes -= socket.write(ba);

        QByteArray block_tmp;
        while(leftBytes > 0)
        {
            qint64 BytesWait = qMin(leftBytes,C_PAYLOAD_SIZE);
            block_tmp = file.read(BytesWait);
            leftBytes -= socket.write(block_tmp);
            block_tmp.resize(0);
        }*/
    }
}

void MainWindow::on_socket_connected()
{
    qDebug()<<"++++++++++++++++++++++++++++++++";
    ui->BtnP_Connect->setText("DisConnect");
    ui->BtnP_Send->setEnabled(true);
    setWindowTitle("connected");
    //thread.start();
}

void MainWindow::on_socket_disconnected()
{
    ui->BtnP_Connect->setText("Connect");
    ui->BtnP_Send->setEnabled(false);//qDebug()<<"add true transaction";
    clsTransaction* ts = new clsTransaction(NULL,clsTransaction::SEND,"",true);
    thread.addTransaction(ts);
}

void MainWindow::on_thread_sigout(clsTransaction::SIGNALS sig)
{
    switch(sig)
    {
    case clsTransaction::CONNECTED:
        ui->BtnP_Connect->setText("DisConnect");
        ui->BtnP_Send->setEnabled(true);
        setWindowTitle("connected");
        break;
    case clsTransaction::WRITE_FINISHED:
        break;
    default:
        break;
    }
}

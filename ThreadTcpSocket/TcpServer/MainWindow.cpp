#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ThreadSocket.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->btn_send->setEnabled(false);
    qDebug()<<"Main-Thread id"<<QThread::currentThreadId();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_start_clicked()
{
    int port = ui->ledt_port->text().toInt();
    if(m_tcp_server.listen(QHostAddress::Any, port))
    {
        connect(&m_tcp_server,SIGNAL(newConnection()),SLOT(slot_tcp_server_newConnection()));
        ui->btn_start->setEnabled(false);
        ui->btn_send->setEnabled(true);
        ui->tedt_log->append("server start listening ...");
    }
    else
    {
        ui->tedt_log->append("server start listening failed...");
    }
}

void MainWindow::on_btn_send_clicked()
{
    QByteArray ba = ui->ledt_msg->text().toLatin1();
    foreach(QTcpSocket* socket, m_lst_socket)
    {
        socket->write(ba);
    }
}

void MainWindow::slot_tcp_server_newConnection()
{
    while(m_tcp_server.hasPendingConnections())
    {
        QTcpSocket* socket_accepted =m_tcp_server.nextPendingConnection();
        ui->tedt_log->append("New Connection...");
        m_lst_socket.append(socket_accepted);
        ThreadSocket* thread = new ThreadSocket(socket_accepted);
        connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
        connect(thread,SIGNAL(newMsg(QByteArray)),this,SLOT(slot_thread_socket_newMsg(QByteArray)));
        connect(this,SIGNAL(destroyed()),thread,SLOT(slot_stop_thread()));
        thread->start();
    }
}

void MainWindow::slot_thread_socket_newMsg(QByteArray ba)
{
    //QMessageBox::information(this,"received msg","hehe","OK");
    QString str = QString::fromLatin1(ba);
    ui->tedt_log->append(str);
}

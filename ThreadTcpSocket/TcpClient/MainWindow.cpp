#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->btn_send->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_connect_clicked()
{
    QHostAddress ha(ui->ledt_remote_ip->text());
    quint16 port = ui->ledt_remote_port->text().toInt();
    m_tcp_client.connectToHost(ha,port);
    connect(&m_tcp_client,SIGNAL(readyRead()),SLOT(slot_tcp_client_readyRead()));
    ui->btn_send->setEnabled(true);
    ui->btn_connect->setEnabled(false);
}

void MainWindow::on_btn_send_clicked()
{
    QByteArray ba = ui->ledt_msg->text().toLatin1();
    m_tcp_client.write(ba);
}

void MainWindow::slot_tcp_client_readyRead()
{
    QByteArray ba = m_tcp_client.readAll();
    ui->tedt_log->append(QString::fromLatin1(ba));
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_btn_start_clicked();

    void on_btn_send_clicked();

    void slot_tcp_server_newConnection();
    void slot_thread_socket_newMsg(QByteArray ba);

private:
    Ui::MainWindow *ui;
    QTcpServer m_tcp_server;
    QList<QTcpSocket*> m_lst_socket;
};

#endif // MAINWINDOW_H

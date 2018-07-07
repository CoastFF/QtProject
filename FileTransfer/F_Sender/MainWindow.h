#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include "clsThread.h"
#include "clsTransaction.h"
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
    void on_BtnP_Connect_clicked();

    void on_BtnP_Send_clicked();

    void on_socket_connected();
    void on_socket_disconnected();

    void on_thread_sigout(clsTransaction::SIGNALS sig);

private:
    Ui::MainWindow *ui;
    QTcpSocket socket;
    clsThread thread;
    const qint64 C_PAYLOAD_SIZE = 64 * 1024;
    qint64 totalBytes;
    qint64 leftBytes;
};

#endif // MAINWINDOW_H

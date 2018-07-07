#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
class QFile;
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
    void on_BtnP_Listen_clicked();
    void on_socket_server_newConnection();
    void on_socket_client_readRead();
    void on_socket_client_disconnected();

private:
    Ui::MainWindow *ui;
    QTcpServer socket_server;
    QTcpSocket* socket_client;

    qint64 totalBytes;
    qint64 leftBytes;
    qint64 fileLength;
    QString folder;
    QString fileName;
    QFile* file;
    bool readyReadFileContent;
};

#endif // MAINWINDOW_H

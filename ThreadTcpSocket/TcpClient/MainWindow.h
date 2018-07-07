#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

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
    void on_btn_connect_clicked();

    void on_btn_send_clicked();
    void slot_tcp_client_readyRead();

private:
    Ui::MainWindow *ui;
    QTcpSocket m_tcp_client;
};

#endif // MAINWINDOW_H

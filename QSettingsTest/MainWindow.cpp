#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSettings settings("CoastFF","QSettings Test App");
    settings.beginGroup("positions");
    QRect rect = settings.value("last pos").toRect();
    settings.endGroup();
    this->setGeometry(rect);
    setWindowTitle("reg saved");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnP_Save_Reg_clicked()
{
    QSettings settings("CoastFF","QSettings Test App");
    settings.beginGroup("positions");
    settings.setValue("last pos",this->geometry());
    settings.endGroup();
    setWindowTitle("reg saved");
}

void MainWindow::on_btnP_Save_Ini_clicked()
{
    QSettings settings("./config.ini",QSettings::IniFormat);
    settings.beginGroup("positions");
    settings.setValue("last pos","xy");
    settings.endGroup();
    setWindowTitle("ini saved");
}

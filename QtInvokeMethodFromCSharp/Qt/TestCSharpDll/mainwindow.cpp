#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

#pragma comment(lib,"E:/SourceCode/Qt/TestCSharpDll/CppDll.lib")

__declspec(dllimport) int api_add(int a, int b);
__declspec(dllimport) void api_substract(int a, int b, int* c);
__declspec(dllimport) void api_showBox(const char* content);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnP_Add_clicked()
{
    int a = ui->edtL_Add_One->text().toInt();
    int b = ui->edtL_Add_Two->text().toInt();
    QString str = QString::number(api_add(a, b));
    QMessageBox::information(this,"call add from dll",str);
}

void MainWindow::on_btnP_Sub_clicked()
{
    int a = ui->edtL_Sub_One->text().toInt();
    int b = ui->edtL_Sub_Two->text().toInt();
    int c = 0;
    api_substract(a, b, &c);
    QString str = QString::number(c);
    QMessageBox::information(this,"call substract from dll",str);
}

void MainWindow::on_btnP_ShowBox_clicked()
{
    QString str = ui->edtL_Content->text();
    api_showBox(str.toLocal8Bit().data());
}

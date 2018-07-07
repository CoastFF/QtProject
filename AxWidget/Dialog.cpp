#include "Dialog.h"
#include "ui_Dialog.h"
#include <QAxWidget>
#include <QAxObject>
#include <QFile>
#include <QTextStream>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);


    QAxWidget* flash = new QAxWidget();
    flash->resize(500,500);
    flash->setControl("AcroPDF.PDF");
    flash->dynamicCall("LoadFile(QString)","E:\\test.pdf");
    //flash->setControl("ShockwaveFlash.ShockwaveFlash");
    QString str = flash->generateDocumentation();
    QFile file("e:\\1.html");
    file.open(QFile::WriteOnly);
    QTextStream ts(&file);
    ts<<str;
    file.close();
    //flash->setControl(QString::fromUtf8("{d27cdb6e-ae6d-11cf-96b8-444553540000}"));
    //flash->dynamicCall("LoadMovie(long,string)",0,"E:\\SourceCode\\test.swf");
    flash->show();
    /*
    QAxWidget word("Word.Application");

    word.setProperty("Visible", false);
    QAxObject * documents = word.querySubObject("Documents");
    QString str = documents->generateDocumentation();
    QFile file("e:\\1.html");
    file.open(QFile::WriteOnly);
    QTextStream ts(&file);
    ts<<str;
    file.close();
    documents->dynamicCall("Add (void)");
    QAxObject * document = word.querySubObject("ActiveDocument");
    document->dynamicCall("SaveAs (const QString&)", QString("e:/test.doc"));
    document->dynamicCall("Close (boolean)", false);
    word.dynamicCall("Quit (void)");*/
}

Dialog::~Dialog()
{
    delete ui;
}

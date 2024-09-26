#include "searchdia.h"
#include "ui_searchdia.h"

SearchDia::SearchDia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDia)
{
    ui->setupUi(this);
    //sDia=new QDialog(this);
    connect(ui->pushButton,SIGNAL(triggered(bool)),this,SIGNAL(pressBtnS));


}

SearchDia::~SearchDia()
{
    delete ui;
}

void SearchDia::pressBtnS(){
    QString qss=ui->lineEdit->text();
    ui->lineEdit->setText(" finished!");
    qDebug()<<"read s :"<<qss;
    emit sendData(qss);
    accept();
    this->close();
}

void SearchDia::setInitStr(){
   if(!initStr.isEmpty()){
       ui->lineEdit->setText(initStr);
   }
}

void SearchDia::on_pushButton_clicked()
{
    QString qss=ui->lineEdit->text();
    //ui->lineEdit->setText(" finished!");
    //qDebug()<<"read s :"<<qss;
    emit sendData(qss);
    accept();
    this->close();
}

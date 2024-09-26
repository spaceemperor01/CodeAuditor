#include "d_addfunction.h"
#include "ui_d_addfunction.h"
#include <QMessageBox>
#include"funsql.h"
d_addfunction::d_addfunction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::d_addfunction)
{
    ui->setupUi(this);
}

d_addfunction::~d_addfunction()
{
    delete ui;
}
void d_addfunction::setType(bool isAdd,FunctionInfo info)
{
    m_isAdd = isAdd;
    m_info = info;

    ui->le_dname->setText(info.dname);
    ui->sb_degree->setValue(info.degree);
    ui->le_suggest->setText(info.suggest);
}

void d_addfunction::on_add_save_clicked()
{
    FunctionInfo info;
    auto ptr = funSql::getinstance();
    info.dname = ui->le_dname->text();
    info.degree = ui->sb_degree->text().toUInt();
    info.suggest = ui->le_suggest->text();
    if(m_isAdd)
    {
       ptr->addFun(info);
    }
    else
    {
        info.id = m_info.id;
        ptr->UpdateFunctionInfo(info);
    }

    QMessageBox::information(nullptr,"信息","存储成功");
    this->hide();
}

void d_addfunction::on_add_cancel_clicked()
{
    this->hide();
}

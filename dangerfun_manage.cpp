#include "dangerfun_manage.h"
#include "ui_dangerfun_manage.h"

#include <QMessageBox>

dangerfun_manage::dangerfun_manage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dangerfun_manage)
{
    ui->setupUi(this);
    m_ptrriskSql = funSql::getinstance();
}

dangerfun_manage::~dangerfun_manage()
{
    delete ui;
}

void dangerfun_manage::on_B_add_clicked()
{
    m_addFunction.setType(true);
    m_addFunction.exec();
    on_B_refresh_clicked();
}

void dangerfun_manage::on_B_search_clicked()
{
    QString strFilter = ui->le_search->text();

    if(strFilter.isEmpty())
    {
        QMessageBox::information(nullptr,"","搜索不为空");
        on_B_refresh_clicked();
        return;
    }

    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(5);
    QStringList l;
    l<<"序号"<<"id"<<"函数名"<<"等级"<<"建议";
    ui->tableWidget->setHorizontalHeaderLabels(l);

    auto cnt = m_ptrriskSql->getFunCnt();
    ui->lb_cnt->setText(QString("函数数量：%1").arg(cnt));
    QList<FunctionInfo> lFunction = m_ptrriskSql->getPageFun(0,cnt);

    int index = 0;
    for (int i = 0;i < lFunction.size();i++) {
        if(!lFunction[index].dname.contains(strFilter)){
            continue;
        }
        ui->tableWidget->setItem(index,0,new QTableWidgetItem(QString::number(index+1)));
        ui->tableWidget->setItem(index,1,new QTableWidgetItem(QString::number(lFunction[i].id)));
        ui->tableWidget->setItem(index,2,new QTableWidgetItem(lFunction[i].dname));
        ui->tableWidget->setItem(index,3,new QTableWidgetItem(QString::number(lFunction[i].degree)));
        ui->tableWidget->setItem(index,4,new QTableWidgetItem(lFunction[i].suggest));
        index ++;
    }
    ui->tableWidget->setRowCount(index);
}
//编辑
void dangerfun_manage::on_B_edit_clicked()
{
    FunctionInfo info;
    int i = ui->tableWidget->currentRow();
    if(i>=0){
        info.id = ui->tableWidget->item(i,1)->text().toUInt();
        info.dname = ui->tableWidget->item(i,2)->text();
        info.degree = ui->tableWidget->item(i,3)->text().toUInt();
        info.suggest = ui->tableWidget->item(i,4)->text();
        m_addFunction.setType(false,info);
        m_addFunction.exec();
    }
    on_B_refresh_clicked();
}
//删除
void dangerfun_manage::on_B_delete_clicked()
{
    int i = ui->tableWidget->currentRow();
    if(i>=0){
        int id = ui->tableWidget->item(i,1)->text().toUInt();
        m_ptrriskSql->delFun(id);
        on_B_refresh_clicked();
        QMessageBox::information(nullptr,"信息","删除成功");
    }
}
//刷新
void dangerfun_manage::on_B_refresh_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(5);
    QStringList l;
    l<<"序号"<<"id"<<"函数名"<<"等级"<<"建议";
    ui->tableWidget->setHorizontalHeaderLabels(l);

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    auto cnt = m_ptrriskSql->getFunCnt();
    ui->lb_cnt->setText(QString("函数数量：%1").arg(cnt));
    QList<FunctionInfo> lFunction = m_ptrriskSql->getPageFun(0,cnt);
    ui->tableWidget->setRowCount(cnt);
    for (int i = 0;i < lFunction.size();i++) {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(i)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(lFunction[i].id)));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(lFunction[i].dname));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(lFunction[i].degree)));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(lFunction[i].suggest));
    }
}

void dangerfun_manage::on_B_clear_clicked()
{
    QList<FunctionInfo> n;
    m_ptrriskSql->clearFunTable();
    on_B_refresh_clicked();
}

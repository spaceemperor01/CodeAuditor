#include "funsql.h"
#include<QMessageBox>
#include<QCoreApplication>

#include <QSqlQuery>
#include<QtDebug>
funSql*funSql::ptrfunSql = nullptr;
funSql::funSql(QObject *parent)
    : QObject(parent)
{
    init();

}
void funSql::init()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
#if 1
    auto str = QCoreApplication::applicationDirPath()+"danagerfunction.db";
    qDebug()<<str;
#endif
    m_db.setDatabaseName("../danagerfunction.db");
    if(!m_db.open())
        qDebug()<<"db not open";
}
//函数数量
quint32 funSql::getFunCnt()
{
    QSqlQuery sql(m_db);
    sql.exec("select count(id) from danagerfunction;");
    quint32 uiCnt = 0;
    while(sql.next()){
        uiCnt = sql.value(0).toUInt();
    }
    return uiCnt;
}

QList<FunctionInfo> funSql::getPageFun(quint32 page, quint32 uiCnt)
{
    QList<FunctionInfo> l;
    QSqlQuery sql(m_db);
    QString strsql = QString("select * from danagerfunction order by id limit %1 offset %2").
            arg(uiCnt).arg(page * uiCnt);
    sql.exec(strsql);
    FunctionInfo info;
    while(sql.next()){
       info.id = sql.value(0).toUInt();
       info.dname = sql.value(1).toString();
       info.degree = sql.value(2).toUInt();
       info.suggest = sql.value(3).toString();
       l.push_back(info);
    }
    return l;
}
//增加
bool funSql::addFun(FunctionInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("insert into danagerfunction values(null,'%1',%2,'%3')").
            arg(info.dname).
            arg(info.degree).
            arg(info.suggest);
    sql.exec(strSql);
}
//删除
bool funSql::delFun(int id)
{
    QSqlQuery sql(m_db);
    return sql.exec(QString("delete from danagerfunction where id = %1" ).arg(id));
}
//编辑
bool funSql::UpdateFunctionInfo(FunctionInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("update danagerfunction set dname = '%1',degree = '%2',suggest = '%3' where id = %4 ").
            arg(info.dname).
            arg(info.degree).
            arg(info.suggest).
            arg(info.id);
    return sql.exec(strSql);
}

bool funSql::clearFunTable()
{
    QSqlQuery sql(m_db);
    sql.exec("delete from danagerfunction");
    return sql.exec("delete from sqlite_sequence where name = 'danagerfunction'");

}
//
QList<dangerFun*> funSql::getdanagerFun()
{
    QSqlQuery sql(m_db);
    FunctionInfo info;
    QString strsql = QString("select * from danagerfunction");
    sql.exec(strsql);
    while(sql.next()){
        info.dname = sql.value(1).toString();
        info.id = sql.value(0).toUInt();
        info.degree = sql.value(2).toUInt();
        info.suggest = sql.value(3).toString();
//        qDebug()<<info.dname<<info.degree<<info.suggest;
        dangerfunctionlist.append(new dangerFun(info.dname,info.degree,info.suggest));
    }
    return dangerfunctionlist;
}

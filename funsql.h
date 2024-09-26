#ifndef FUNSQL_H
#define FUNSQL_H

#include <QObject>
#include <QSqlDatabase>
#include"dangerfun.h"
struct FunctionInfo
{
    int id;
    QString dname;
    int degree;
    QString suggest;

};
class funSql : public QObject
{
    Q_OBJECT
public:
    QList<dangerFun*>dangerfunctionlist;
    static funSql*ptrfunSql;
    static funSql*getinstance(){
        if(nullptr == ptrfunSql){
            ptrfunSql = new funSql;
        }
        return ptrfunSql;
    }
    explicit funSql(QObject *parent = nullptr);
    void init();
    //查询函数数量
    quint32 getFunCnt();
    //第几页的函数
    QList<FunctionInfo> getPageFun(quint32 page,quint32 uiCnt);
    //增加函数
    bool addFun(FunctionInfo );
    //删除函数
    bool delFun(int id);
    //修改函数信息
    bool UpdateFunctionInfo(FunctionInfo info);
    //清空数据表
    bool clearFunTable();
    //查询数据库函数
    QList<dangerFun*> getdanagerFun();
signals:
private:
    QSqlDatabase m_db;
public slots:
};

#endif // FUNSQL_H

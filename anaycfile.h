#ifndef ANAYCFILE_H
#define ANAYCFILE_H
#include<QString>
#include<QStringList>
#include<QList>
#include<QDebug>
#include<QStandardItemModel>
#include<QStandardItem>
#include<QIcon>
#include<QMap>
#include"funcinfo.h"
#include"parainfo.h"
#include"dangerfun.h"
#include"dangerinfo.h"
class AnayCFile
{
public:
    QString afname;
    QString content;
    QStringList keyword;
    QStringList elementlist;
    QStringList qoute;
    QList<FuncInfo*>funlist;
    QList<ParaInfo*>paralist;
    QStringList localStruct;
    QStringList quote;
    QList<int> linelist;
    QMap<int,dangerFun*>dangerlocmap;
    QList<dangerInfo*>dangerInfoList;
    QMap<QString,QString>deffile;
    QMap<QString,int>defloc;
    QStandardItemModel *model;
    AnayCFile(QString content);
    AnayCFile(QString afname,QString content);
    AnayCFile(QString content,QStringList keyword);
    AnayCFile(QString afname,QString content,QStringList keyword);
    QList<FuncInfo*> getFun();

    QList<ParaInfo*> getPara();

    void quoteBuild();

    void preAnay();

    void divider();

    void funContent(FuncInfo* f,int fbeg,int fend);

    void finddanger(QList<dangerFun*>* dangerlist);

    //void buildModel();

};

#endif // ANAYCFILE_H

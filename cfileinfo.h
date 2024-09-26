#ifndef CFILEINFO_H
#define CFILEINFO_H

#include<QString>
#include<QList>
#include<QStringList>
#include<QDebug>
#include<QStandardItemModel>
#include<QStandardItem>
#include<QIcon>
#include<QMap>
#include"funcinfo.h"
#include"parainfo.h"
#include"filepane.h"
#include"dangerfun.h"
#include"dangerinfo.h"
class CFileInfo
{
public:
    QString cfname;
    QStringList quote;
    QList<FuncInfo*> funlist;
    QList<ParaInfo*> paralist;
    QStringList localStruct;
    QMap<QString,QString>deffile;
    QMap<QString,int>defloc;
    QMap<int,dangerFun*>dangerlocmap;
    QList<dangerInfo*>dangerInfoList;
    FilePane* fpane;
    QStandardItemModel *model;
    QStringList elementlist;
    QList<int> linelist;

    bool isInitial=false;
    CFileInfo();
    CFileInfo(QString name);
    CFileInfo(QString name,FilePane* fp);
    QString output();
    void buildModel();
};

#endif // CFILEINFO_H

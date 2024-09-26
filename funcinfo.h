#ifndef FUNCINFO_H
#define FUNCINFO_H
#include<QString>
#include<QStringList>
#include<QList>
#include<QDebug>
#include"parainfo.h"
class FuncInfo
{
public:
    QString fname;
    QString freturn;
    QString content;
    QStringList funUsed;
    QList<ParaInfo*>plist;
    QString deffile;
    int defloc;
    FuncInfo();
    FuncInfo(QString fname,QString freturn,QList<ParaInfo*>plist);
    FuncInfo(QString fname,QString freturn,QList<ParaInfo*>plist,QString deffile,int defloc);
    FuncInfo(QString fname,QString freturn);

    void output();
    QString out();
};

#endif // FUNCINFO_H

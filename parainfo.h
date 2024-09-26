#ifndef PARAINFO_H
#define PARAINFO_H
#include<QString>
#include<QDebug>

class ParaInfo
{
public:
    QString pname;
    QString ptype;
    QString deffile;
    int defloc;
    ParaInfo();
    ParaInfo(QString name,QString type);
    ParaInfo(QString name,QString type,QString deffile,int defloc);
    QString out();
    void output();
};

#endif // PARAINFO_H

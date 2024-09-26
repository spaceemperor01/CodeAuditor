#include "parainfo.h"

ParaInfo::ParaInfo()
{

}
ParaInfo::ParaInfo(QString name,QString type){
    pname=name;
    ptype=type;

}
ParaInfo::ParaInfo(QString name,QString type,QString deffile,int defloc){
    pname=name;
    ptype=type;
    this->deffile=deffile;
    this->defloc=defloc;
}
QString ParaInfo::out(){
    QString str=ptype+" "+pname;
    return str;
}
void ParaInfo::output(){
    QString str=ptype+" "+pname+"\r";
    qDebug()<<str;
}

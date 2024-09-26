#include "funcinfo.h"

FuncInfo::FuncInfo()
{

}
FuncInfo::FuncInfo(QString fname,QString freturn,QList<ParaInfo*>plist){
    this->fname=fname;
    this->freturn=freturn;
    this->plist=plist;

}
FuncInfo::FuncInfo(QString fname,QString freturn){
    this->fname=fname;
    this->freturn=freturn;
}
FuncInfo::FuncInfo(QString fname,QString freturn,QList<ParaInfo*>plist,QString deffile,int defloc){
    this->fname=fname;
    this->freturn=freturn;
    this->plist=plist;
    this->deffile=deffile;
    this->defloc=defloc;
}

void FuncInfo::output(){
    QString str;
    for(int i=0;i<plist.size();i++){
        str.append(" "+plist.at(i)->out()+"\r");
        //str.append("\r");
    }
    qDebug()<<freturn<<fname<<str;

}
QString FuncInfo::out(){

    QString str;
    for(int i=0;i<plist.size();i++){
        str.append(" "+plist.at(i)->out()+"\r");
    }
    return freturn+" "+fname+" \r"+str+"\r\r";
    //return freturn+" "+fname+"\r\r";

}

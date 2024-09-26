#include "filepane.h"

FilePane::FilePane(QString fname,QString faddr,FilePane* parent,int type)
{
    this->fname=fname;
    this->faddr=faddr;
    this->type=type;
    this->parent=parent;
    if(parent!=NULL){
        if(type==0){
            parent->sonFile<<this;
        }else{
            parent->sonDir<<this;
        }
    }

}
FilePane::FilePane(QString fname,QString faddr,int type)
{
    this->fname=fname;
    this->faddr=faddr;
    this->type=type;
    this->parent=NULL;
}
FilePane::~FilePane(){


}

QString FilePane::getText(){
    if(this->type==0){
        QFile file(faddr);
        if(file.exists()){
            file.open(QIODevice::ReadOnly);
                  QByteArray array= file.readAll();

                   //QByteArray array;
                  // array=file.readLine();
                  // array.toStdString();
                   return array;
        }
        return NULL;
    }
    return NULL;

}

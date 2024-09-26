#include "cfileinfo.h"
CFileInfo::CFileInfo()
{

}
CFileInfo::CFileInfo(QString name){
    cfname=name;
}

CFileInfo::CFileInfo(QString name,FilePane* fp){
    cfname=name;
    fpane=fp;
}
QString CFileInfo::output(){
    QString res=cfname+" \r struct:\r";
    for(int i=0;i<localStruct.size();i++){
        res.append(localStruct.at(i)+"\r");

    }
    res.append("\r parament : \r");
    for(int i=0;i<paralist.size();i++){
        res.append(paralist.at(i)->out()+";\r");
    }
    res.append("\r function:  \r");
    for(int i=0;i<funlist.size();i++){
        res.append(funlist.at(i)->out());
    }

    return res;
}

void CFileInfo::buildModel(){
    model=new QStandardItemModel();
    QStandardItem *stru=new QStandardItem(QIcon(":/res/struct.png"),"结构体");
    QStandardItem *para=new QStandardItem(QIcon(":/res/parameter.png"),"全局变量");
    QStandardItem *fun=new QStandardItem(QIcon(":/res/fun.png"),"函数");
    model->appendRow(stru);
    model->appendRow(para);
    model->appendRow(fun);
    for(QString str:localStruct){
        QStandardItem *struItem =new QStandardItem(QIcon(":/res/data.png"),str);
         qDebug()<<"struct "<<str;
        stru->appendRow(struItem);
    }
    int prow=0;
    for(ParaInfo* cp :paralist){
        QString ps=cp->out();
        qDebug()<<"parament "<<ps;
        QStandardItem *cpi=new QStandardItem(QIcon(":/res/variable.png"),ps);
        QStandardItem *pchild=new QStandardItem("child");
       QList<QStandardItem*> qsilist;
        qsilist<<pchild;
        //cpi->appendColumn(qsilist);
        para->appendRow(cpi);
        //para->appendColumn(qsilist);
        //model->item(1,0)->setChild(prow,0,cpi);
       // model->item(1,0)->setChild(prow,1,pchild);
        //prow++;
        //para->appendColumn(qsilist);
        //para->setChild(1,prow,pchild);
       // prow++;
        //cpi->setChild(cpi->row()+1,cpi->column(),pchild);
    }

    for(FuncInfo *cf :funlist){
        QString qs=cf->freturn+" "+cf->fname;
        qDebug()<<"function "<<cf;
        QStandardItem *cfi=new QStandardItem(QIcon(":/res/function.png"),qs);
        fun->appendRow(cfi);
        for(ParaInfo* subp:cf->plist){
            QString subps=subp->out();
            qDebug()<<"  para "<<subps;
            QStandardItem *subpi=new QStandardItem(QIcon(":/res/variable.png"),subps);
             cfi->appendRow(subpi);
        }

    }


}

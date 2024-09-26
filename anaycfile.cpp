#include "anaycfile.h"


AnayCFile::AnayCFile(QString content)
{
     this->content=content;
     this->keyword<<"void"<<"double"<<"float"<<"int"<<"long"<<"char"<<"short"<<"unsigned"<<"struct"<<"union"<<"typedef"<<"const";
     //this->keyword<<keyword;
     QStringList prtlist;
     for(int i=0;i<this->keyword.size();i++){
         prtlist<<this->keyword.value(i)+"*";

     }
     this->keyword<<prtlist;
}

AnayCFile::AnayCFile(QString afname,QString content)
{    this->afname=afname;
     this->content=content;
     this->keyword<<"void"<<"double"<<"float"<<"int"<<"long"<<"char"<<"short"<<"unsigned"<<"struct"<<"union"<<"typedef"<<"const";
     //this->keyword<<keyword;
     QStringList prtlist;
     for(int i=0;i<this->keyword.size();i++){
         prtlist<<this->keyword.value(i)+"*";

     }
     this->keyword<<prtlist;
}

AnayCFile::AnayCFile(QString content,QStringList keyword)
{
     this->content=content;
     this->keyword<<"void"<<"double"<<"float"<<"int"<<"long"<<"char"<<"short"<<"unsigned"<<"struct"<<"union";
     this->keyword<<keyword;
     QStringList prtlist;
     for(int i=0;i<this->keyword.size();i++){
         prtlist<<this->keyword.value(i)+"*";

     }
     this->keyword<<prtlist;
}

AnayCFile::AnayCFile(QString afname,QString content,QStringList keyword){
    this->afname=afname;
    this->content=content;
    this->keyword<<"void"<<"double"<<"float"<<"int"<<"long"<<"char"<<"short"<<"unsigned"<<"struct"<<"union";
    this->keyword<<keyword;
    QStringList prtlist;
    for(int i=0;i<this->keyword.size();i++){
        prtlist<<this->keyword.value(i)+"*";

    }
    this->keyword<<prtlist;
}

void AnayCFile::quoteBuild(){
    qDebug()<<"quote";
    int index=0;
    while(index<elementlist.size()-3){

         qDebug()<<index<<elementlist.at(index);
        if(elementlist.at(index).startsWith("#")){
            qDebug()<<"#";
            int currentIndex=index;
            if(elementlist.at(index).indexOf("include")!=-1){
                while(elementlist.at(currentIndex)!="\r"){
                    if(elementlist.at(currentIndex)=='"'||elementlist.at(currentIndex)=='<'){
                        qDebug()<<elementlist.at(currentIndex+1);
                        quote<<elementlist.at(currentIndex+1);
                        break;
                    }
                    currentIndex++;
                }
            }
            while(elementlist.at(currentIndex)!="\r"){
                currentIndex++;
            }
            index=currentIndex+1;
        }else{
            qDebug()<<"no keyword";
            index++;
        }
    }
}

void AnayCFile::preAnay(){
    qDebug()<<"prework";
     int index=0;
     while(index<elementlist.size()-3){

          qDebug()<<index<<elementlist.at(index)<<"line: "<<linelist.at(index);
         if(elementlist.at(index).startsWith("#")){
             qDebug()<<"#";
             int currentIndex=index;
             if(elementlist.at(index).indexOf("include")!=-1){
                 while(elementlist.at(currentIndex)!="\r"){
                     if(elementlist.at(currentIndex)=='"'||elementlist.at(currentIndex)=='<'){
                         qDebug()<<elementlist.at(currentIndex+1);
                         qoute<<elementlist.at(currentIndex+1);
                         break;
                     }
                     currentIndex++;
                 }
             }
             while(elementlist.at(currentIndex)!="\r"){
                 currentIndex++;
             }
             index=currentIndex+1;
         }else if(keyword.indexOf(elementlist.at(index))!=-1){
             qDebug()<<"enterFun&Para";
             int nameIndex=index;
             while(keyword.indexOf(elementlist.at(nameIndex))!=-1){
                 nameIndex++;
             }
             qDebug()<<"found name"<<elementlist.at(nameIndex);
             QString OtypeName;
             for(int i=index;i<nameIndex;i++){
                    OtypeName.append(elementlist.at(i)+" ");
             }
             qDebug()<<"oname "<<OtypeName;
             while(elementlist.at(nameIndex)=="*"){
                 nameIndex++;
             }

             QString typeName;
             for(int i=index;i<nameIndex;i++){
                    typeName.append(elementlist.at(i)+" ");
             }
             qDebug()<<"tname "<<typeName;
             if(typeName.startsWith("struct")){
                 qDebug()<<"struct";
                 localStruct.append(elementlist.at(nameIndex));
                 deffile.insert(elementlist.at(nameIndex),afname);
                 defloc.insert(elementlist.at(nameIndex),linelist.at(nameIndex));

                 localStruct.append(elementlist.at(nameIndex)+"*");
                 deffile.insert(elementlist.at(nameIndex)+"*",afname);
                 defloc.insert(elementlist.at(nameIndex)+"*",linelist.at(nameIndex));

                 keyword.append(elementlist.at(nameIndex));
                  keyword.append(elementlist.at(nameIndex)+"*");
                 int lastIndex=nameIndex;
                 while(true){
                     if(elementlist.at(lastIndex)=='}'){
                         lastIndex++;
                         break;
                     }
                     lastIndex++;
                 }
                 while(true){

                     if(elementlist.at(lastIndex)==";"){
                         lastIndex++;
                         break;
                     }
                     QStringList qsl;
                     qsl<<"&"<<"*"<<","<<"["<<"]"<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"0";
                     if(elementlist.at(lastIndex).length()>1||qsl.indexOf(elementlist.at(lastIndex).at(0))==-1){
                         if(elementlist.at(lastIndex-1)=="*"){
                             paralist<<new ParaInfo(elementlist.at(lastIndex),elementlist.at(nameIndex)+"*");

                         }else{
                             paralist<<new ParaInfo(elementlist.at(lastIndex),elementlist.at(nameIndex));
                         }
                         lastIndex++;
                     }else{
                         lastIndex++;
                     }
                 }
                 index=lastIndex+1;

             }else if(typeName.startsWith("typedef struct")){
                 qDebug()<<"typedef";
                 int lastIndex=nameIndex;
                 while(elementlist.at(lastIndex)!="}"){
                     lastIndex++;
                 }
                 lastIndex++;
                 localStruct.append(elementlist.at(lastIndex));
                 deffile.insert(elementlist.at(lastIndex),afname);
                 defloc.insert(elementlist.at(lastIndex),linelist.at(lastIndex));
                 qDebug()<<"struct "<<elementlist.at(lastIndex);
                 localStruct.append(elementlist.at(lastIndex)+"*");
                 deffile.insert(elementlist.at(lastIndex)+"*",afname);
                 defloc.insert(elementlist.at(lastIndex)+"*",linelist.at(lastIndex));
                 keyword.append(elementlist.at(lastIndex));
                 keyword.append(elementlist.at(lastIndex)+"*");
                 QString defType=elementlist.at(lastIndex);

                 while(elementlist.at(lastIndex)!=";"){
                     QStringList qsl;
                     qsl<<"&"<<"*"<<","<<"["<<"]"<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"0";
                     if(elementlist.at(lastIndex).length()>1||qsl.indexOf(elementlist.at(lastIndex).at(0))==-1){
                         if(elementlist.at(lastIndex-1)=="*"){
                             paralist<<new ParaInfo(elementlist.at(lastIndex),defType+"*",afname,linelist.at(lastIndex));

                         }else{
                             paralist<<new ParaInfo(elementlist.at(lastIndex),defType,afname,linelist.at(lastIndex));
                         }
                         lastIndex++;
                     }else{
                         lastIndex++;
                     }
                 }
                    index=lastIndex+1;
             }else{
                 qDebug()<<"normal";
                 if(elementlist.at(nameIndex+1)=="("){
                     qDebug()<<"func"<<elementlist.at(nameIndex);
                     int lastIndex=nameIndex+2;
                     QList<ParaInfo*> plist;
                     bool ready=true;
                     int beg=lastIndex;
                     while(elementlist.at(lastIndex)!=")"){
                         qDebug()<<"find para"<<elementlist.at(lastIndex);
                         if(keyword.indexOf(elementlist.at(lastIndex))==-1&&elementlist.at(lastIndex)!='*'&&elementlist.at(lastIndex)!='&'){
                             if(ready==true){
                                 QString par;
                                 for(int i=beg;i<lastIndex;i++){
                                     //par=par+" "+elementlist.at(i);
                                     par.append(" "+elementlist.at(i));
                                 }
                                 plist.append(new ParaInfo(elementlist.at(lastIndex),par,afname,linelist.at(lastIndex)));
                                 qDebug()<<"add para"<<elementlist.at(lastIndex);
                                 ready=false;
                             }
                         }else{
                             if(ready==false){
                                 ready=true;
                                 beg=lastIndex;
                             }

                         }

                         lastIndex++;

                     }
                     /*
                     for(ParaInfo* pr:plist){
                         qDebug()<<pr->out();
                     }
                     */
                     FuncInfo* fci=new FuncInfo(elementlist.at(nameIndex),typeName,plist,afname,linelist.at(nameIndex));
                     funlist.append(fci);
                     index=lastIndex+1;
                     if(elementlist.at(index)!=";"){
                         int num=0;
                         int pos=index;

                         while(elementlist.at(pos)!="{"){
                             pos++;
                         }
                         int fbeg=pos+1;
                         do{
                             QString q=elementlist.at(pos);
                             if(q=="{"){
                                 num++;
                             }else if(q=="}"){
                                 num--;
                             }
                             pos++;
                         }while(num!=0);
                         int fend=pos-1;
                         funContent(fci,fbeg,fend);
                         index=pos+1;
                     }

                 }else{
                     qDebug()<<"para";
                     QStringList qsl;
                     qsl<<"&"<<"*"<<","<<"["<<"]"<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"0"<<"=";
                     qDebug()<<elementlist.at(nameIndex+1);
                     if(qsl.indexOf(elementlist.at(nameIndex+1))!=-1||elementlist.at(nameIndex+1)==";"){
                         qDebug()<<"singal";
                         paralist.append(new ParaInfo(elementlist.at(nameIndex),typeName,afname,linelist.at(nameIndex)));
                         int pos=nameIndex+1;
                         while(elementlist.at(pos)!=";"){
                             pos++;
                         }
                         index=pos+1;
                     }else{
                         qDebug()<<"multi";
                         int lastIndex=nameIndex;
                         while(elementlist.at(lastIndex)!=";"){
                             if(qsl.indexOf(elementlist.at(lastIndex))==-1){
                                 if(elementlist.at(lastIndex-1)=="*"||elementlist.at(lastIndex-1)=="&"||elementlist.at(lastIndex+1)=="["){
                                     paralist.append(new ParaInfo(elementlist.at(nameIndex),OtypeName+"*",afname,linelist.at(nameIndex)));
                                 }else{
                                     paralist.append(new ParaInfo(elementlist.at(nameIndex),OtypeName,afname,linelist.at(nameIndex)));
                                 }


                             }


                         }
                         index=lastIndex+1;

                     }


                 }


             }



         }else{
             qDebug()<<"no keyword";
             index++;
         }
     }
}



void AnayCFile::funContent(FuncInfo *f, int fbeg, int fend){
     int index=fbeg;
     while(index<fend-3){
         qDebug()<<"funCon "<<elementlist.at(index);
         if(keyword.indexOf(elementlist.at(index))!=-1){
             qDebug()<<"funDef"<<elementlist.at(index);
            int nameIndex=index;
            while(keyword.indexOf(elementlist.at(nameIndex))!=-1||elementlist.at(nameIndex)=="*"||elementlist.at(nameIndex)=="&"){
                nameIndex++;
            }
            if(elementlist.at(nameIndex)==")"){
                index=nameIndex+1;
                continue;
            }


            int lastIndex=nameIndex;
            QStringList qsl;
            qsl<<"&"<<"*"<<","<<"["<<"]"<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"0";
            while(true){
                qDebug()<<"funPara"<<elementlist.at(lastIndex);
                if(elementlist.at(lastIndex)=="="||elementlist.at(lastIndex)==";"){
                    break;
                }
                if(qsl.indexOf(elementlist.at(lastIndex).at(0))==-1){
                    qDebug()<<"found para"<<elementlist.at(lastIndex);

                        QString pcname="";
                        for(int i=index;i<nameIndex;i++){
                            pcname.append(elementlist.at(i)+" ");
                        }
                        // qDebug()<<"index"<<elementlist.at(index);
                         //qDebug()<<"index"<<elementlist.at(index-1);
                        ParaInfo* pci=new ParaInfo(elementlist.at(lastIndex),pcname,afname,linelist.at(lastIndex));
                        f->plist.append(pci);
                        qDebug()<<"insert "<<pci->pname;

                }
                lastIndex++;
            }
            index=lastIndex+1;


         }else{
             index++;
         }
     }
     qDebug()<<"parlist:";
     for(ParaInfo* pt:f->plist){
         qDebug()<<"par"<<pt->out();
     }

}

void AnayCFile::divider(){
    qDebug()<<"divide";
    int index=0;
    int lineNum=0;
    while(index<content.size()){
        qDebug()<<index<<content.at(index);
        QChar cn=content.at(index);
        if(cn=='\r'||cn=="\r"){
            index+=2;

            elementlist.append("\r");
            linelist.append(lineNum);
            lineNum++;
            qDebug()<<"line!";
        }else if(cn=="/"){
           QChar cnt=content.at(index+1);
           if(cnt=="/"){

               index=content.indexOf("\n",index)+1;
               lineNum++;
           }else if(cnt=="*"){
               int zsend=content.indexOf("*/",index)+1;
               for(int k=index;k<zsend;k++){
                   if(content.at(k)=="\r"||content.at(k)=='\r'){
                       lineNum++;
                   }

               }
               index=zsend;

           }else{
               index++;
           }

        }else{
            int lastIndex=index;
            while(true){
               QChar c=content.at(lastIndex);
               if(c=="\r"||c=='\r'){

                   elementlist.append(content.mid(index,lastIndex-index));
                    linelist.append(lineNum);
                   qDebug()<<content.mid(index,lastIndex-index);
                   elementlist.append(content.mid(lastIndex,1));
                    linelist.append(lineNum);
                   qDebug()<<content.mid(lastIndex,1);
                   lineNum++;
                   index=lastIndex+2;
                   break;
               }else if(c==" "||c=="\t"){
                   if(index!=lastIndex){
                       elementlist.append(content.mid(index,lastIndex-index));
                       linelist.append(lineNum);
                       qDebug()<<content.mid(index,lastIndex-index);
                   }

                  //elementlist.append(content.mid(lastIndex,1));
                  index=lastIndex+1;
                  break;
               }else if(c=="&"||c=="="||c==","||c=="'"||c=='"'||c=="*"||c==";"||c=="("||c==")"||c=="{"||c=="}"||c=="["||c=="]"||c=="<"||c==">"){
                   if(lastIndex==index){
                       elementlist.append(content.mid(lastIndex,1));
                       linelist.append(lineNum);
                       qDebug()<<content.mid(lastIndex,1);
                       index=lastIndex+1;
                       break;
                   }else{
                       elementlist.append(content.mid(index,lastIndex-index));
                       linelist.append(lineNum);
                       qDebug()<<content.mid(index,lastIndex-index);
                       elementlist.append(content.mid(lastIndex,1));
                       linelist.append(lineNum);
                       qDebug()<<content.mid(lastIndex,1);
                       index=lastIndex+1;
                       break;
                   }

               }else{
                  lastIndex++;
               }
            }


        }


    }
    /*
    int g=-1;
    for(int k=0;k<elementlist.size();k++){
        if(linelist.at(k)>g){
            g=linelist.at(k);
            qDebug()<<g<<" "<<elementlist.at(k);

        }
    }
   */

}

void AnayCFile::finddanger(QList<dangerFun*>*dangerlist){
    qDebug()<<"danger################################";
    QStringList qsl;
    for(int i=0;i<dangerlist->size();i++){
        qsl.append(dangerlist->at(i)->dname);
        qDebug()<<"load "<<dangerlist->at(i)->dname;
    }
    for(int i=0;i<elementlist.size();i++){
        int pos=qsl.indexOf(elementlist.at(i));
        if(pos!=-1){
            //dangerlocmap.insert(i,dangerlist->at(pos));
            dangerInfoList.append(new dangerInfo(linelist.at(i),afname,dangerlist->at(pos)));
            qDebug()<<"found "<<dangerlist->at(pos)->dname;
        }
    }


}

QList<FuncInfo*> AnayCFile:: getFun(){
   QList<FuncInfo*> qlist;
      qlist<<new FuncInfo();
           return qlist;
}

QList<ParaInfo*> AnayCFile:: getPara(){
    QList<ParaInfo*> qlist;
    qlist<<new ParaInfo();
    return qlist;

}


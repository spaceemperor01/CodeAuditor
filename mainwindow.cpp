#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"logindialog.h"
#include"funsql.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    count=0;
    connect(ui->openAction,SIGNAL(triggered()),this,SLOT(triggerOpen()));
    QAction* searchAction=new QAction("局部搜索");
    connect(searchAction,SIGNAL(triggered(bool)),this,SLOT(searchName()));
    ui->SearchMenu->addAction(searchAction);
    connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(removeSubTab(int)));
    connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(removeTabList(int)));
    connect(ui->action_2,SIGNAL(triggered()), this, SLOT(d_function_manageslot()));
    ui->tabWidget->clear();
    ui->tabWidget_2->setTabText(0,"成员");
    ui->tabWidget_2->setTabText(1,"漏洞");
    ui->tabWidget_2->setTabText(2,"报告");
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->horizontalHeader()->resizeSection(0,50);
    ui->tableWidget->horizontalHeader()->resizeSection(2,50);
     ui->tableWidget->horizontalHeader()->resizeSection(3,150);
     ui->tableWidget->horizontalHeader()->resizeSection(4,100);
     ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
     ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

     connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(toDanger(int,int)));
    QStringList header;
    header<<"行"<<"函数名"<<"危险等级"<<"建议"<<"文件";
    Loaddanagerfunction();
#if 0
    loadDangerFun(":/res/danger.txt");
#endif
    for(dangerFun* df:dangerlist){
        qDebug()<<"danger "<<df->dname<<" degree "<<df->degree;
    }


    //test anay
    /*
    QFile testF("C:/Users/lenovo/Desktop/实验/HandwrittenNumeralRecognition-master/source/main.c");
    qDebug()<<"open";
    QString testS;
    if(testF.exists()){
        testF.open(QIODevice::ReadOnly);
              QByteArray array= testF.readAll();
               testS=array;
               //QByteArray array;
              // array=file.readLine();
              // array.toStdString();

    }
    qDebug()<<"read";
    AnayCFile *acf=new AnayCFile(testS);
    qDebug()<<"create";
    acf->divider();
    for(int i=0;i<acf->elementlist.size();i++){
        qDebug()<<acf->elementlist.value(i);
    }
    acf->quoteBuild();
    for(int i=0;i<acf->quote.size();i++){
        qDebug()<<"quote "<<acf->quote.value(i);

    }
    acf->preAnay();
    for(int i=0;i<acf->qoute.size();i++){
        qDebug()<<"header "<<acf->qoute.value(i);

    }
    for(int i=0;i<acf->localStruct.size();i++){
        qDebug()<<"header "<<acf->localStruct.value(i);

    }
    for(int i=0;i<acf->paralist.size();i++){
       acf->paralist.value(i)->output();

    }
    for(int i=0;i<acf->funlist.size();i++){
       acf->funlist.value(i)->output();

    }
    */

}

MainWindow::~MainWindow()
{
    delete ui;
}
 void MainWindow::triggerOpen(){
    //QString filename=QFileDialog::getOpenFileName(this,"文件对话框",".","");

    QString filename = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                      "/home",
                                                      QFileDialog::ShowDirsOnly
                                                      | QFileDialog::DontResolveSymlinks);

    if(filename.isNull()){
        return;
    }

    rootAddr=filename;
    fileMap.clear();
    fileroot=new FilePane(filename,rootAddr,1);

    QStandardItemModel *model = new QStandardItemModel(this);
    MyText* edit=NULL;

    QTreeView* t = ui->fileArch;
      t->setEditTriggers(QTreeView::NoEditTriggers);			//单元格不能编辑
        t->setSelectionBehavior(QTreeView::SelectRows);			//一次选中整行
        t->setSelectionMode(QTreeView::SingleSelection);        //单选，配合上面的整行就是一次选单行
    //    t->setAlternatingRowColors(true);                       //每间隔一行颜色不一样，当有qss时该属性无效
        t->setFocusPolicy(Qt::NoFocus);

        QStringList headers;
            headers << QStringLiteral("文件名");

                model->setHorizontalHeaderLabels(headers);

                buildTree(fileroot,filename,model,NULL,1);
                t->setModel(model);
                 if(textmap.value("main.c")==NULL){
                     edit=findMain();
                 }
               connect(t,SIGNAL(doubleClicked ( const QModelIndex)),this,SLOT(pickTreeItem(const QModelIndex)));

    /*
     QStringList dirlist,filelist;
     QDir dir(filename);
    QStringList filters ;

    foreach (QString file, dir.entryList(filters, QDir::Files)) {
            filelist.append(filename + "/" + file);
        }

    foreach (QString subdir, dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot)) {
            dirlist.append(filename + "/" + subdir);
        }

    QStringListIterator strIterator(filelist);
    while (strIterator.hasNext())
          qDebug() << strIterator.next() << endl;

    QStringListIterator strIterator2(dirlist);
    while (strIterator2.hasNext())
          qDebug() << strIterator2.next() << endl;


   */

    ui->lineEditCode->setText(filename);

    for(FilePane* fp:fileMap){
        if(fp->fname.endsWith(".c")||fp->fname.endsWith(".h")){
            qDebug()<<"name"<<fp->fname<<"add"<<fp->faddr;
            cfilelist.append(new CFileInfo(fp->fname,fp));
        }
    }
    if(fileMain!=NULL){
        buildCFileTree(fileMain->fname);
        for(int i=0;i<cfilelist.size();i++){
            if(fileMain->fname==cfilelist.at(i)->cfname){
                cfileroot=cfilelist.at(i);
                break;
            }
        }

        //ui->plainTextEdit_2->insertPlainText("text");
        //ui->plainTextEdit_2->insertPlainText(cfileroot->output());
       buildCFileWidget(cfileroot);
       buildDangerTable(cfileroot);
       report(cfileroot);
    }
    //test edit
    if(edit!=NULL){
        qDebug()<<"read edit";
         QTextDocument *doc=edit->document();
         QTextBlock currentBlock = doc->begin();
         QTextBlock::iterator it;
         while(true){
             for (it = currentBlock.begin(); !(it.atEnd()); ++it) {

                         QTextFragment currentFragment = it.fragment();

                         if (currentFragment.isValid()){
                                 QString strText = currentFragment.text();

                                 qDebug()<<strText;
                         }

                             //processFragment(currentFragment);

                     }
             currentBlock = currentBlock.next();
                     if(!currentBlock.isValid())
                         break;

         }



    }





}

//报告
 void MainWindow::report(CFileInfo *cf){
     QList<dangerInfo*> higdan;
     QList<dangerInfo*> middan;
     QList<dangerInfo*> lowdan;
     QList<dangerInfo*> testdan;
     QList<FuncInfo*> unuse;
     for(dangerInfo* d:cf->dangerInfoList){
         switch (d->danger->degree) {
              case 0:
                 higdan.append(d);
                 break;
              case 1:
                 higdan.append(d);

                break;
              case 2:
                middan.append(d);
                 break;
              case 3:
                lowdan.append(d);
                 break;
              default :
                 testdan.append(d);

              break;
         };
     }
     unuse=findUnUsedFun(cf);

     QPlainTextEdit* pte=ui->plainTextEdit_2;
     pte->clear();
     pte->insertPlainText("报告 "+cf->cfname+"\r");
     QString head="统计结果:\r";
     head.append("发现高危函数 ");
     head.append(QString::number(higdan.size()));
     head.append(" 个\r");
     head.append("发现普通危险函数 ");
     head.append(QString::number(middan.size()));
     head.append(" 个\r");
     head.append("发现低危函数 ");
     head.append(QString::number(lowdan.size()));
     head.append(" 个\r");
     head.append("发现测试函数 ");
     head.append(QString::number(testdan.size()));
     head.append(" 个\r");
     head.append("发现无效函数 ");
     head.append(QString::number(unuse.size()));
     head.append(" 个\r");
     pte->insertPlainText(head);
     pte->insertPlainText("高危函数列表:\r");
     for(dangerInfo*d:higdan){
         pte->insertPlainText(d->danger->dname+":\r");
         pte->insertPlainText("位于 "+d->filename+" "+QString::number(d->line)+"行\r");
         pte->insertPlainText(d->danger->suggest+"\r");

     }
     pte->insertPlainText("中等危险函数列表:\r");
     for(dangerInfo*d:middan){
         pte->insertPlainText(d->danger->dname+":\r");
         pte->insertPlainText("位于 "+d->filename+" "+QString::number(d->line)+"行\r");
         pte->insertPlainText(d->danger->suggest+"\r");

     }
     pte->insertPlainText("低风险函数列表:\r");
     for(dangerInfo*d:lowdan){
         pte->insertPlainText(d->danger->dname+":\r");
         pte->insertPlainText("位于 "+d->filename+" "+QString::number(d->line)+"行\r");
         pte->insertPlainText(d->danger->suggest+"\r");

     }
     pte->insertPlainText("测试函数列表:\r");
     for(dangerInfo*d:testdan){
         pte->insertPlainText(d->danger->dname+":\r");
         pte->insertPlainText("位于 "+d->filename+" "+QString::number(d->line)+"行\r");
         pte->insertPlainText(d->danger->suggest+"\r");

     }
     pte->insertPlainText("无效函数列表:\r");
     for(FuncInfo* ff:unuse){
         pte->insertPlainText(ff->fname+"\r");
         pte->insertPlainText("位于"+ff->deffile+" "+QString::number(ff->defloc)+"行\r");

     }

 }

 void MainWindow::removeTabList(int index){
     QString qd;
     if(index<tablist.size()){
         qd=tablist.at(index);
         tablist.removeAt(index);
     }
     textmap.remove(qd);

 }

 void MainWindow::d_function_manageslot()
 {
     fun_manager = new dangerfun_manage;

     LoginDialog dlg;

     if (dlg.exec() == QDialog::Accepted)
     {
            fun_manager->show();

     }
 }



 void MainWindow::switchTab(QString filename){
     for(int i=0;i<tablist.size();i++){
         if(tablist.at(i)==filename){
             ui->tabWidget->setCurrentIndex(i);
         }
     }

 }
 void visitFile(QString filename){





      QStringList dirlist,filelist;
      QDir dir(filename);
     QStringList filters ;

     foreach (QString file, dir.entryList(filters, QDir::Files)) {
             filelist.append(filename + "/" + file);
         }

     foreach (QString subdir, dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot)){
             dirlist.append(filename + "/" + subdir);
         }


 }

 void MainWindow::buildTree(FilePane* fparent,QString fileloc,QStandardItemModel *model,QStandardItem *item,int dec){
     QStringList dirlist,filelist;
     QDir dir(fileloc);
     QStringList filters ;
     //filters<<"*.h"<<"*.c"<<"*.cpp";
     foreach (QString file, dir.entryList(filters, QDir::Files)) {
             filelist.append(file);

             qDebug()<<file;
         }

     foreach (QString subdir, dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot)) {
             dirlist.append(subdir);

             qDebug()<<subdir;
         }

     if(dec==1){
         qDebug()<<"1";
         foreach(QString f,filelist){
             qDebug()<<"f"<<f;
             FilePane* fp=new FilePane(f,fileloc+"/"+f,fparent,0);
             fileMap.insert(fp->faddr,fp);
             //QStandardItem *qitem=new QStandardItem(f);
             //qitem->setIcon(QIcon("D:/QtCode/CodeAudit/ico/file.ico"));
             model->appendRow(new QStandardItem(QIcon(":/res/file.png"),f));
         }
         foreach(QString f,dirlist){
             qDebug()<<"d"<<f;
             QStandardItem *qitem=new QStandardItem(f);
             FilePane* fp=new FilePane(f,fileloc+"/"+f,fparent,1);
             fileMap.insert(fp->faddr,fp);
             qitem->setIcon(QIcon(":/res/folder.png"));

             model->appendRow(qitem);
             buildTree(fp,fileloc+ "/"+f,model,qitem,0);
         }
     }else{
         qDebug()<<"0";
         foreach(QString f,filelist){
             qDebug()<<"f"<<f;
             FilePane* fp=new FilePane(f,fileloc+"/"+f,fparent,0);
             fileMap.insert(fp->faddr,fp);
             //QStandardItem *qitem=new QStandardItem(f);
             //qitem->setIcon(QIcon("D:/QtCode/CodeAudit/ico/file.ico"));
             item->appendRow(new QStandardItem(QIcon(":/res/file.png"),f));
         }
        // item->appendRow(qitem);
         foreach(QString f,dirlist){
             qDebug()<<"d"<<f;
             QStandardItem *qitem=new QStandardItem(f);
             FilePane* fp=new FilePane(f,fileloc+"/"+f,fparent,1);
             fileMap.insert(fp->faddr,fp);
             qitem->setIcon(QIcon("D:/QtCode/CodeAudit/ico/folder.ico"));
             item->appendRow(qitem);
             buildTree(fp,fileloc+ "/"+f,model,qitem,0);
         }
     }
 }

 void MainWindow:: buildCFileWidget(CFileInfo* cfptr){
     qDebug()<<"build cfile information tree!";


     QTreeView* g = ui->treeView;
       g->setEditTriggers(QTreeView::NoEditTriggers);			//单元格不能编辑
         g->setSelectionBehavior(QTreeView::SelectRows);			//一次选中整行
         g->setSelectionMode(QTreeView::SingleSelection);        //单选，配合上面的整行就是一次选单行
     //    t->setAlternatingRowColors(true);                       //每间隔一行颜色不一样，当有qss时该属性无效
         g->setFocusPolicy(Qt::NoFocus);
         if(cfptr->model!=NULL){
             currentCFile=cfptr;
             QStandardItem* item=new QStandardItem(cfptr->cfname);
             cfptr->model->setHorizontalHeaderItem(0,item);
             g->setModel(cfptr->model);
              connect(g,SIGNAL(doubleClicked ( const QModelIndex)),this,SLOT(pickCFileItem(const QModelIndex)));
         }else{


             qDebug()<<"no information";
         }


 }

MyText* MainWindow::findMain(){
     FilePane *ft=NULL;
     MyText *edit;
     QMapIterator<QString, FilePane*> iterator(fileMap);
         while (iterator.hasNext()) {
             iterator.next();
             if(iterator.value()->fname.compare("main.c")==0){
                 ft=iterator.value();
             }
            // qDebug() << iterator.key() << ":" << iterator.value();
         }


     if(ft!=NULL){
         fileMain=ft;
         if(ft->type==0){
             edit = new MyText(ui->tabWidget,"main.c");
             textmap.insert(edit->name,edit);
             tablist.insert(0,"main.c");
             qpe=edit;

             ui->tabWidget->insertTab(0,edit,QString::number(count));
             ui->tabWidget->setTabText(0,"main.c");
             ui->tabWidget->setCurrentIndex(0);
             edit->insertPlainText(ft->getText());
             edit->setContextMenuPolicy(Qt::CustomContextMenu);

             connect(edit, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_textmenu(QPoint)));

             count++;
         }
     }
     return edit;
 }

void MainWindow:: pickCFileItem(const QModelIndex & index){
     if(index.isValid()&&currentCFile!=NULL){
         QString qs=index.data().toString();
         QString tar;
         QString deffile;
         int defline;
         qDebug()<<"pick file: "<<qs;
         bool dec=false;
         for(QString ss:currentCFile->localStruct){
             if(ss==qs){
                 tar=qs;
                 deffile=currentCFile->deffile.value(tar);
                 defline=currentCFile->defloc.value(tar);
                 qDebug()<<"struct "<<tar;

                 dec=true;
                 break;
             }
         }

         if(dec==false){
             int ind=qs.lastIndexOf(" ");
             QString subs;
             if(ind!=-1){
                 subs=qs.mid(ind+1);
             }else{
                 subs=qs;
             }

             for(ParaInfo* ps:currentCFile->paralist){
                 if(ps->pname==subs){
                     tar=subs;
                     deffile=ps->deffile;
                     defline=ps->defloc;
                     dec=true;
                     qDebug()<<"parament "<<tar;

                     break;

                 }

             }

             if(dec==false){
                 for(FuncInfo* fs:currentCFile->funlist){
                     if(dec){
                         break;
                     }
                     if(fs->fname==subs){
                         tar=subs;
                         deffile=fs->deffile;
                         defline=fs->defloc;
                         dec=true;
                         qDebug()<<"funtion "<<tar;

                         break;
                     }
                     for(ParaInfo* fsp:fs->plist){
                         if(fsp->pname==subs){
                             tar=subs;
                             deffile=fsp->deffile;
                             defline=fsp->defloc;
                             dec=true;
                             qDebug()<<"local parament"<<tar;
                             break;
                         }
                     }

                 }
             }

         }

         if(dec==false){
             qDebug()<<"no information element";
         }else{

            // QString num=QString::number(defline);
            // QString num=QString("%1").arg(defline);
             qDebug()<<"file: "<<deffile<<" line: "<<defline;

             setLineHighLigth(deffile,defline);



         }


     }
}

void MainWindow::setLineHighLigth(QString filename, int line){
    qDebug()<<"setHighLight at "<<filename<<" line "<<line;
    MyText *edit=textmap.value(filename);
    if(edit!=NULL){
        switchTab(filename);
        qDebug()<<"exists";

        clearFormat(edit);

        QTextCursor textCursor =edit->textCursor();

        QTextBlock  block = edit->document()->findBlockByNumber(line);

        int len=block.length();

        int pos=block.position();
        textCursor.setPosition(pos,QTextCursor::MoveAnchor);
        textCursor.setPosition(pos+len,QTextCursor::KeepAnchor);
        //block.charFormat();
        //edit->setTextCursor(QTextCursor(block));
         //edit->setTextCursor(QTextCursor(block));


        //textCursor.select(QTextCursor::LineUnderCursor);



         /*
        textCursor.setPosition(line,QTextCursor::MoveAnchor); //将光标移动到指定位置

        textCursor.select(QTextCursor::LineUnderCursor);

        QString curText = textCursor.selectedText();
        */
        QTextCharFormat format;

        format.setBackground(Qt::blue);

        format.setForeground(Qt::red);

        textCursor.mergeCharFormat(format);




    }else{
        qDebug()<<"not exists";
        CFileInfo* cfi=NULL;
        for(CFileInfo* cff:cfilelist){
            if(cff->cfname==filename){

                cfi=cff;
                break;
            }
        }
        if(cfi!=NULL){
            FilePane* fpane=cfi->fpane;
            edit=new MyText(ui->tabWidget,filename);
            textmap.insert(edit->name,edit);
            tablist.insert(0,filename);
            ui->tabWidget->insertTab(0,edit,QString::number(count));
            ui->tabWidget->setTabText(0,filename);
            ui->tabWidget->setCurrentIndex(0);
            edit->insertPlainText(fpane->getText());


            edit->setContextMenuPolicy(Qt::CustomContextMenu);

            connect(edit, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_textmenu(QPoint)));


            clearFormat(edit);



            QTextCursor textCursor =edit->textCursor();

            QTextBlock  block = edit->document()->findBlockByNumber(line);


            int pos=block.position();
            int len=block.length();
            textCursor.setPosition(pos,QTextCursor::MoveAnchor);
            textCursor.setPosition(pos+len,QTextCursor::KeepAnchor);
            //edit->setTextCursor(QTextCursor(block));
             //edit->setTextCursor(QTextCursor(block));

            //textCursor.select(QTextCursor::LineUnderCursor);


            /*
            textCursor.setPosition(line,QTextCursor::MoveAnchor); //将光标移动到指定位置

            textCursor.select(QTextCursor::LineUnderCursor);

            QString curText = textCursor.selectedText();

            */
            QTextCharFormat format;

            format.setBackground(Qt::blue);

            format.setForeground(Qt::red);

            textCursor.mergeCharFormat(format);


        }


    }

}

void MainWindow::clearFormat(MyText *edit){
    qDebug()<<"clear format";
    QTextCursor textCursor =edit->textCursor();
    textCursor.setPosition(0,QTextCursor::MoveAnchor);
    textCursor.movePosition(QTextCursor::End,QTextCursor::KeepAnchor);
    QTextCharFormat format;

    format.setBackground(Qt::white);

    format.setForeground(Qt::black);

       textCursor.mergeCharFormat(format);

}

void MainWindow:: toDanger(int row,int column){
    QTableWidgetItem * item1 = new QTableWidgetItem;
    item1 = ui->tableWidget->item(row,0);
     QTableWidgetItem * item2 = new QTableWidgetItem;
     item2 = ui->tableWidget->item(row,4);
     int line=item1->text().toInt();
     QString filename=item2->text();
    qDebug()<<"line "<<line<<" file "<<filename;
    setLineHighLigth(filename,line);


}

 void MainWindow::pickTreeItem(const QModelIndex & index){

     QString s=getWholeName(index);
     qDebug()<<"click"<<s;

     //QWidget *temp = new QWidget;
         //在当前页面的后面插入一个新的页面.
         FilePane *ft=fileMap.value(s);
         qDebug()<<"search "<<s;
         if(ft!=NULL){
             qDebug()<<"enter1";
             //qDebug()<<ft->getText();
             if(ft->type==0){
                 qDebug()<<"enter2";
                 //QPlainTextEdit* edit = new QPlainTextEdit(ui->tabWidget);
                 MyText* edit=textmap.value(ft->fname);

                 if(edit==NULL){
                     qDebug()<<"enter null";
                     qDebug()<<"";
                     edit=new MyText(ui->tabWidget,ft->fname);
                    textmap.insert(edit->name,edit);
                    tablist.insert(0,edit->name);
                    ui->tabWidget->insertTab(0,edit,QString::number(count));
                    ui->tabWidget->setTabText(0,index.data().toString());
                    ui->tabWidget->setCurrentIndex(0);
                    edit->insertPlainText(ft->getText());


                    edit->setContextMenuPolicy(Qt::CustomContextMenu);

                    connect(edit, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_textmenu(QPoint)));
                 }else{
                     qDebug()<<"enter not null";
                     switchTab(ft->fname);
                     /*
                     //edit=ui->tabWidget_2->findChild<MyText*>(ft->fname);
                     QList<MyText*> sonlist=ui->tabWidget_2->findChildren<MyText*>();

                     for(MyText* my:sonlist){
                         if(my->name==ft->fname){
                             edit=my;
                             break;
                         }
                     }

                     if(edit==NULL){
                         qDebug()<<"not find son text Widget";
                         edit=new MyText(ui->tabWidget,ft->fname);
                                          textmap.insert(edit->name,edit);
                                          tablist.insert(0,edit->name);
                                          ui->tabWidget->insertTab(0,edit,QString::number(count));
                                          ui->tabWidget->setTabText(0,index.data().toString());
                                          ui->tabWidget->setCurrentIndex(0);
                                          edit->insertPlainText(ft->getText());


                                          edit->setContextMenuPolicy(Qt::CustomContextMenu);

                                          connect(edit, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_textmenu(QPoint)));

                     }else{
                         qDebug()<<"find son Widget";
                            // qDebug()<<"find tab widget";
                            // ui->tabWidget_2->setCurrentWidget(edit);
                            switchTab(ft->fname);

                     }

                     */
                 }
                 /*
                 MyText edit=new MyText(ui->tabWidget,ft->fname);
                 textmap.insert(edit->tname,edit);
                 ui->tabWidget->insertTab(0,edit,QString::number(count));
                 ui->tabWidget->setTabText(0,index.data().toString());
                 ui->tabWidget->setCurrentIndex(0);
                 edit->insertPlainText(ft->getText());


                 edit->setContextMenuPolicy(Qt::CustomContextMenu);

                 connect(edit, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_textmenu(QPoint)));
                 */
                 CFileInfo *cf=NULL;
                 for(int i=0;i<cfilelist.size();i++){
                     if(ft->fname==cfilelist.at(i)->cfname){
                         cf=cfilelist.at(i);
                         break;
                     }
                 }
                 if(cf!=NULL){
                     if(cf->isInitial==false){
                        buildCFileTree(cf->cfname);

                     }

                     //ui->plainTextEdit_2->clear();
                     //ui->plainTextEdit_2->insertPlainText(cf->output());
                     buildCFileWidget(cf);
                     buildDangerTable(cf);
                     report(cf);
                 }

                 /*
                 ui->tabWidget->insertTab(0, temp,QString::number(count));    //显示新的页面.
                 ui->tabWidget->setTabText(0,index.data().toString());
                 ui->tabWidget->setCurrentIndex(0);
                 */

                 count++;

             }

         }






 }
#if 0
 void MainWindow::loadDangerFun(QString filename){
     QFile testF(filename);
     qDebug()<<"open";
     QString testS;
     QStringList list;
     if(testF.exists()){
         testF.open(QIODevice::ReadOnly);
               //QByteArray array;
                //testS=array;
         while(!testF.atEnd()){
             testS=testF.readLine();
             list=testS.split("#");
             if(list.size()==3){
                 dangerlist.append(new dangerFun(list.at(0),list.at(1).toInt(),list.at(2)));
             }

         }
     }
 }
#endif
#if 1 //数据库连接
 void MainWindow::Loaddanagerfunction()
 {
     auto p = funSql::getinstance();
     dangerlist = p->getdanagerFun();
 }

#endif
 void MainWindow::slot_textmenu(QPoint){
     QMenu *menu = new QMenu;
     //自定义action

     QAction *action = new QAction("查看定义",qpe);
     connect(action, SIGNAL(triggered(bool)), this, SLOT(searchDefine()));
     //添加action到menu
     menu->addAction(action);

     QAction *action2 = new QAction("搜索",qpe);
     connect(action2, SIGNAL(triggered(bool)), this, SLOT(searchName()));
     //添加action到menu
     menu->addAction(action2);


     menu->move (cursor().pos());
     menu->show();
 }

 void MainWindow::buildCFileTree(QString cfilename){
     qDebug()<<"build "<<cfilename;
     AnayCFile* acf;
     CFileInfo * clocal;
     for(CFileInfo* cfi:cfilelist){
       if(cfi->cfname==cfilename){
           acf=new AnayCFile(cfilename,cfi->fpane->getText());
           clocal=cfi;
           break;
       }
     }
     QStringList q_stru;
     QMap<QString,QString>file_stru;
     QMap<QString,int>loc_stru;
     QList<FuncInfo*> q_fun;
     QList<ParaInfo*> q_para;
     QList<dangerInfo*>q_dan;
     if(acf!=NULL){
         acf->divider();
         acf->quoteBuild();
         acf->finddanger(&dangerlist);

        // clocal->dangerlocmap=acf->dangerlocmap;
         clocal->elementlist=acf->elementlist;
         clocal->linelist=acf->linelist;

          clocal->dangerInfoList=acf->dangerInfoList;
          qDebug()<<"danger implement%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
          qDebug()<<"name "<<cfilename;
          for(dangerInfo* dtest:clocal->dangerInfoList){
              qDebug()<<"danname "<<dtest->danger->dname;
          }
         for(QString s:acf->quote){
             for(CFileInfo *cfi:cfilelist){
                 if(cfi->cfname==s){
                     if(cfi->isInitial==false){
                          buildCFileTree(s);
                     }
                    q_stru.append(cfi->localStruct);
                    QMapIterator <QString,QString> fi(cfi->deffile);
                    while(fi.hasNext()){
                        fi.next();
                        file_stru.insert(fi.key(),fi.value());
                    }
                    QMapIterator<QString,int> dior(cfi->defloc);
                    while(dior.hasNext()){
                        dior.next();
                        loc_stru.insert(dior.key(),dior.value());
                    }
                    q_fun.append(cfi->funlist);
                    q_para.append(cfi->paralist);
                    q_dan.append(cfi->dangerInfoList);
                 }
             }
         }

         acf->keyword.append(q_stru);
         acf->preAnay();
         QMapIterator<QString,QString> qfi(acf->deffile);
         while(qfi.hasNext()){
             qfi.next();
             file_stru.insert(qfi.key(),qfi.value());
         }
         QMapIterator<QString,int> qli(acf->defloc);
         while(qli.hasNext()){
             qli.next();
             loc_stru.insert(qli.key(),qli.value());
         }
         clocal->funlist =acf->funlist;
         clocal->paralist=acf->paralist;
         clocal->localStruct=acf->localStruct;
         clocal->deffile=file_stru;
         clocal->defloc=loc_stru;
         clocal->funlist.append(q_fun);
         clocal->paralist.append(q_para);
         clocal->dangerInfoList.append(q_dan);
         qDebug()<<"danger assign$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$";
         qDebug()<<"name "<<cfilename;
         for(dangerInfo* dtest:clocal->dangerInfoList){
             qDebug()<<"danname "<<dtest->danger->dname;
         }
         clocal->localStruct.append(q_stru);


           clocal->isInitial=true;



           clocal->buildModel();

           //begin build model


            //finish build model
     }
     if(clocal!=NULL&&acf!=NULL){

         for(QString s:clocal->localStruct){
             qDebug()<<"struct "<<s;
         }
         for(QString k:acf->keyword){
             qDebug()<<"keyword "<<k;
         }
         for(ParaInfo *p:clocal->paralist){
             qDebug()<<"parament "<<p->out();
         }

     }

     qDebug()<<"finish build"<<cfilename;


 }
 QList<FuncInfo*> MainWindow::findUnUsedFun(CFileInfo* cfile){
     QList<FuncInfo*> uflist;

     for(FuncInfo* fun:cfile->funlist){
         int num=0;
         for(CFileInfo* ffile:cfilelist){
             for(int i=0;i<ffile->elementlist.size();i++){
                 if(ffile->elementlist.at(i)==fun->fname){
                     if(ffile->linelist.at(i)==fun->defloc&&ffile->cfname==fun->deffile){
                         qDebug()<<"find def";
                     }else{
                         qDebug()<<"find use";
                         num++;
                     }
                 }
             }
         }
         if(num==0){
             uflist.append(fun);

         }

     }
     return uflist;

 }


void MainWindow::buildDangerTable(CFileInfo* cf){
    //qSort(cf->dangerInfoList.begin(),cf->dangerInfoList.end(),compareDan);
    //"行"<<"函数名"<<"危险等级"<<"建议"<<"文件"
    qDebug()<<"danger---------------------------------------------------------------";
      ui->tableWidget->clear();
      int row_num=0;
      int size=cf->dangerInfoList.size()-ui->tableWidget->rowCount();
      for(int k=0;k<size;k++){
          ui->tableWidget->insertRow(ui->tableWidget->rowCount());
      }
    for(dangerInfo* danI:cf->dangerInfoList){


         //ui->tableWidget->insertRow(row_num);
        qDebug()<<"dan "<<danI->danger->dname;
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(danI->line));
        QTableWidgetItem *item1 = new QTableWidgetItem(danI->danger->dname);
        QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(danI->danger->degree));
        QTableWidgetItem *item3 = new QTableWidgetItem(danI->danger->suggest);
        QTableWidgetItem *item4 = new QTableWidgetItem(danI->filename);
        ui->tableWidget->setItem(row_num, 0, item);
        ui->tableWidget->setItem(row_num, 1, item1);
        ui->tableWidget->setItem(row_num, 2, item2);
        ui->tableWidget->setItem(row_num, 3, item3);
        ui->tableWidget->setItem(row_num, 4, item4);
        row_num++;
    }
}
/*
static bool MainWindow::compareDan(const dangerInfo &df1,const dangerInfo &df2){
     return df1.danger->degree-df2.danger->degree;
}*/
 QString MainWindow::getWholeName(const QModelIndex &node){
     if(node.parent().isValid()){
         return getWholeName(node.parent())+"/"+node.data().toString();
     }else{
         return rootAddr+"/"+node.data().toString();
     }
 }

 void MainWindow::removeSubTab(int index)
 {
       count--;
       ui->tabWidget->removeTab(index);
 }

 void MainWindow::searchName(){

     QWidget* page=ui->tabWidget->currentWidget();
     QPlainTextEdit *textrandom=(QPlainTextEdit*)page;
     QString selectStr = textrandom->textCursor().selectedText();


     SearchDia *sd=new SearchDia(this);
     sd->initStr=selectStr;
     sd->setInitStr();

     connect(sd,SIGNAL(sendData(QString)),this,SLOT(conductSearchName(QString)));
     if(sd->exec()==QDialog::Accepted){
         }

     delete sd;

 }

 void MainWindow::conductSearchName(QString data){
     ui->plainTextEdit->clear();
     qDebug()<<"searchName: "<<data;
     ui->plainTextEdit->insertPlainText("search: "+data);

     QWidget* page=ui->tabWidget->currentWidget();
     MyText *textrandom=(MyText*)page;
     clearFormat(textrandom);
     QTextDocument * document =textrandom->document();
     HighLighter *myhigh=new HighLighter(document);
     myhigh->setTextColor(data,Qt::green);
     //MyHigher *myhigh=new MyHigher(document);

 }

 void MainWindow::searchDefine(){

     QWidget* page=ui->tabWidget->currentWidget();
     MyText *textrandom=(MyText*)page;
     //clearFormat(textrandom);
     QString selectStr = textrandom->textCursor().selectedText();
     ui->plainTextEdit->clear();
     ui->plainTextEdit->insertPlainText("serach defination of "+selectStr+"\r");
     qDebug()<<page;
     int line=-1;
     QString filename;
     CFileInfo* currentF=NULL;
     bool dec=false;
     for(CFileInfo* cf:cfilelist){
         if(cf->cfname==textrandom->name){
             currentF=cf;
             break;
         }
     }
     if(currentF!=NULL){
         qDebug()<<"find cfile";
         for(int i=0;i<currentF->localStruct.size();i++){
             if(currentF->localStruct.at(i)==selectStr){
                 line=currentF->defloc.value(selectStr);
                 filename=currentF->deffile.value(selectStr);
                 dec=true;
                 break;
             }
         }
         if(dec==false){
             for(ParaInfo* p:currentF->paralist){
                 if(p->pname==selectStr){
                     dec=true;
                     line=p->defloc;
                     filename=p->deffile;
                     break;
                 }
             }
             if(dec==false){
                 for(FuncInfo* f:currentF->funlist){
                     if(dec==true){
                         break;
                     }
                     if(f->fname==selectStr){
                         dec=true;
                         line=f->defloc;
                         filename=f->deffile;
                         break;
                     }
                     for(ParaInfo *fp:f->plist){
                         if(fp->pname==selectStr){
                             dec=true;
                             line=fp->defloc;
                             filename=fp->deffile;
                             break;
                         }
                     }
                 }

             }

         }

         if(dec){
             setLineHighLigth(filename,line);
             ui->plainTextEdit->insertPlainText("found defination of "+selectStr+" at "+filename+" line "+line+"\r");
         }else{
             ui->plainTextEdit->insertPlainText("found defination of "+selectStr+"\r");
         }


     }



     /*
     QList <QPlainTextEdit*> qplist=ui->tabWidget->findChildren<QPlainTextEdit*>();

     for(int i=0;i<qplist.size();i++){

         QPlainTextEdit *qprandom=qplist.at(i);
         //QString qstr=qprandom->document()->findBlockByLineNumber(2).text();
         qDebug()<<"son widget"<<qprandom;


     }
     */


 }

void MainWindow::on_insertButton_clicked()
{
    ui->lineEditCode->setText("shit");
}

void MainWindow::on_savedata_clicked()
{
    bool exist;

    QString filename;
    QDir*folder = new QDir;

    exist = folder->exists("../pro/data");

    if(!exist)
    {
       bool ok = folder->mkdir("../pro/data");
       if(ok){
           QMessageBox::information(nullptr,"创建目录","创建成功");
       }else {
           QMessageBox::information(nullptr,"创建目录","创建失败");
       }
    }
    filename = tr("../pro/data/%1.txt").arg("data");
    QFile f(filename);
    QString line =  QString::number(ui->plainTextEdit_2->document()->lineCount());
    f.open(QIODevice::Text|QIODevice::WriteOnly);
    for (int i = 0;i <= line;i ++) {
    myString = ui->plainTextEdit_2->document()->findBlockByLineNumber(i).text();
    QTextStream out(&f);

    out<<myString<<endl;
    }
}

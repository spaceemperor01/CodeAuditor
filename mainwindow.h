#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include<QWidget>
#include<QFileDialog>
#include<QString>
#include<QDir>
#include<QStringList>
#include<QFile>
#include<QFileInfo>
#include<QDebug>
#include<QDirModel>
#include<QStandardItemModel>
#include<QStandardItem>
#include<QMap>
#include<QPlainTextEdit>
#include <QTextBlock>
#include<QTextDocument>
#include<QIcon>
#include<QMapIterator>
#include<QTextCursor>
#include<QTextCharFormat>
#include<QTableWidgetItem>
#include"filepane.h"
#include"mytext.h"
#include"searchdia.h"
#include"myhigher.h"
#include"highlighter.h"
#include"anaycfile.h"
#include"cfileinfo.h"
#include"dangerfun.h"
#include"dangerfun_manage.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    int count;//页数



    QString rootAddr;

    QPlainTextEdit *qpe;

    FilePane* fileroot;

    FilePane* fileMain;

    CFileInfo* cfileroot;

    CFileInfo* currentCFile;

    QList<CFileInfo*> cfilelist;

    QStringList tablist;

    QList<dangerFun*>dangerlist;

    QMap<QString,FilePane*> fileMap;

    QMap<QString,MyText*> textmap;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void visitFile(QString filename);

    QString getWholeName( const QModelIndex & node);

   void buildTree(FilePane* fparent,QString fileloc,QStandardItemModel *model,QStandardItem *item,int dec);

   void buildCFileWidget(CFileInfo* cfptr);

   MyText* findMain();

   void buildCFileTree(QString cfilename);

   void setLineHighLigth(QString filename,int line);

   void switchTab(QString filename);

   void loadDangerFun(QString filename);

   void buildDangerTable(CFileInfo* cf);

   void clearFormat(MyText* edit);

   void report(CFileInfo* cf);

   void Loaddanagerfunction();

   QList<FuncInfo*> findUnUsedFun(CFileInfo* cfile);

   static bool compareDan(const dangerInfo &df1,const dangerInfo &df2){
       return df1.danger->degree-df2.danger->degree;
   }

public slots:
   void conductSearchName(QString data);

   void toDanger(int row,int column);

private slots:

    void triggerOpen();

    void on_insertButton_clicked();

    void pickTreeItem(const QModelIndex & index);

    void removeSubTab(int index);

    void slot_textmenu(QPoint);

    void searchDefine();

    void searchName();

    void pickCFileItem(const QModelIndex & index);

    void removeTabList(int index);

    void d_function_manageslot();



    void on_savedata_clicked();

private:
    Ui::MainWindow *ui;
    dangerfun_manage*fun_manager;
    QString myString;
};
#endif // MAINWINDOW_H

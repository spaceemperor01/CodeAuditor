#ifndef FILEPANE_H
#define FILEPANE_H
#include<QString>
#include<QList>
#include<QFile>
class FilePane
{
public:

    int type;   //0 is file,1 is dir;
    QString fname;
    QString faddr;
    FilePane* parent;
    QList<FilePane*> sonFile;
    QList<FilePane*> sonDir;


    FilePane(QString fname,QString faddr,FilePane* parent,int type);
    FilePane(QString fname,QString faddr,int type);
    ~FilePane();

    QString getText();


};

#endif // FILEPANE_H

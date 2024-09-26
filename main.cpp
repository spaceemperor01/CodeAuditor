#include "mainwindow.h"

#include <QApplication>
#include"anaycfile.h"
#include"funsql.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    funSql sql;
    return a.exec();
}

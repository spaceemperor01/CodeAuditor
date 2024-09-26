#ifndef DANGERFUN_H
#define DANGERFUN_H
#include<QString>

class dangerFun
{
public:
    QString dname;
    int degree;
    QString suggest;

    dangerFun();
    dangerFun(QString dname,int degree,QString suggest);
};

#endif // DANGERFUN_H

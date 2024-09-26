#ifndef DANGERINFO_H
#define DANGERINFO_H
#include<QString>
#include"dangerfun.h"

class dangerInfo
{
public:
    int line;
    QString filename;
    dangerFun* danger;
    dangerInfo();
    dangerInfo(int line,QString filename,dangerFun *danger);
};

#endif // DANGERINFO_H

#ifndef MYTEXT_H
#define MYTEXT_H
#include<QPlainTextEdit>
#include<QString>
class MyText : public QPlainTextEdit
{
public:
    QString name;
    int seqnum;
    MyText(QWidget *parent);
    MyText(QWidget* parent,QString name);
};

#endif // MYTEXT_H

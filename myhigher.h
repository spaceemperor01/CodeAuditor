#ifndef MYHIGHER_H
#define MYHIGHER_H

#include <QWidget>
#include <QSyntaxHighlighter>
#include <QTextDocument>
#include<QString>
#include<QColor>
class MyHigher : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit MyHigher(QTextDocument *parent = nullptr);
    void highlightBlock(const QString &text);

signals:

public slots:

};

#endif // MYHIGHER_H
#ifndef MYHIGHLIGHTCODER_H
#define MYHIGHLIGHTCODER_H

#include <QWidget>
#include <QPlainTextEdit>

#include<QColor>
#include<QString>
#include"mainwindow.h"
class MyHighlightCoder : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit MyHighlightCoder(QWidget *parent = nullptr);




signals:

public slots:

private:
    MyHigher * higher;
};

#endif // MYHIGHLIGHTCODER_H

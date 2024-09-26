#include "myhigher.h"
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QDebug>

MyHigher::MyHigher(QTextDocument *parent) : QSyntaxHighlighter(parent)
{

}

void MyHigher::highlightBlock(const QString &text){
    qDebug()<< text;
    QTextCharFormat myClassFormat;
      myClassFormat.setFontWeight(QFont::Bold);
      myClassFormat.setForeground(Qt::blue);

      QRegularExpression expression("d");
      QRegularExpressionMatchIterator i = expression.globalMatch(text);
      while (i.hasNext())
      {
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart(), match.capturedLength(), myClassFormat);
      }


}












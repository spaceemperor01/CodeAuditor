

#include <QSyntaxHighlighter>
    #include <qtextedit.h>
    #include <qtextdocument.h>
    #include <QTextCharFormat>
    #include <qtextcursor.h>
    #include <qhash.h>
    #include <qvector.h>
    #include <qregexp.h>
    #include <qcolor.h>
    #include <qstring.h>

    //高亮部分文本
    class HighLighter : public QSyntaxHighlighter
    {
    public:
        HighLighter(QTextDocument *parent = 0);

        void highlightBlock(const QString &text);
        void setTextColor(const QString &str, const QColor &color);
        void clearRules();

    private:
        struct HighlightingRule
        {
            QRegExp pattern;
            QTextCharFormat format;
        };
        QVector<HighlightingRule> highlightingRules;
    };


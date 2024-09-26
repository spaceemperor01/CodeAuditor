#include "highlighter.h"

HighLighter::HighLighter(QTextDocument *parent)
        : QSyntaxHighlighter(parent)
    {
        highlightingRules.clear();
    }

    void HighLighter::highlightBlock(const QString &text)
    {
        foreach(HighlightingRule rule, highlightingRules)
        {
            QRegExp expression(rule.pattern);
            int index = text.indexOf(expression);
            while (index >= 0)
            {
                int length = expression.matchedLength();
                setFormat(index, length, rule.format);
                index = text.indexOf(expression, index + length);
            }
        }
    }

    void HighLighter::setTextColor(const QString &str, const QColor &color)
    {
        HighlightingRule rule;
        rule.pattern = QRegExp(str);
        QTextCharFormat format;
        format.setForeground(color);
        rule.format = format;
        highlightingRules.append(rule);
    }

    void HighLighter::clearRules()
    {
        highlightingRules.clear();
    }



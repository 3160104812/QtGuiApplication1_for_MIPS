#pragma once

#include <QSyntaxHighlighter>

class highlighter : public QSyntaxHighlighter
{
	Q_OBJECT

public:
	highlighter::highlighter(QTextDocument *parent = 0);
	~highlighter();

protected:
	void highlight_block(const QString &text) Q_DECL_OVERRIDE;
private:
	struct Rule {
		QRegExp pattern;
		QTextCharFormat format;
	};//rule

	QVector<Rule> Rules;

	QTextCharFormat key_format;
	QTextCharFormat operator_format;

};

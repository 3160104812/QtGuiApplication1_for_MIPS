#include "highlighter.h"

highlighter::highlighter(QTextDocument *parent)
	: QSyntaxHighlighter(parent)
{
	Rule rule;
	QFont key_font = QFont(tr("Consolas"), 14);
	key_font.setBold(true);
	key_format.setFont(key_font);
	key_format.setForeground(Qt::blue);


}

highlighter::~highlighter()
{
}

//InfoCardHighlighter.h by Emercoin developers
#pragma once

class InfoCardHighlighter: public QSyntaxHighlighter {
	public:
		InfoCardHighlighter(QTextDocument *parent);
		virtual void highlightBlock(const QString &text)override;
	protected:
		QTextCharFormat _key;
		QTextCharFormat _comment;
		void highlightKeys(const QString &text);
		void highlightComments(const QString &text);
};
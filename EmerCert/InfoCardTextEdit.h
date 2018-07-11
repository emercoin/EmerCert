//InfoCardTextEdit.h by Emercoin developers
#pragma once

class InfoCardTextEdit: public QTextEdit {
	public:
		InfoCardTextEdit();
		void setCompleter(QCompleter *c);
		QCompleter *completer()const;
	protected:
		virtual void keyPressEvent(QKeyEvent *e) override;
		virtual void focusInEvent(QFocusEvent *e) override;
		void insertCompletion(const QString &completion);
		QString textUnderCursor() const;
		QCompleter *c = 0;
};
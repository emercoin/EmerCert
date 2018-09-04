//NameEqValueTextEdit.h by Emercoin developers
#pragma once

class NameEqValueTextEdit: public QPlainTextEdit {
	public:
		NameEqValueTextEdit();
		virtual QSize sizeHint()const override;
	protected:
		struct Highlighter;
};
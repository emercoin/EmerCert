//SelectableTextEdit.h by Emercoin developers
#pragma once

class SelectableTextEdit: public QPlainTextEdit {
	public:
		SelectableTextEdit();

		QPointer<QWidget> _buddyToShowToolip;//use this window if not set
		virtual void mousePressEvent(QMouseEvent *e)override;
		void copyAndShowTooltip(QLineEdit*toDeselect = 0);
		virtual QSize sizeHint()const override;
};
//NameValueEditWidget.h by Emercoin developers
#pragma once
#include "SelectableLineEdit.h"
class SelectableTextEdit;

class NameValueEditWidget: public QWidget {
	public:
		NameValueEditWidget();
		void setName(const QString & s);
		void setValue(const QString & s);
		void setValuePlaceholder(const QString & s);
		void setValueMultiline(bool b);
		void setValueReadOnly(bool b);
		
		SelectableLineEdit* _resultingName = 0;
	protected:
		bool _multiline = false;
		QWidget* _w1Line = 0;
		QWidget* _wMultiLine = 0;
        SelectableLineEdit* _resultingValue = 0;
		SelectableTextEdit* _resultingMultiline = 0;

		void copyValue();
};
//RegisterUniversityWidget.h by Emercoin developers
#pragma once
#include "NameValueEditWidget.h"

class RegisterUniversityWidget: public QWidget {
	public:
		RegisterUniversityWidget();

		NameValueEditWidget* _NVPair = 0;
    protected:
		QLineEdit* _editName = 0;
		QPlainTextEdit* _editOther = 0;
		QList<QLineEdit*> _edits;
		void recalcValue();
		QLineEdit* addLineEdit(QFormLayout*form, QString dnsParam, QString text, QString tooltipq);
};
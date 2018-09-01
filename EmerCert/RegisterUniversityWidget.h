//RegisterUniversityWidget.h by Emercoin developers
#pragma once
#include "NameValueEditWidget.h"

class RegisterUniversityWidget: public QScrollArea {
	public:
		RegisterUniversityWidget();

		NameValueEditWidget* _NVPair = 0;
    protected:
		QLineEdit* _editName = 0;
		QPlainTextEdit* _editOther = 0;
		QList<QLineEdit*> _edits;
		void recalcValue();
		QLineEdit* addLineEdit(QFormLayout*form, const QString& name, const QString& text, const QString& tooltip);
};
//RegisterUniversityWidget.h by Emercoin developers
#pragma once
#include "NameValueLineEdits.h"

class RegisterUniversityWidget: public QScrollArea {
	public:
		RegisterUniversityWidget();

		NameValueLineEdits* _NVPair = 0;
    protected:
		QLineEdit* _editName = 0;
		QPlainTextEdit* _editOther = 0;
		QList<QLineEdit*> _edits;
		QLineEdit* _hrefForSite = 0;
		void recalcValue();
		QLineEdit* addLineEdit(QFormLayout*form, const QString& name, const QString& text, const QString& tooltip, bool readOnly = false);
};
//ManageDnsPage.h by emercoin developers
#pragma once
#include <QDialog>
#include <QLineEdit>
#include "NameValueEditWidget.h"
class QLineEdit;
class QFormLayout;
class QString;

class ManageDnsPage: public QWidget {
    public:
	    ManageDnsPage(QWidget*parent=0);
    protected:
		NameValueEditWidget* _NVPair = 0;
		QLineEdit* _editName = 0;
		QList<QLineEdit*> _edits;

		void recalcValue();
		QLineEdit* addLineEdit(QFormLayout*form, const QString& dnsParam, const QString& text, const QString& tooltip);
};
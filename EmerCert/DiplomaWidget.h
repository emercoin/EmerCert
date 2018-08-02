//DiplomaWidget.h by Emercoin developers
#pragma once
#include <QDialog>
#include <QLineEdit>
#include "NameValueEditWidget.h"
class QLineEdit;
class QTabWidget;
class QString;

class DiplomaWidget: public QWidget {
	public:
		DiplomaWidget(QWidget*parent=0);
		~DiplomaWidget();
	protected:
		QTabWidget* _tab = 0;
};
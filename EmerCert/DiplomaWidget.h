//DiplomaWidget.h by Emercoin developers
#pragma once
class QTabWidget;

class DiplomaWidget: public QWidget {
	public:
		DiplomaWidget(QWidget*parent=0);
		~DiplomaWidget();
	protected:
		QTabWidget* _tab = 0;
};
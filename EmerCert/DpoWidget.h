//DpoWidget.h by Emercoin developers
#pragma once
class QTabWidget;

class DpoWidget: public QWidget {
	public:
		DpoWidget(QWidget*parent = 0);
		~DpoWidget();
	protected:
		QTabWidget* _tab = 0;
};
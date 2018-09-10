//DpoWidget.h by Emercoin developers
#pragma once
class QTabWidget;
class DpoCreateRootWidget;
class DpoCreateRecordWidget;
class DpoSignRecordWidget;

class DpoWidget: public QWidget {
	public:
		DpoWidget(QWidget*parent = 0);
		~DpoWidget();
	protected:
		QTabWidget* _tab = 0;

		DpoCreateRootWidget* _createRoot = 0;
		DpoCreateRecordWidget* _createRecord = 0;
		DpoSignRecordWidget* _signRecord = 0;
};
//InfoCardsWidget.h by Emercoin developers
#pragma once
class InfoCardTableView;
class InfoCardTableModel;
class CertLogger;

class InfoCardsWidget: public QWidget {
	public:
		InfoCardsWidget(QWidget*parent=0);
	protected:
		void onDelete();
		void onCreate();
		void enableButtons();
		static QString randName();

		QAbstractButton* _btnDelete = 0;
		QAbstractButton* _btnGenerate = 0;
		QAbstractButton* _btnOpenFolder = 0;
		InfoCardTableView* _view = 0;
		CertLogger* _logger = 0;
};
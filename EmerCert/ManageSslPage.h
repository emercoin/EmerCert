//ManageSslPage.h by Emercoin developers
#pragma once
class CertTableView;
class CertLogger;

class ManageSslPage: public QWidget {
	public:
		ManageSslPage(QWidget*parent=0);
	protected:
		void onDelete();
		void onCreate();
		void enableButtons();
		static QString randName();

		QAbstractButton* _btnDelete = 0;
		QAbstractButton* _btnGenerate = 0;
		QAbstractButton* _btnOpenFolder = 0;
		CertTableView* _view = 0;
		struct TemplateDialog;
		CertLogger* _logger = 0;
};
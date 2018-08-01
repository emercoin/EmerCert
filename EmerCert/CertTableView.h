//CertTableView.h by Emercoin developers
#pragma once
#include "TableView.h"
class CertTableModel;
class CertLogger;

class CertTableView: public TableView {
	public:
		CertTableView(CertLogger*l);
		using Model = CertTableModel;
		Model* model()const;
		void generateCertForSelectedRow();
		int selectedRow()const;
		QString selectedLogPath();
		void showInExplorer();
		static void showInGraphicalShell(QWidget *parent, const QString &pathIn);
	protected:
		CertTableModel* _model = 0;
		QPointer<CertLogger> _logger;
		struct Dialog;
		void reloadLog();
		void recreateButtons();
		void generateCertByButton();
		int rowFromAction(QAction*a);
		void installSelectedIntoSystem();
};
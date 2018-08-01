//InfoCardTableView.h by Emercoin developers
#pragma once
#include "TableView.h"
class InfoCardTableModel;
class CertLogger;

class InfoCardTableView: public TableView {
	public:
		InfoCardTableView(CertLogger*logger);
		InfoCardTableModel* model()const;
		int selectedRow()const;
		QString selectedLogPath();
		void showInExplorer();
		void dataChanged(int row);
		CertLogger*logger()const;
	protected:
		InfoCardTableModel* _model = 0;
		QPointer<CertLogger> _logger;
		void reloadLog();

};
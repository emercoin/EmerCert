//InfoCardTableView.h by Emercoin developers
#pragma once
#include "TableView.h"
class InfoCardTableModel;

class InfoCardTableView: public TableView {
	public:
		InfoCardTableView();
		InfoCardTableModel* model()const;
		int selectedRow()const;
		QString selectedLogPath();
		void showInExplorer();
		void dataChanged(int row);
	protected:
		InfoCardTableModel* _model = 0;
		void reloadLog();

};
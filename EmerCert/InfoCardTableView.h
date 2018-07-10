//InfoCardTableView.h by Emercoin developers
#pragma once
#include "TableView.h"
class InfoCardTableModel;

class InfoCardTableView: public TableView {
	public:
		InfoCardTableView();
		using Model = InfoCardTableModel;
		Model* model()const;
		int selectedRow()const;
		QString selectedLogPath();
		void showInExplorer();
	protected:
		InfoCardTableModel* _model = 0;
		void reloadLog();
};
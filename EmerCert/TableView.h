//TableView.h
#pragma once

class TableView: public QTableView {
	public:
		TableView(QWidget * parent = 0);
		void copyText();
#ifdef _DEBUG
		void showClassInfo();
#endif
};
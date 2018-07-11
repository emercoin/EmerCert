//InfoCardTableView.cpp by Emercoin developers
#include "pch.h"
#include "InfoCardTableView.h"
#include "InfoCardTableModel.h"
#include "ShellImitation.h"
#include "Settings.h"
#include "CertTableView.h"
#include "InfoCardItemDelegate.h"

InfoCardTableView::InfoCardTableView() {
	horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	horizontalHeader()->hide();
	_model = new InfoCardTableModel(this);
	setModel(_model);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setSelectionMode(QAbstractItemView::SingleSelection);
	connect(selectionModel(), &QItemSelectionModel::selectionChanged, this, &InfoCardTableView::reloadLog);
	setItemDelegate(new InfoCardItemDelegate(this, _model));
}
InfoCardTableModel* InfoCardTableView::model()const {
	return _model;
}
void InfoCardTableView::reloadLog() {
	QString path = selectedLogPath();
	if(ShellImitation::s_logger)
		ShellImitation::s_logger->setFile(path);
}
void InfoCardTableView::showInExplorer() {
	int nRow = selectedRow();
	QString path;
	if(const auto & row = _model->itemBy(nRow)) {
		path = row->_file;
	} else {
		path = Settings::certDir().absolutePath();
	}
	CertTableView::showInGraphicalShell(this, path);
}
int InfoCardTableView::selectedRow()const {
	auto rows = selectionModel()->selectedIndexes();
	if(!rows.isEmpty())
		return rows[0].row();
	return -1;
}
QString InfoCardTableView::selectedLogPath() {
	int nRow = selectedRow();
	if(const auto & row = _model->itemBy(nRow))
		return row->logFilePath();
	return {};
}
//InfoCardTableView.cpp by Emercoin developers
#include "pch.h"
#include "InfoCardTableView.h"
#include "InfoCardTableModel.h"
#include "ShellImitation.h"
#include "Settings.h"
#include "CertTableView.h"

InfoCardTableView::InfoCardTableView() {
	horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	_model = new Model(this);
	setModel(_model);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setSelectionMode(QAbstractItemView::SingleSelection);
	connect(selectionModel(), &QItemSelectionModel::selectionChanged, this, &InfoCardTableView::reloadLog);
}
InfoCardTableView::Model* InfoCardTableView::model()const {
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
	if(nRow>=0 && nRow < _model->rowCount()) {
		const auto & row = _model->_rows[nRow];
		path = row._file;
	}
	if(path.isEmpty())
		path = Settings::certDir().absolutePath();
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
	if(-1 == nRow)
		return QString();
	const auto & row = _model->_rows[nRow];
	return row.logFilePath();
}
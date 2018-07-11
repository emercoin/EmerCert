//InfoCardItemDelegate.cpp by Emercoin developers
#include "pch.h"
#include "InfoCardItemDelegate.h"
#include "InfoCardTableModel.h"
#include "InfoCardTableView.h"
#include "InfoCardDialog.h"

InfoCardItemDelegate::InfoCardItemDelegate(InfoCardTableView*parent, InfoCardTableModel*model): QStyledItemDelegate(parent), _parent(parent) {
	_model = model;
}
QWidget * InfoCardItemDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index)const {
	auto item = _model->itemBy(index.row());
	if(!item)
		return 0;
	InfoCardDialog dlg(parent);
	dlg._text->setPlainText(item->_text);
	if(dlg.exec()!=QDialog::Accepted)
		return false;
	_model->setData(index, dlg._text->toPlainText());
	return 0;
}
void InfoCardItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index)const {
	return __super::setEditorData(editor, index);
}
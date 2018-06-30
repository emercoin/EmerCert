//InfoCardDialog.cpp by Emercoin developers
#include "pch.h"
#include "InfoCardDialog.h"

InfoCardDialog::InfoCardDialog(QWidget*parent): QDialog(parent) {
	_lay = new QFormLayout(this);
}
QString InfoCardDialog::Row::text()const {
	if(!_multiline && _line) {
		return _line->text();
	}
	if(_multiline && _text) {
		return _text->toPlainText();
	}
	Q_ASSERT(0);
	return QString();
}
QWidget* InfoCardDialog::Row::widget()const {
	if(_multiline)
		return _line;
	return _text;
}
void InfoCardDialog::add(Row & row) {
	if(row._multiline)
		row._line = new QLineEdit;
	else
		row._text = new QPlainTextEdit;;
	_rows << row;
	_lay->addRow(row._name, row.widget());
}
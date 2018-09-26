//SelectableTextEdit.cpp by Emercoin developers
#include "pch.h"
#include "SelectableTextEdit.h"

SelectableTextEdit::SelectableTextEdit() {
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
void SelectableTextEdit::mousePressEvent(QMouseEvent *e) {
	QPlainTextEdit::mousePressEvent(e);
	if(isReadOnly())
		selectAll();
}
void SelectableTextEdit::copyAndShowTooltip(QLineEdit*toDeselect) {
	if(toDeselect)
		toDeselect->deselect();
	selectAll();
	QApplication::clipboard()->setText(toPlainText());
	QWidget* wNear = _buddyToShowToolip;
	if(!wNear)
		wNear = this;
	auto pt = wNear->rect().bottomLeft();
	QToolTip::showText(wNear->mapToGlobal(pt), tr("Copied"));
}
QSize SelectableTextEdit::sizeHint()const {
	auto sz = QPlainTextEdit::sizeHint();
	sz.rheight() /= 3;
	return sz;
}
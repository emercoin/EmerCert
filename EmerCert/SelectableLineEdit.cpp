﻿//SelectableLineEdit.cpp by Emercoin developers
#include "pch.h"
#include "SelectableLineEdit.h"

void SelectableLineEdit::mousePressEvent(QMouseEvent *e) {
	QLineEdit::mousePressEvent(e);
	if(isReadOnly())
		selectAll();
}
void SelectableLineEdit::copyAndShowTooltip(QLineEdit*toDeselect) {
	if(toDeselect)
		toDeselect->deselect();
	selectAll();
	QApplication::clipboard()->setText(text());
	QWidget* wNear = _buddyToShowToolip;
	if(!wNear)
		wNear = this;
	auto pt = wNear->rect().bottomLeft();
	QToolTip::showText(wNear->mapToGlobal(pt), tr("Copied"));
}
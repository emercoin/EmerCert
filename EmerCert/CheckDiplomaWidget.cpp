//CheckDiplomaWidget.cpp by Emercoin developers
#include "pch.h"
#include "CheckDiplomaWidget.h"

CheckDiplomaWidget::CheckDiplomaWidget() {
	setWindowTitle(tr("Check diploma"));

	auto form = new QFormLayout(this);

	_name = new QLineEdit;
	form->addRow(tr("First name and last name"), _name);

	_university = new QLineEdit;
	form->addRow(tr("University"), _university);

	_year  = new QSpinBox;
	_year->setMinimum(-10000);
	_year->setMaximum(std::numeric_limits<qint32>::max());
	_year->setValue(QDate::currentDate().year());
	form->addRow(tr("Year of submission"), _year);

	auto search = new QPushButton(tr("Search"));
	connect(search, &QPushButton::clicked, this, &CheckDiplomaWidget::onSearch);
	form->addRow("", search);
}
void CheckDiplomaWidget::onSearch() {

}
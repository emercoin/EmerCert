//CheckDiplomaWidget.cpp by Emercoin developers
#include "pch.h"
#include "CheckDiplomaWidget.h"

CheckDiplomaWidget::CheckDiplomaWidget() {
	setWindowTitle(tr("Check diploma"));

	auto form = new QFormLayout(this);

	const int emcMaxNameLen = 500;
	_name = new QLineEdit;
	_name->setMaxLength(emcMaxNameLen);
	form->addRow(tr("First name and last name"), _name);

	_university = new QLineEdit;
	_university->setMaxLength(emcMaxNameLen);
	form->addRow(tr("University"), _university);

	_year  = new QSpinBox;
	_year->setMinimum(-10000);
	_year->setMaximum(std::numeric_limits<qint32>::max());
	_year->setValue(QDate::currentDate().year());
	form->addRow(tr("Year of submission"), _year);

	auto search = new QPushButton(tr("Check"));
	search->setShortcut(QKeySequence("Return"));
	connect(search, &QPushButton::clicked, this, &CheckDiplomaWidget::onSearch);
	form->addRow(QString(), search);
}
void CheckDiplomaWidget::onSearch() {
	auto showMsg = [](QWidget*w) {
		auto pt = w->rect().bottomLeft();
		w->setFocus();
		QToolTip::showText(w->mapToGlobal(pt), tr("This field can't be empty"));
	};
	QString name = _name->text().simplified().trimmed();
	QString univ = _university->text().simplified().trimmed();
	name.replace("  ", " ");
	univ.replace("  ", " ");
	if(name.isEmpty()) {
		showMsg(_name);
		return;
	}
	if(univ.isEmpty()) {
		showMsg(_university);
		return;
	}
	QString url = QString("https://trusted-diploma.com/?univ=%1&name=%2&admission=%3")
		.arg(univ)
		.arg(name)
		.arg(_year->value());
	QDesktopServices::openUrl(url);
}
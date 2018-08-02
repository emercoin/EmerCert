//DiplomaWidget.cpp by Emercoin developers
#include "pch.h"
#include "DiplomaWidget.h"
#include "CheckDiplomaWidget.h"
#include "RegisterDiplomaWidget.h"
#include "RegisterUniversityWidget.h"
//#include "AboutTrustedDiplomaWidget.h"

DiplomaWidget::DiplomaWidget(QWidget*parent): QWidget(parent) {
	setWindowTitle(tr("Trusted diploma"));

	auto lay = new QVBoxLayout(this);
    auto description = new QLabel(tr(	
		"<a href=\"https://trusted-diploma.com/\">Trusted diploma</a> allows to store academic certificates in blockchain.<br>\n"
		"<a href=\"https://www.youtube.com/watch?v=ltP57wyIOd8\">Watch video</a>"
		));	
    description->setOpenExternalLinks(true);
    lay->addWidget(description);

	_tab = new QTabWidget;
	lay->addWidget(_tab);
	auto addTab = [this](QWidget*w) { _tab->addTab(w, w->windowTitle()); };
	addTab(new CheckDiplomaWidget());
	addTab(new RegisterUniversityWidget());
	addTab(new RegisterDiplomaWidget());

	QSettings sett;
	int index = sett.value("DiplomaWidget.tabIndex", 0).toInt();
	index = qBound(0, index, _tab->count()-1);
	_tab->setCurrentIndex(index);
}
DiplomaWidget::~DiplomaWidget() {
	QSettings sett;
	sett.setValue("DiplomaWidget.tabIndex", _tab->currentIndex());
}
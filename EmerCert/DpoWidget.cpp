//DpoWidget.cpp by Emercoin developers
#include "pch.h"
#include "DpoWidget.h"
#include "DpoCreateRootWidget.h"
#include "DpoCreateRecordWidget.h"
#include "DpoSignRecordWidget.h"

DpoWidget::DpoWidget(QWidget*parent): QWidget(parent) {
	setWindowTitle(tr("DPO"));
	//setWindowIcon(QIcon(":/icons/TrustedDiploma-32.png"));

	auto lay = new QVBoxLayout(this);
    auto description = new QLabel(tr(	
		R"STR(DPO is <a href="https://emercoin.com/en/emerdpo">Digital Proof of Ownership</a>)STR"
		));	
    description->setOpenExternalLinks(true);
    lay->addWidget(description);

	_tab = new QTabWidget;
	lay->addWidget(_tab);
	auto addTab = [this](QWidget*w) { _tab->addTab(w, w->windowTitle()); };
	addTab(_createRoot = new DpoCreateRootWidget());
	addTab(_createRecord = new DpoCreateRecordWidget());
	addTab(_signRecord = new DpoSignRecordWidget());

	QSettings sett;
	int index = sett.value("DpoWidget.tabIndex", 0).toInt();
	index = qBound(0, index, _tab->count()-1);
	_tab->setCurrentIndex(index);
}
DpoWidget::~DpoWidget() {
	QSettings sett;
	sett.setValue("DpoWidget.tabIndex", _tab->currentIndex());
	_createRoot->updateSettings(true);
	_createRecord->updateSettings(true);
}
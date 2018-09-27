//DpoWidget.cpp by Emercoin developers
#include "pch.h"
#include "DpoWidget.h"
#include "DpoCreateRootWidget.h"
#include "DpoCreateRecordWidget.h"
#include "DpoRegisterDocWidget.h"
#include "DpoUseCaseScheme.h"

DpoWidget::DpoWidget(QWidget*parent): QWidget(parent) {
	setWindowTitle(tr("DPO"));
	setWindowIcon(QIcon(":/icons/DPO-32.png"));

	auto lay = new QVBoxLayout(this);
    auto description = new QLabel(tr(	
		R"STR(DPO is <a href="https://emercoin.com/en/emerdpo">Digital Proof of Ownership</a>)STR"
		));	
    description->setOpenExternalLinks(true);
    lay->addWidget(description);

	_tab = new QTabWidget;
	lay->addWidget(_tab);
	auto addTab = [this](QWidget*w) {
		_tab->addTab(w, w->windowTitle());
	};
	addTab(new DpoUseCaseScheme);
	addTab(_createRoot = new DpoCreateRootWidget());
	addTab(_createRecord = new DpoCreateRecordWidget());
	addTab(_registerDoc = new DpoRegisterDocWidget());
	connect(_createRecord->_NVPair->nameEdit(), &QLineEdit::textChanged, this, [=](const QString&s) {
		_registerDoc->_editName->setText(s);
	});
	_registerDoc->_editName->setText(_createRecord->_NVPair->name());

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
QString DpoWidget::name()const {
	auto w = _tab->currentWidget();
	if(w==_createRoot)
		return _createRoot->_NVPair->name();
	if(w==_createRecord)
		return _createRecord->_NVPair->name();
	if(w==_registerDoc)
		return _registerDoc->_NVPair->name();
	return {};
}
QString DpoWidget::value()const {
	auto w = _tab->currentWidget();
	if(w==_createRoot)
		return _createRoot->_NVPair->value();
	if(w==_createRecord)
		return _createRecord->_NVPair->value();
	if(w==_registerDoc)
		return _registerDoc->_NVPair->value();
	return {};
}
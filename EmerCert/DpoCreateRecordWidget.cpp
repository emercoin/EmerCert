//DpoCreateRecordWidget.cpp by Emercoin developers
#include "pch.h"
#include "DpoCreateRecordWidget.h"
#include "EmailLineEdit.h"
#include "PhoneNumberLineEdit.h"
#include "SelectableLineEdit.h"
#include "NameEqValueTextEdit.h"

DpoCreateRecordWidget::DpoCreateRecordWidget() {
	setWindowTitle(tr("2) Participate in organization"));
	auto w = new QWidget;
	auto lay = new QVBoxLayout(w);
	_NVPair = new NameValueLineEdits;
	_NVPair->setValueMultiline(true);

	auto description = new QLabel(tr("Create record with your name/nickname etc, for which organization will prove you are working with them"));
	lay->addWidget(description);

	auto form = new QFormLayout;
	lay->addLayout(form);
	_editName = addLineEdit(form, {}, tr("Organisation abbreviation (?) dpo:"),
		tr("This must be already registered DPO root record, like dpo:NDI"));
	_editSN = addLineEdit(form, {}, tr("Your name or nickname (?)"),
		tr("If this name or SN is already registered, add any number after it (like ':1234')"));
	
	lay->addWidget(_NVPair);
	lay->addWidget(new QLabel(tr("This record must be created by person who's rights are recorded.\n"
		"After you create this name record, emeil this name to organization so they can sign it.")));
    lay->addStretch();
	setWidget(w);
	updateSettings(false);
}
void DpoCreateRecordWidget::updateSettings(bool save) {
	QSettings sett;
	sett.beginGroup("DpoCreateRecordWidget");
	if(save)
		sett.setValue("name", _editName->text());
	else
		_editName->setText(sett.value("name").toString());
}
void DpoCreateRecordWidget::recalcValue() {
	const QString name = _editName->text().trimmed();
	const QString serial = _editSN->text().trimmed();
    if(name.isEmpty() || serial.isEmpty()) {
		_NVPair->setName({});//to display placeholderText
	} else {
		QString s = name + ':' + serial;
		if(!s.startsWith("dpo:"))
			s.prepend("dpo:");
        _NVPair->setName(s);
	}

	QStringList parts;
    for(auto e: _edits) {
        QString value = e->text().trimmed();
		if(auto tel = dynamic_cast<PhoneNumberLineEdit*>(e))
			value = tel->toPhoneNumber();
        if(!value.isEmpty())
            parts << e->objectName() + "=" + value;
    }
	for(auto & s: parts)
		s = s.trimmed();
	QString v = parts.join('\n');
	if(v.isEmpty())
		v += "Signature=";
	_NVPair->setValue(v);
}
QLineEdit* DpoCreateRecordWidget::addLineEdit(QFormLayout*form, const QString& name,
	const QString& text, const QString& tooltip, bool readOnly)
{
	QLineEdit* edit = 0;
	if(readOnly) {
		edit = new SelectableLineEdit;
		edit->setReadOnly(true);
	} else {
		edit = new QLineEdit;
	}
    edit->setObjectName(name);
    edit->setClearButtonEnabled(true);
    connect(edit, &QLineEdit::textChanged, this, &DpoCreateRecordWidget::recalcValue);
	auto label = new QLabel(text);
	label->setToolTip(tooltip);
    edit->setToolTip(tooltip);
    form->addRow(label, edit);
	if(!name.isEmpty())
		_edits << edit;
    return edit;
}
//DpoCreateRecordWidget.cpp by Emercoin developers
#include "pch.h"
#include "DpoCreateRecordWidget.h"
#include "EmailLineEdit.h"
#include "PhoneNumberLineEdit.h"
#include "SelectableLineEdit.h"
#include "NameEqValueTextEdit.h"

DpoCreateRecordWidget::DpoCreateRecordWidget() {
	setWindowTitle(tr("Register ownership record"));
	auto w = new QWidget;
	auto lay = new QVBoxLayout(w);
	_NVPair = new NameValueEditWidget;
	_NVPair->setValueMultiline(true);

	auto description = new QLabel(tr("Create record - serial number for some goods, or person name owning some rights etc"));
	lay->addWidget(description);

	auto form = new QFormLayout;
	lay->addLayout(form);
	_editName = addLineEdit(form, {}, tr("Organisation abbreviation (?) dpo:"),
		tr("This must be already registered DPO root record, like dpo:NDI"));
	_editSN = addLineEdit(form, {}, tr("Serial number or person name (?)"),
		tr("If this name or SN is already registered, add any number after it (like ':1234'), and conflict will be solved after you sign that record"));
	
	lay->addWidget(_NVPair);
	lay->addWidget(new QLabel(tr("This record must be created by person who's rights are recorded.\n"
		"If you are organization thet trnsfers tights, you can use NAME_UPDATE to send this record ownership to that person.")));
    lay->addStretch();
	setWidget(w);
}
void DpoCreateRecordWidget::recalcValue() {
	const QString name = _editName->text().trimmed();
	const QString serial = _editSN->text().trimmed();
    if(name.isEmpty() || serial.isEmpty()) {
		_NVPair->setName({});//to display placeholderText
	} else {
        _NVPair->setName("dpo:" + name + ':' + serial);
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
	_NVPair->setValue(parts.join('\n'));
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
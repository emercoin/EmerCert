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

	auto description = new QLabel();
	lay->addWidget(newLabel(
		tr("Create record with your name/nickname etc, for which organization will prove you are working with them")));

	auto form = new QFormLayout;
	lay->addLayout(form);
	_editName = addLineEdit(form, {}, tr("Organisation abbreviation (?) dpo:"),
		tr("This must be already registered DPO root record, like dpo:NDI"));
	_editSN = addLineEdit(form, {}, tr("Your name or nickname (?)"),
		tr("If this name or SN is already registered, add any number after it (like ':1234')"));

	form->addRow(newLabel(
			tr("Email or IM next text to organisation (get their contacts somehow, as you know what are you dealing with):")));

	_askSignature = new SelectableLineEdit;
	_askSignature->setReadOnly(true);
	_askSignature->setPlaceholderText(tr("Text above is not filled"));
	form->addRow(_askSignature);
	
	_signature = addLineEdit(form, "Signature", tr("Received signature:"), {});
	_signature->setPlaceholderText(tr("Like Hyy39/xmrf7aYasLiK1TZdRSHkVq8US1w8K6rHIlb5DSFiINsX46H7HzBIn3R5uDfjFQNqo4voMYLMu8MisUIhk="));
	
	lay->addWidget(_NVPair);
	lay->addWidget(newLabel(tr("This record must be created by person who's rights are recorded.\n"
		"After you create this name record, emeil this name to organization so they can sign it.")));
    lay->addStretch();
	setWidget(w);
	updateSettings(false);
}
QLabel* DpoCreateRecordWidget::newLabel(const QString & s) {
	auto l = new QLabel(s);
	l->setWordWrap(true);
	l->setOpenExternalLinks(true);
	return l;
}
void DpoCreateRecordWidget::updateSettings(bool save) {
	QSettings sett;
	sett.beginGroup("DpoCreateRecordWidget");
	if(save)
		sett.setValue("name", _editName->text());
	else
		_editName->setText(sett.value("name").toString());

	if(save)
		sett.setValue("nick", _editSN->text());
	else
		_editSN->setText(sett.value("nick").toString());

	if(save)
		sett.setValue("SIG", _signature->text());
	else
		_signature->setText(sett.value("SIG").toString());
}
void DpoCreateRecordWidget::recalcValue() {
	const QString name = _editName->text().trimmed();
	const QString serial = _editSN->text().trimmed();
    if(name.isEmpty() || serial.isEmpty()) {
		_NVPair->setName({});//to display placeholderText
		_askSignature->setText({});
	} else {
		QString s = name + ':' + serial;
		if(!s.startsWith("dpo:"))
			s.prepend("dpo:");
        _NVPair->setName(s);
		_askSignature->setText(tr("Hi! I want to participate in your program, please sign my name: %1").arg(s));
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
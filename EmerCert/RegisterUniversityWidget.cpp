//RegisterUniversityWidget.cpp by Emercoin developers
#include "pch.h"
#include "RegisterUniversityWidget.h"
#include "EmailLineEdit.h"
#include "PhoneNumberLineEdit.h"

RegisterUniversityWidget::RegisterUniversityWidget() {
	setWindowTitle(tr("Register university"));
	auto w = new QWidget;
	auto lay = new QVBoxLayout(w);
	_NVPair = new NameValueEditWidget;
	_NVPair->setValueMultiline(true);

	auto description = new QLabel(tr("You must first create root record (register university) to sign diplomas"));
    description->setOpenExternalLinks(true);
    lay->addWidget(description);

	auto form = new QFormLayout;
	lay->addLayout(form);
    _editName = addLineEdit(form, QString(), tr("University abbreviation for blockchain"),
		tr("If this name is already registered, you can modify it or add random characters, like 'orig' or ':1'"));
    addLineEdit(form, "brand", tr("Full university name (brand)"), tr("There will be no conflicts within blockchain"));
    addLineEdit(form, "url", tr("Web-site address"), tr("Your university website address"));
	{
		auto lay = new QVBoxLayout;
		auto email = new EmailLineEdit;
		email->setObjectName("email");
		_edits << email;
		connect(email, &QLineEdit::textChanged, this, &RegisterUniversityWidget::recalcValue);
		lay->addWidget(email);

		QLabel* errorDesc = new QLabel;
		lay->addWidget(errorDesc);
		email->validator()->setErrorLabel(errorDesc);
		errorDesc->hide();
			
		form->addRow(tr("E-mail:"), lay);
	}
	{
		auto tel = new PhoneNumberLineEdit;
		tel->setObjectName("tel");
		connect(tel, &QLineEdit::textChanged, this, &RegisterUniversityWidget::recalcValue);
		_edits << tel;
		form->addRow(tr("Telephone"), tel);
	}
	form->addRow(new QLabel("Any other data in format: key=value (for example, type=private), each value on a new line:"));
	_editOther = new QPlainTextEdit;
	connect(_editOther, &QPlainTextEdit::textChanged, this, &RegisterUniversityWidget::recalcValue);
	form->addRow(_editOther);

	lay->addWidget(_NVPair);
    lay->addStretch();
	setWidget(w);
}
void RegisterUniversityWidget::recalcValue() {
	const QString dns = _editName->text().trimmed();
    if(dns.isEmpty())
        _NVPair->setName(QString());//to display placeholderText
    else
        _NVPair->setName("dpo:" + dns);

	QStringList parts;
    for(auto e: _edits) {
        QString value = e->text().trimmed();
		if(auto tel = dynamic_cast<PhoneNumberLineEdit*>(e))
			value = tel->toPhoneNumber();
        if(!value.isEmpty())
            parts << e->objectName() + "=" + value;
    }
	parts << _editOther->toPlainText().split('\n', QString::SkipEmptyParts);
	for(auto & s: parts)
		s = s.trimmed();
	_NVPair->setValue(parts.join('\n'));
}
QLineEdit* RegisterUniversityWidget::addLineEdit(QFormLayout*form, const QString& name,
	const QString& text, const QString& tooltip)
{
    auto edit = new QLineEdit;
    edit->setObjectName(name);
    edit->setClearButtonEnabled(true);
    connect(edit, &QLineEdit::textChanged, this, &RegisterUniversityWidget::recalcValue);
	auto label = new QLabel(text);
	label->setToolTip(tooltip);
    edit->setToolTip(tooltip);
    form->addRow(label, edit);
	if(!name.isEmpty())
		_edits << edit;
    return edit;
}
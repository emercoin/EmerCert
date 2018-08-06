//RegisterUniversityWidget.cpp by Emercoin developers
#include "pch.h"
#include "RegisterUniversityWidget.h"

RegisterUniversityWidget::RegisterUniversityWidget() {
	setWindowTitle(tr("Register university"));
	auto lay = new QVBoxLayout(this);
	_NVPair = new NameValueEditWidget;
	_NVPair->setValueMultiline(true);

	auto description = new QLabel(tr("You must first create root record (register university) to sign diplomas"));
    description->setOpenExternalLinks(true);
    lay->addWidget(description);

	auto form = new QFormLayout;
	lay->addLayout(form);
    _editName = addLineEdit(form, "", tr("University name"), tr(""));
	_edits.removeOne(_editName);
    addLineEdit(form, "brand", tr("Full university name"), tr(""));
    addLineEdit(form, "url", tr("Url"), tr("Your university website address"));
    addLineEdit(form, "email", tr("Email"), tr(""));
    addLineEdit(form, "tel", tr("Tel"), tr(""));
	form->addRow(new QLabel("Any other data in format: key=value"));
	_editOther = new QPlainTextEdit;
	connect(_editOther, &QPlainTextEdit::textChanged, this, &RegisterUniversityWidget::recalcValue);
	form->addRow(_editOther);

	lay->addWidget(_NVPair);
    lay->addStretch();
}
void RegisterUniversityWidget::recalcValue() {
	const QString dns = _editName->text().trimmed();
    if(dns.isEmpty())
        _NVPair->_resultingName->setText(QString());//to display placeholderText
    else
        _NVPair->_resultingName->setText("dpo:" + dns);

	QStringList parts;
    for(auto e: _edits) {
        QString value = e->text().trimmed();
        if(!value.isEmpty())
            parts << e->objectName() + "=" + value;
    }
	parts << _editOther->toPlainText().split('\n', QString::SkipEmptyParts);
	for(auto & s: parts)
		s = s.trimmed();
	_NVPair->setValue(parts.join('\n'));
}
QLineEdit* RegisterUniversityWidget::addLineEdit(QFormLayout*form, QString name, QString text, QString tooltip) {
    auto edit = new QLineEdit;
    edit->setObjectName(name);
    edit->setClearButtonEnabled(true);
    connect(edit, &QLineEdit::textChanged, this, &RegisterUniversityWidget::recalcValue);
	auto label = new QLabel(text);
	label->setToolTip(tooltip);
    edit->setToolTip(tooltip);
    form->addRow(label, edit);
    _edits << edit;
    return edit;
}
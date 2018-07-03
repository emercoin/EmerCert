//EnumerDialog.cpp by Emercoin developers - 2018.07.03 12:33:17
#include "pch.h"
#include "EnumerDialog.h"

struct PhoneValidator: public QValidator {
	//E.164 format https://en.wikipedia.org/wiki/E.164
	PhoneValidator(QObject*parent = 0): QValidator(parent) {}
	virtual void fixup(QString &input) const override {
		input = input.trimmed();
	}
	virtual State validate(QString &input, int &pos) const override {
		input = input.trimmed();
		for(QChar& c : input) {
			if(c=='+' || c==' ' || c=='-' || c=='\t' || c.isDigit())
				continue;
			return Invalid;
		}
		return Acceptable;
	}
};
struct PhoneNumberLineEdit: public QLineEdit {
	PhoneNumberLineEdit() {
		setValidator(new PhoneValidator(this));
		setPlaceholderText(tr("Like +124-000-000"));
	}
	QString toPhoneNumber()const {
		QString s = text();
		s.remove(' ');
		s.remove('\t');
		s.remove('-');
		return s;
	}
};
EnumerDialog::EnumerDialog() {
	setWindowTitle(tr("ENUMER"));
	
	auto lay = new QFormLayout(this);
	_NVEdit = new NameValueEditWidget;
	_NVEdit->setValueMultiline(true);
	_NVEdit->setValueReadOnly(false);
	_phone = new PhoneNumberLineEdit;
	connect(_phone, &QLineEdit::textChanged, this, &EnumerDialog::generateNVPair);
	_phone->setFocus();

	lay->addRow(new QLabel(tr("<a href=\"https://emercoin.com/en/documentation/blockchain-services/enumer\">ENUMER</a> is a free VoIP system, based on emercoin blockchain"
		"<br>\nStep 1: create ENUM record")));
	//Good russian article, maybe translate it to english: https://habr.com/company/emercoin/blog/337034/
	lay->addRow(tr("Phone number:"), _phone);//E.164 format https://en.wikipedia.org/wiki/E.164
	{
		QString str = tr("If someone created record with same phone number, just add random number suffix to create unique name and verify it's you by email");
		_antiSquatter->setToolTip(str);
		auto desc = new QLabel(tr("Suffix (?):"));
		desc->setToolTip(str);
		lay->addRow(desc, _antiSquatter);
	}
	{
		auto text = new QPlainTextEdit;
		QString str = tr(R"DEMO(Add several lines to value, like:
E2U+sip=Priority|Preference|Regex, like
E2U+sip=100|10|!^(.*)$!sip:17772325555@in.callcentric.com!
Or signature records from steps below)DEMO");
		text->setPlainText(str);
		text->setReadOnly(true);
		lay->addRow(text);
	}
	lay->addRow(_NVEdit);
	lay->addRow(new QLabel("Step 2: add this name-value pair to the emercoin blockchain"));
	
	auto labelEmail = new QLabel("Step 3: verify it by writing to <a href=\"mailto:enumer@emercoin.com\">enumer@emercoin.com</a>, get verification record and update value");
	labelEmail->setOpenExternalLinks(true);
	lay->addRow(labelEmail);
	lay->addRow(new QLabel(tr("Step 4: ")));
}
void EnumerDialog::generateNVPair() {
	QString phone = _phone->toPhoneNumber();
	QString name = QString("enum:%1:%2").arg(phone).arg(_antiSquatter->text());
	_NVEdit->_resultingName->setText(name);
}
//ManageDnsPage.cpp.cpp by emercoin developers
#include "ManageDnsPage.h"
#include "IPv4LineEdit.h"
#include <QToolButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QToolTip>
#include <QApplication>
#include <QClipboard>
#include <QLabel>
#include <QPushButton>
#include <QCommandLinkButton>

ManageDnsPage::ManageDnsPage(QWidget*parent): QWidget(parent) {
	setWindowTitle(tr("DNS names"));
	auto lay = new QVBoxLayout(this);
	_NVPair = new NameValueEditWidget;

    auto description = new QLabel(tr(
      "<a href=\"https://wiki.emercoin.com/en/EMCDNS\">EmerDNS</a> "
      "is a decentralized <a href=\"https://en.wikipedia.org/wiki/Domain_Name_System\">domain names system</a>"
      " supporting a full range of DNS <a href=\"https://en.wikipedia.org/wiki/List_of_DNS_record_types\">records.</a><br/>"
      "On this page you can prepare EmerDNS name-value pairs to use them in 'Manage names' tab."));
    description->setOpenExternalLinks(true);
    lay->addWidget(description);

	auto form = new QFormLayout;
	lay->addLayout(form);
    _editName = addLineEdit(form, "", tr("DNS name"), tr("Like mysite.com"));
    addLineEdit(form, "A", tr("A record"), tr("IPv4 address, like 185.31.209.8"));
    addLineEdit(form, "AAAA", tr("AAAA record"), tr("IPv6 address, like 2a04:5340:1:1::3"));
    addLineEdit(form, "MX", tr("MX record"), tr("Mail exchanger, like mx.yandex.ru:10"));
    addLineEdit(form, "NS", tr("NS record"), tr("Name server; delegates a DNS zone to use the given authoritative name servers"));
    addLineEdit(form, "CNAME", tr("CNAME"), tr("Canonical name; alias of one name to another: the DNS lookup will continue by retrying the lookup with the new name."));
    addLineEdit(form, "PTR", tr("PTR"), tr("Pointer to a canonical name. Unlike a CNAME, DNS processing stops and just the name is returned."));
    addLineEdit(form, "TXT", tr("TXT"), tr("Arbitrary human-readable text. Nowdays more often carries machine-readable data, such as Policy Framework, DKIM, DMARC, DNS-SD, etc."));
    addLineEdit(form, "SD", tr("SD"), tr("Subdomain - EmerDns feature"));
	lay->addWidget(_NVPair);
  
    lay->addStretch();
}
void ManageDnsPage::recalcValue() {
    const QString dns = _editName->text().trimmed();
    if(dns.isEmpty())
        _NVPair->setName(QString());//to display placeholderText
    else
        _NVPair->setName("dns:" + dns);

    QStringList parts;
    for(auto e: _edits) {
        if(e==_editName)
            continue;
        QString value = e->text().trimmed();
        if(!value.isEmpty())
            parts << e->objectName() + "=" + value;
    }
	_NVPair->setValue(parts.join('|'));
}
QLineEdit* ManageDnsPage::addLineEdit(QFormLayout*form, const QString& name,
	const QString& text, const QString& tooltip)
{
    auto edit = new QLineEdit;
    edit->setObjectName(name);
    edit->setClearButtonEnabled(true);
    connect(edit, &QLineEdit::textChanged, this, &ManageDnsPage::recalcValue);
	QString t = text;
	if(!tooltip.isEmpty() && !text.contains('?') && !t.endsWith(':')) {
		t += " (?)";
	}
	auto label = new QLabel(t);
	label->setToolTip(tooltip);
    edit->setToolTip(tooltip);
    form->addRow(label, edit);
	if(!name.isEmpty())
		_edits << edit;
    return edit;
}
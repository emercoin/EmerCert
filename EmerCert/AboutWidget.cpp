//AboutWidget.cpp by Emercoin developers
#include "pch.h"
#include "AboutWidget.h"

AboutWidget::AboutWidget(QWidget*parent): QWidget(parent) {
	setWindowTitle(tr("About"));
	setWindowIcon(QIcon(":/qt-project.org/qmessagebox/images/qtlogo-64.png"));
	QString text = tr(R"TXT(<a href="https://emercoin.com/">Emercoin</a> is a blockchain platform.
Since 2013 it has developed a wide range of easy-to-use dSDKs.
dSDK (Decentralized Software Development Kit) is a set of software development tools that allows the creation of software, 
services and solutions. Usually, it includes APIs, technical documentation and parts of code for 
fast and easy development on a certain platform.<br>
<br>
dSDKs are already implemented in numerous innovative technical solutions built on the blockchain. Emercoin offers services that have a potential to change the way different industries operate, providing means for data protection, secure storage of information, and creation of distributed services.
)TXT");
	auto lay = new QVBoxLayout(this);
	auto label = new QTextBrowser();
	label->setOpenExternalLinks(true);
	label->setText(text);
	lay->addWidget(label);

	auto qt = new QToolButton;
	qt->setIcon(QIcon(":/qt-project.org/qmessagebox/images/qtlogo-64.png"));
	qt->setIconSize({32, 32});
	qt->setText(tr("About Qt"));
	qt->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	connect(qt, &QPushButton::clicked, qApp, &QApplication::aboutQt);
	lay->addWidget(qt);

	lay->addStretch();
}

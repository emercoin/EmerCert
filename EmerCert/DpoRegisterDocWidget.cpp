//DpoRegisterDocWidget.cpp by Emercoin developers
#include "DpoRegisterDocWidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QCryptographicHash>

DpoRegisterDocWidget::DpoRegisterDocWidget() {
	setWindowTitle(tr("3) Document registration"));
	auto lay = new QVBoxLayout(this);

	lay->addWidget(new QLabel(tr("Choose a file to add to blockchain:")));
	
	{
		auto lay2 = new QHBoxLayout;
		lay->addLayout(lay2);

		_editFile = new QLineEdit;
		_editFile->setReadOnly(true);
		_editFile->setPlaceholderText(tr("Click button to the right"));
		lay2->addWidget(_editFile);

		auto open = new QPushButton(tr("Open file..."));
		open->setIcon(QIcon(":/qt-project.org/styles/commonstyle/images/standardbutton-open-32.png"));
		connect(open, &QPushButton::clicked, this, &DpoRegisterDocWidget::openFileDialog);
		lay2->addWidget(open);
	}

	_editHash = new QLineEdit(this);
	_editHash->setEnabled(false);
	_editHash->hide();
	connect(_editHash, &QLineEdit::textChanged, this, &DpoRegisterDocWidget::recalcValue);
	lay->addWidget(_editHash);

	lay->addWidget(new QLabel("You can change default document name:"));
	_editDocName = new QLineEdit;
	lay->addWidget(_editDocName);

	lay->addWidget(new QLabel("Sign next message:"));
	
	_signLabel = new QLineEdit;
	_signLabel->setReadOnly(true);
	lay->addWidget(_signLabel);
	lay->addWidget(new QLabel("Write this signature here:"));
	_editSignature = new QLineEdit;
	lay->addWidget(_editSignature);
	connect(_editSignature, &QLineEdit::textChanged, this, &DpoRegisterDocWidget::recalcValue);

	lay->addWidget(new QLabel(tr("Enter your name from the previous tab:")));
	_editName = new QLineEdit;
	_editName->setPlaceholderText(tr("Like dpo:NDI:someName"));
	_editName->setToolTip(_editName->placeholderText());
	connect(_editName, &QLineEdit::textChanged, this, &DpoRegisterDocWidget::recalcValue);
	lay->addWidget(_editName);

	_NVPair = new NameValueLineEdits;
	_NVPair->setValueMultiline(true);
	lay->addWidget(_NVPair);
	lay->addStretch();
}
void DpoRegisterDocWidget::openFileDialog() {
	QString path = QFileDialog::getOpenFileName(this, tr("Choose file to register in blockchain"), QString(),
		tr("Adobe pdf (*.pdf);;All files (*)"));
	if(path.isEmpty())
		return;
	_editFile->setText(path);
	_editDocName->setText(QFileInfo(path).completeBaseName());

	QFile file(path);
	if(!file.open(QFile::ReadOnly)) {
		QMessageBox::critical(this, qApp->applicationDisplayName(),
			tr("Can't open file %1 for reading: %2").arg(path, file.errorString()));
		return;
	}
	auto arr = file.readAll();
	auto hash = QCryptographicHash::hash(arr, QCryptographicHash::Sha256);
	_editHash->setText(hash.toHex());
}
void DpoRegisterDocWidget::recalcValue() {
	QString hash = _editHash->text().trimmed();
	if(!hash.isEmpty())
		hash.prepend("doc:");
	if(hash.isEmpty()) {
		_NVPair->setName({});//to display placeholderText
		_signLabel->setText({});
	} else {
        _NVPair->setName(hash);
		_signLabel->setText(hash);
	}

	const QString name = _editName->text().trimmed();
	const QString sig  = _editSignature->text().trimmed();
	if(name.isEmpty() || sig.isEmpty()) {
		_NVPair->setValue({});//to display placeholderText
	} else {
		QString v = QString("SIG=%1|%2\n").arg(name, sig);
		QString name = _editDocName->text().trimmed();
		if(name.isEmpty())
			name = QFileInfo(_editFile->text()).completeBaseName();
		if(name.isEmpty())
			name = QFileInfo(_editFile->text()).fileName();
		v += "name=" + name;
        _NVPair->setValue(v);
	}
}
//DpoRegisterDocWidget.cpp by Emercoin developers
#include "pch.h"
#include "DpoRegisterDocWidget.h"

DpoRegisterDocWidget::DpoRegisterDocWidget() {
	setWindowTitle(tr("Register document"));
	auto lay = new QVBoxLayout(this);

	lay->addWidget(new QLabel(tr("Choose file to register in blockchain:")));
	
	auto open = new QPushButton(tr("Open file..."));
	open->setIcon(QIcon(":/qt-project.org/styles/commonstyle/images/standardbutton-open-32.png"));
	connect(open, &QPushButton::clicked, this, &DpoRegisterDocWidget::openFileDialog);
	lay->addWidget(open);

	lay->addWidget(new QLabel("It's hash is:"));
	_editHash = new QLineEdit;
	connect(_editHash, &QLineEdit::textChanged, this, &DpoRegisterDocWidget::recalcValue);
	lay->addWidget(_editHash);

	lay->addWidget(new QLabel("Sign next message:"));
	
	_signLabel = new QLineEdit;
	_signLabel->setReadOnly(true);
	lay->addWidget(_signLabel);

	lay->addWidget(new QLabel("Write this signature here:"));
	_editSignature = new QLineEdit;
	lay->addWidget(_editSignature);
	connect(_editSignature, &QLineEdit::textChanged, this, &DpoRegisterDocWidget::recalcValue);

	lay->addWidget(new QLabel(tr("Write your name from previous tab:")));
	_editName = new QLineEdit;
	_editName->setPlaceholderText(tr("Like dpo:NDI:someName"));
	connect(_editName, &QLineEdit::textChanged, this, &DpoRegisterDocWidget::recalcValue);
	lay->addWidget(_editName);

	lay->addWidget(new QLabel("Add this signature to value instead of 'signature'"));

	_NVPair = new NameValueLineEdits;
	lay->addWidget(_NVPair);
	lay->addStretch();
}
void DpoRegisterDocWidget::openFileDialog() {
	QString path = QFileDialog::getOpenFileName(this, tr("Choose file to register in blockchain"), QString(),
		tr("Adobe pdf (*.pdf);;All files (*)"));
	if(path.isEmpty())
		return;
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
        _NVPair->setValue(QString("SIG=%1|%2").arg(name, sig));
	}
}
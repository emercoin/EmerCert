//DpoRegisterDocWidget.cpp by Emercoin developers
#include "pch.h"
#include "DpoRegisterDocWidget.h"

DpoRegisterDocWidget::DpoRegisterDocWidget() {
	auto lay = new QVBoxLayout(this);

	lay->addWidget(new QLabel(tr("Choose file to register in blockchain:")));
	
	auto open = new QPushButton(tr("Open file..."));
	open->setIcon(QIcon(":/qt-project.org/styles/commonstyle/images/standardbutton-open-32.png"));
	connect(open, &QPushButton::clicked, this, &DpoRegisterDocWidget::openFileDialog);
	lay->addWidget(open);

	_editHash = new QLineEdit;
	connect(open, &QPushButton::clicked, this, &DpoRegisterDocWidget::openFileDialog);
	lay->addWidget(_editHash);
	
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
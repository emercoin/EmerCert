//ManageSslPage.cpp by Emercoin developers
#include "pch.h"
#include "ManageSslPage.h"
#include "Settings.h"
#include "CertTableModel.h"
#include "EmailLineEdit.h"
#include "CertTableView.h"
#include "CertLogger.h"
#include "ShellImitation.h"
#include "OpenSslConfigWriter.h"
#include "OpenSslExecutable.h"

ManageSslPage::ManageSslPage(QWidget*parent): QWidget(parent) {
	setWindowTitle(tr("EmerSSL certificates"));
	auto lay = new QVBoxLayout(this);
	//https://cryptor.net/tutorial/sozdaem-ssl-sertifikat-emcssl-dlya-avtorizacii-na-saytah
	lay->addWidget(new QLabel(
		"EmerSSL allows you to automatically login without passwords on many sites using cerificate, stored in blockchain."
	));
	_view = new CertTableView;
	{
		auto lay2 = new QHBoxLayout;
		lay->addLayout(lay2);

		auto btnNew = new QPushButton(tr("New"));
		btnNew->setIcon(QIcon(":/qt-project.org/styles/commonstyle/images/file-32.png"));
		connect(btnNew, &QAbstractButton::clicked, this, &ManageSslPage::onCreate);
		lay2->addWidget(btnNew);

		_btnDelete = new QPushButton(tr("Delete"));
		_btnDelete->setIcon(QIcon(":/qt-project.org/styles/commonstyle/images/standardbutton-cancel-32.png"));
		connect(_btnDelete, &QAbstractButton::clicked, this, &ManageSslPage::onDelete);
		lay2->addWidget(_btnDelete);

		_btnGenerate = new QPushButton(tr("Generate again"));
		_btnGenerate->setToolTip(tr("Regenerate certificate (for same nickname and email) if it has been expired or has been compromised"));
		_btnGenerate->setIcon(QIcon(":/qt-project.org/styles/commonstyle/images/refresh-24.png"));
		connect(_btnGenerate, &QAbstractButton::clicked, this, &ManageSslPage::onCreate);
		lay2->addWidget(_btnGenerate);

		_btnOpenFolder = new QPushButton(tr("Open folder"));
		_btnOpenFolder->setToolTip(tr("Reveal certificate file in folder"));
		_btnOpenFolder->setIcon(QIcon(":/qt-project.org/styles/commonstyle/images/standardbutton-open-32.png"));
		connect(_btnOpenFolder, &QAbstractButton::clicked, this, &ManageSslPage::onDelete);
		lay2->addWidget(_btnOpenFolder);

		lay2->addStretch();
	}

	auto splitter = new QSplitter(Qt::Vertical);
	lay->addWidget(splitter);

	connect(_view->selectionModel(), &QItemSelectionModel::selectionChanged, this, &ManageSslPage::enableButtons);
	enableButtons();
	splitter->addWidget(_view);

	_logger = new CertLogger();
	splitter->addWidget(_logger);
	ShellImitation::s_logger = _logger;

	OpenSslConfigWriter::checkAndWrite();
	QTimer::singleShot(1, &OpenSslExecutable::isFoundOrMessageBox);
}
void ManageSslPage::enableButtons() {
	bool selected = _view->selectionModel()->hasSelection();
	_btnDelete->setEnabled(selected);
	_btnGenerate->setEnabled(selected);
	_btnOpenFolder->setEnabled(selected);
}
struct ManageSslPage::TemplateDialog: public QDialog {
	QLineEdit* _name = new QLineEdit;
	EmailLineEdit* _email = new EmailLineEdit;
	QLineEdit* _ecard = new QLineEdit;
	QLabel* _emailErrorDesc = new QLabel;
	QPushButton* _okBtn = 0;
	TemplateDialog(QWidget*parent): QDialog(parent) {
		setWindowTitle(tr("New certificate template"));
		setWindowFlag(Qt::WindowContextHelpButtonHint, false);

		auto lay = new QVBoxLayout(this);
		auto form = new QFormLayout;
		lay->addLayout(form);
		const QString strMandatoryField = tr("Mandatory field");
		_name->setPlaceholderText(strMandatoryField);
		form->addRow(tr("Name or nickname:"), _name);
		{
			auto lay = new QVBoxLayout;
			lay->addWidget(_email);
			_email->setPlaceholderText(strMandatoryField);
			lay->addWidget(_emailErrorDesc);
			_email->validator()->_labelError = _emailErrorDesc;
			_emailErrorDesc->hide();
			form->addRow(tr("E-mail:"), lay);
		}
		form->addRow(tr("Your UID to retrieve InfoCard info:"), _ecard);
		_ecard->setPlaceholderText(tr("Optional field"));

		auto box = new QDialogButtonBox;
		lay->addWidget(box);
		_okBtn = box->addButton(QDialogButtonBox::Ok);
		auto cancel = box->addButton(QDialogButtonBox::Cancel);
		_okBtn->setIcon(QIcon(":/qt-project.org/styles/commonstyle/images/standardbutton-apply-32.png"));
		cancel->setIcon(QIcon(":/qt-project.org/styles/commonstyle/images/standardbutton-cancel-32.png"));
		connect(_okBtn, &QAbstractButton::clicked, this, &QDialog::accept);
		connect(cancel, &QAbstractButton::clicked, this, &QDialog::reject);
		connect(_email, &QLineEdit::textChanged, this, &TemplateDialog::enableOk);
		connect(_name, &QLineEdit::textChanged, this, &TemplateDialog::enableOk);
		connect(_ecard, &QLineEdit::textChanged, this, &TemplateDialog::enableOk);
		lay->addStretch();
		_okBtn->setEnabled(false);
	}
	bool allValid()const {
		if(_name->text().trimmed().isEmpty())
			return false;
		if(_email->text().isEmpty())//first - simplified check to prevent detailed description
			return false;
		return _email->hasAcceptableInput();
	}
	void enableOk() {
		_okBtn->setEnabled(allValid());
	}
	virtual void accept()override {
		if(allValid())
			QDialog::accept();
	}
};
QString ManageSslPage::randName() {
	//rand key chosed to be 64-bit so EmerSSL can optimize hashes processing etc;
	//also in plain C 64bit integers are much easier to manipulate than strings, son int64 are used;
	//we can't use std::random_device because it's deterministic on MinGW https://sourceforge.net/p/mingw-w64/bugs/338/
	QByteArray uid = QUuid::createUuid().toByteArray();
	uid = QCryptographicHash::hash(uid, QCryptographicHash::Sha256);
	uid.truncate(8);
	return uid.toHex();
}
void ManageSslPage::onCreate() {
	TemplateDialog dlg(this);
	if(dlg.exec()!=QDialog::Accepted)
		return;
	const QString name = dlg._name->text().trimmed();
	const QString mail = dlg._email->text().trimmed();
	const QString ecard = dlg._ecard->text().trimmed();
	QString contents = QString("/CN=%1/emailAddress=%2")
		.arg(name).arg(mail);
	if(!ecard.isEmpty())
		contents += "/UID=" + ecard;
	contents += '\n';
	QString fileNameTemplate = name + ' ' + mail;
	for(QChar & c : fileNameTemplate) {
		if(c.isDigit() || c.isLetter() || c==' ' || c=='.' || c=='@')
			c;
		else
			c = '.';
	}
	QString fileName = randName() + ".tpl";
	QDir dir = Settings::certDir();
	QString path = dir.absoluteFilePath(fileName);
	QString error;
	if(!ShellImitation::write(path, contents.toUtf8(), error))
		return;
	_view->model()->reload();
	int index = _view->model()->indexByFile(path);
	Q_ASSERT(index!=-1);
	if(-1==index)
		return;
	_view->selectRow(index);
	_view->setFocus();
	_view->generateCertForSelectedRow();
}
void ManageSslPage::onDelete() {
	auto rows = _view->selectionModel()->selectedRows();
	if(rows.isEmpty())
		return;
	_logger->clear();
	_view->model()->removeRows(rows);
}
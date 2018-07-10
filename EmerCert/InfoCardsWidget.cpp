//InfoCardsWidget.cpp by Emercoin developers
#include "pch.h"
#include "InfoCardsWidget.h"
#include "InfoCardDialog.h"
#include "InfoCardTableView.h"
#include "InfoCardTableModel.h"
#include "CertLogger.h"
#include "ShellImitation.h"
#include "Settings.h"
#include "OpenSslExecutable.h"
#include "InfoCardDialog.h"

InfoCardsWidget::InfoCardsWidget(QWidget*parent): QWidget(parent) {
	setWindowTitle(tr("InfoCard"));
	auto lay = new QVBoxLayout(this);
	//https://cryptor.net/tutorial/sozdaem-ssl-sertifikat-emcssl-dlya-avtorizacii-na-saytah
	auto label = new QLabel(
		"<a href=\"https://docs.emercoin.com/en/Blockchain_Services/EmerSSL/EmerSSL_InfoCard.html\">InfoCards</a> is a decentralized distributed 'business card' system on the Emercoin blockchain that complements EmerSSL's passwordless login");
	label->setOpenExternalLinks(true);
	lay->addWidget(label);
	_view = new InfoCardTableView;
	{
		auto lay2 = new QHBoxLayout;
		lay->addLayout(lay2);

		auto btnNew = new QPushButton(tr("New InfoCard"));
		btnNew->setIcon(QIcon(":/qt-project.org/styles/commonstyle/images/file-32.png"));
		btnNew->setShortcut(QKeySequence("Ctrl+N"));
		connect(btnNew, &QAbstractButton::clicked, this, &InfoCardsWidget::onCreate);
		lay2->addWidget(btnNew);

		_btnDelete = new QPushButton(tr("Delete selected"));
		_btnDelete->setIcon(QIcon(":/qt-project.org/styles/commonstyle/images/standardbutton-cancel-32.png"));
		connect(_btnDelete, &QAbstractButton::clicked, this, &InfoCardsWidget::onDelete);
		lay2->addWidget(_btnDelete);

		_btnOpenFolder = new QPushButton(tr("Open folder"));
		_btnOpenFolder->setToolTip(tr("Reveal InfoCard file in folder"));
		_btnOpenFolder->setIcon(QIcon(":/qt-project.org/styles/commonstyle/images/standardbutton-open-32.png"));
		connect(_btnOpenFolder, &QAbstractButton::clicked, _view, &InfoCardTableView::showInExplorer);
		lay2->addWidget(_btnOpenFolder);

		lay2->addStretch();
	}

	auto splitter = new QSplitter(Qt::Vertical);
	lay->addWidget(splitter);

	connect(_view->selectionModel(), &QItemSelectionModel::selectionChanged, this, &InfoCardsWidget::enableButtons);
	enableButtons();
	splitter->addWidget(_view);

	_logger = new CertLogger();
	splitter->addWidget(_logger);
	ShellImitation::s_logger = _logger;

	QTimer::singleShot(1, &OpenSslExecutable::isFoundOrMessageBox);
}
void InfoCardsWidget::enableButtons() {
	bool selected = _view->selectionModel()->hasSelection();
	_btnDelete->setEnabled(selected);
	//_btnGenerate->setEnabled(selected);
	_btnOpenFolder->setEnabled(selected);
}
QString InfoCardsWidget::randName() {
	//rand key chosed to be 64-bit so EmerSSL can optimize hashes processing etc;
	//also in plain C 64bit integers are much easier to manipulate than strings, son int64 are used;
	//we can't use std::random_device because it's deterministic on MinGW https://sourceforge.net/p/mingw-w64/bugs/338/
	QByteArray uid = QUuid::createUuid().toByteArray();
	uid = QCryptographicHash::hash(uid, QCryptographicHash::Sha256);
	uid.truncate(8);
	return uid.toHex();
}
void InfoCardsWidget::onCreate() {
	InfoCardDialog dlg(this);
	dlg.resize(sizeHint());
	if(dlg.exec()!=QDialog::Accepted)
		return;
	QString contents = dlg._text->toPlainText().trimmed();
	contents += '\n';
	QString fileName = randName() + ".info";
	QDir dir = Settings::certDir();
	QString path = dir.absoluteFilePath(fileName);
	QString error;
	Shell::s_logger->setFileNear(dir, fileName);
	if(!Shell::write(path, contents.toUtf8(), error))
		return;
	_view->model()->reload();
	int index = _view->model()->indexByFile(path);
	Q_ASSERT(index!=-1);
	if(-1==index)
		return;
	_view->selectRow(index);
	_view->setFocus();
	//_view->generateInfoZForSelectedRow();
}
void InfoCardsWidget::onDelete() {
	auto rows = _view->selectionModel()->selectedRows();
	if(rows.isEmpty())
		return;
	_logger->clear();
	_view->model()->removeRows(rows);
}
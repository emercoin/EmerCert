#include "pch.h"
#include "MainWindow.h"
#include "InfoCardsWidget.h"
#include "ManageSslPage.h"
#include "ManageDnsPage.h"
#include "EnumerDialog.h"
#include "DiplomaWidget.h"
#include "DpoWidget.h"

MainWindow::MainWindow(QWidget *parent): QTabWidget(parent) {
	setWindowTitle(tr("EmerCert Manager ") + QCoreApplication::applicationVersion());
	add(new ManageSslPage);
	add(new InfoCardsWidget);
	add(new ManageDnsPage);
	add(new DpoWidget);
	add(new DiplomaWidget);
#ifdef _DEBUG
	add(new EnumerDialog);
#endif

	auto qt = new QPushButton(QIcon(":/qt-project.org/qmessagebox/images/qtlogo-64.png"), tr("About Qt"));
	connect(qt, &QPushButton::clicked, qApp, &QApplication::aboutQt);
	setCornerWidget(qt);

	auto quit = new QAction(tr("Quit"));
	quit->setShortcut(QKeySequence("Ctrl+Q"));
	connect(quit, &QAction::triggered, qApp, &QCoreApplication::quit);
	addAction(quit);

	QSettings sett;
	int index = sett.value("MainWindow.tabIndex", 0).toInt();
	index = qBound(0, index, count()-1);
	setCurrentIndex(index);
}
void MainWindow::add(QWidget *w) {
	addTab(w, w->windowIcon(), w->windowTitle());
}
void MainWindow::closeEvent(QCloseEvent *e) {
	QSettings sett;
	sett.setValue("MainWindow.tabIndex", currentIndex());
	QTabWidget::closeEvent(e);
}
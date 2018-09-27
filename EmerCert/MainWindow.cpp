#include "pch.h"
#include "MainWindow.h"
#include "InfoCardsWidget.h"
#include "ManageSslPage.h"
#include "ManageDnsPage.h"
#include "EnumerDialog.h"
#include "DiplomaWidget.h"
#include "DpoWidget.h"
#include "AboutWidget.h"

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
	add(new AboutWidget);
	
	setIconSize({32, 32});
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
MainWindow::~MainWindow() {
	QSettings sett;
	sett.setValue("MainWindow.tabIndex", currentIndex());
}
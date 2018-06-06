#include "pch.h"
#include "MainWindow.h"
#include "InfoCardsWidget.h"
#include "ManageSslPage.h"
#include "ManageDnsPage.h"

MainWindow::MainWindow(QWidget *parent): QTabWidget(parent) {
	setWindowTitle(tr("EmerCert Manager ") + QCoreApplication::applicationVersion());
	add(new ManageSslPage);
	add(new ManageDnsPage);

	auto qt = new QPushButton(QIcon(":/qt-project.org/qmessagebox/images/qtlogo-64.png"), tr("About Qt"));
	connect(qt, &QPushButton::clicked, qApp, &QApplication::aboutQt);
	setCornerWidget(qt);

	auto quit = new QAction(tr("Quit"));
	quit->setShortcut(QKeySequence("Ctrl+Q"));
	connect(quit, &QAction::triggered, qApp, &QCoreApplication::quit);
	addAction(quit);
}
void MainWindow::add(QWidget *w) {
	addTab(w, w->windowTitle());
}
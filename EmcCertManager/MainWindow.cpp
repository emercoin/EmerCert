#include "pch.h"
#include "MainWindow.h"
#include "InfoCardsWidget.h"
#include "ManageSslPage.h"

MainWindow::MainWindow(QWidget *parent): QSplitter(parent) {
	setWindowTitle(tr("Emer Cert Manager"));
	//add(new InfoCardsWidget);
	add(new ManageSslPage);
}
void MainWindow::add(QWidget *w) {
	auto tab = new QTabWidget;
	tab->addTab(w, w->windowTitle());
	addWidget(tab);
}
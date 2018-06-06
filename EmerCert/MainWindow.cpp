#include "pch.h"
#include "MainWindow.h"
#include "InfoCardsWidget.h"
#include "ManageSslPage.h"
#include "ManageDnsPage.h"

MainWindow::MainWindow(QWidget *parent): QTabWidget(parent) {
	setWindowTitle(tr("EmerCert Manager"));
	//add(new InfoCardsWidget);
	add(new ManageSslPage);
	add(new ManageDnsPage);
}
void MainWindow::add(QWidget *w) {
	addTab(w, w->windowTitle());
}
#include "pch.h"
#include "MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	QCoreApplication::setApplicationName("EmerCert");
	QCoreApplication::setApplicationVersion("v0.6.3");
	QCoreApplication::setOrganizationName("emercoin");
	QCoreApplication::setOrganizationDomain("emercoin.com");
	MainWindow w;
	w.showNormal();
	return a.exec();
}

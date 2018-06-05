#include "pch.h"
#include "MainWindow.h"
#include "ManageSslPage.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	ManageSslPage w;
	w.showMaximized();
	return a.exec();
}

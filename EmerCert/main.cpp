#include "pch.h"
#include "MainWindow.h"
#include <QtWidgets/QApplication>

QtMessageHandler g_oldQtMessageHandler;
void myMsgHandler(QtMsgType type, const QMessageLogContext & context, const QString &msg) {
	if(type!=QtInfoMsg)
		int t=3;//breakpoint here
	g_oldQtMessageHandler(type, context, msg);
}
int main(int argc, char *argv[]) {
	g_oldQtMessageHandler = qInstallMessageHandler(myMsgHandler);
	QApplication a(argc, argv);
	QCoreApplication::setApplicationName("EmerCert");
	QCoreApplication::setApplicationVersion("v0.6.3");
	QCoreApplication::setOrganizationName("emercoin");
	QCoreApplication::setOrganizationDomain("emercoin.com");
	MainWindow w;
	w.showNormal();
	return a.exec();
}

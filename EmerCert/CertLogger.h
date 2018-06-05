//CertLogger.h by Emercoin developers
#pragma once

class CertLogger: public QTextBrowser {
	public:
		void append(const QString & s);
		void setFile(const QString & path);//read from and log to
		void clear();
	protected:
		QFile _file;

		void closeEvent(QCloseEvent *event);
};
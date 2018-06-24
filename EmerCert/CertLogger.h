//CertLogger.h by Emercoin developers
#pragma once

class CertLogger: public QTextBrowser {
	public:
		CertLogger();
		void append(const QString & s);
		void setFile(const QString & path);//read from and log to
		void setFileNear(const QDir & dir, const QString & fileName);
		void clear();
	protected:
		QFile _file;

		void closeEvent(QCloseEvent *event);
};
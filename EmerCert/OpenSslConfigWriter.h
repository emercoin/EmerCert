//OpenSslConfigWriter.h by Emercoin developers
#pragma once
class CertLogger;

class OpenSslConfigWriter {
	public:
		OpenSslConfigWriter(CertLogger*logger);
		QString checkAndWrite();
	protected:
		CertLogger* _logger = 0;
		bool writeIfAbsent(const QString & subPath, const char* strContents, QString & error);
};
//OpenSslConfigWriter.h by Emercoin developers
#pragma once

class OpenSslConfigWriter {
	public:
		static QString checkAndWrite();
	protected:
		static bool writeIfAbsent(const QString & subPath, const char* strContents, QString & error);
};
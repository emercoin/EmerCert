//ShellImitation.h by Emercoin developers
#pragma once
#include "CertLogger.h"

struct ShellImitation {
	static QPointer<CertLogger> s_logger;
	static void maybeLog(const QString & s);

	static bool touch(const QDir & dir, const QString & fileName, QString & err);
	static bool mkpath(const QDir & dir, const QString & path, QString & error, int tries = 5);
	static bool write(const QString & path, const QByteArray & what, QString &err);
	static bool removeRecursiveFilesOnly(QDir & dir, QString &err);
	protected:
	static QString tr(const char*c);
};
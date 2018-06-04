//Settings.cpp by Emercoin developers
#include "pch.h"
#include "Settings.h"

QDir Settings::certDir() {
	QDir dir = qApp->applicationDirPath();
	bool ok = dir.mkpath("certificates");
	Q_ASSERT(ok && dir.exists());
	return dir;
}
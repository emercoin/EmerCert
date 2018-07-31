//Settings.cpp by Emercoin developers
#include "pch.h"
#include "Settings.h"

QDir Settings::certDir() {
	QString str = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
	str = QDir::toNativeSeparators(str);
	QDir dir = str;
	bool ok = dir.mkpath(".");
	Q_ASSERT(ok && dir.exists());
	return dir;
}
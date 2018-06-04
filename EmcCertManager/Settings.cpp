//Settings.cpp by Emercoin developers
#include "pch.h"
#include "Settings.h"

QDir Settings::certDir() {
	//QDir dir = "D:\\g\\emcssl";
	QDir dir = "C:\\Users\\neurocod\\AppData\\Roaming\\EmerCoin\\certificates";
	bool ok = dir.mkpath(".");
	Q_ASSERT(ok && dir.exists());
	return dir;
}
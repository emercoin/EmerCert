//InfoCardTableModel.cpp by Emercoin developers
#include "pch.h"
#include "InfoCardTableModel.h"
#include "ShellImitation.h"
#include "Settings.h"
#include "OpenSslExecutable.h"

QString InfoCardTableModel::Row::logFilePath()const {
	return pathByExt("log");
}
QString InfoCardTableModel::Row::loadFromFile(const QFileInfo & entry) {//QString::isEmpty -> ok
	_file = entry.filePath();
	_baseName = entry.baseName();
	_dir = entry.dir();
	QFile file(_file);
	if(!file.open(QFile::ReadOnly))
		return file.errorString();
	const QByteArray arr = file.readAll();
	_text = arr;
	parse(_text);
	return QString();
}
using Shell = ShellImitation;
QString InfoCardTableModel::Row::pathByExt(const QString & extension)const {
	return _dir.absoluteFilePath(_baseName + '.' + extension);
}
void InfoCardTableModel::Row::add(const QString & key, const QString & value, bool replace) {
	InfoCard::add(key, value, replace);
	if(key=="Import")
		return;
	if(!_displayedText.isEmpty())
		_displayedText += "; ";
	_displayedText += key % ": " % value;
}
QString InfoCardTableModel::Row::removeFiles() {
	for(auto ext: QString("info|infoz|log").split('|')) {
		QString path = pathByExt(ext);
		if(QFile::exists(path)) {
			if(!QFile::remove(path)) {
				return QObject::tr("Can't remove %1").arg(path);
			}
		}
	}
	return QString();
}
InfoCardTableModel::InfoCardTableModel(QObject*parent): QAbstractTableModel(parent) {
	reload();
}
void InfoCardTableModel::removeRows(const QModelIndexList & rows) {
	if(rows.isEmpty())
		return;
	int row = rows[0].row();
	if(row < 0 || row >= _rows.count()) {
		Q_ASSERT(0);
		return;
	}
	Row & r = _rows[row];
	QString error = r.removeFiles();
	if(!error.isEmpty()) {
		reload();
		QMessageBox::critical(0, tr("Error"), tr("Error removing files: %1").arg(error));
		return;
	}
	beginRemoveRows(QModelIndex(), row, row);
	_rows.removeAt(row);
	endRemoveRows();
}
void InfoCardTableModel::reload() {
	beginResetModel();
	_rows.clear();
	QDir dir = Settings::certDir();
	const QFileInfoList list = dir.entryInfoList(QStringList() << "*.info", QDir::Files, QDir::Name);
	for(const QFileInfo & entry : list) {
		Row item;
		const QString code = item.loadFromFile(entry);
		if(code.isEmpty()) {
			_rows << item;
		} else {
			QMessageBox::critical(0, tr("Can't load template file"), code);
		}
	}
	endResetModel();
}
int InfoCardTableModel::rowCount(const QModelIndex& index)const {
	return _rows.count();
}
int InfoCardTableModel::columnCount(const QModelIndex& index)const {
	return ColEnd;
}
QVariant InfoCardTableModel::headerData(int section, Qt::Orientation orientation, int role)const {
	if(orientation == Qt::Vertical) {
		if(role == Qt::DisplayRole || role == Qt::ToolTipRole)
			return section + 1;
	} else {
		if(role == Qt::DisplayRole || role == Qt::ToolTipRole) {
			static_assert(ColEnd == 1, "update switch");
			switch(section) {
				case ColText: return tr("Values");
			}
		}
	}
	return QVariant();
}
QVariant InfoCardTableModel::data(const QModelIndex &index, int role) const {
	int row = index.row();
	if(row<0 || row >= rowCount())
		return QVariant();
	const auto & item = _rows.at(row);
	if(role == Qt::DisplayRole || role == Qt::ToolTipRole) {
		static_assert(ColEnd == 1, "update switch");
		switch(index.column()) {
			case ColText: return item._displayedText;
			//case ColDateTime: return item._InfoCardId;
		}
	}
	return QVariant();
}
int InfoCardTableModel::indexByFile(const QString & s)const {
	for(int i = 0; i < _rows.count(); ++i) {
		if(_rows[i]._file==s)
			return i;
	}
	return -1;
}
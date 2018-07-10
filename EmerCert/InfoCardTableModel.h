//InfoCardTableModel.h by Emercoin developers
#pragma once
#include "InfoCard.h"

class InfoCardTableModel: public QAbstractTableModel {
	public:
	enum Columns {
		ColText,
		//ColInfoCardId,
		
		ColEnd
	};
	enum CertType {
		EC,
		RSA
	};
	struct Row: public InfoCard {
		QString _text;
		QString _displayedText;
		QString _InfoCardId;//optional
		QDir _dir;
		QString _file;
		QString _baseName;
		
		QString logFilePath()const;
		QString loadFromFile(const QFileInfo & entry);//returns error, isEmpty() -> ok
		QString removeFiles();//returns error, isEmpty() -> ok
		QString pathByExt(const QString & extension)const;
		virtual void add(const QString & key, const QString & value, bool replace)override;
	};
	QList<Row> _rows;
	
	InfoCardTableModel(QObject*parent);
	void reload();
	int indexByFile(const QString & s)const;
	void removeRows(const QModelIndexList & rows);
	virtual int rowCount(const QModelIndex& index = QModelIndex())const override;
	virtual int columnCount(const QModelIndex& index = QModelIndex())const override;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole)const override;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};
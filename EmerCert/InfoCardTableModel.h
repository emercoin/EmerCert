//InfoCardTableModel.h by Emercoin developers
#pragma once
#include "InfoCard.h"

class InfoCardTableModel: public QAbstractTableModel {
	public:
		InfoCardTableModel(QObject*parent);
		~InfoCardTableModel();
		enum Columns {
			ColText,
			//ColInfoCardId,
		
			ColEnd
		};
		enum CertType {
			EC,
			RSA
		};
		struct Item: public InfoCard {
			QString _displayedText;
			QString _InfoCardId;//optional
			QDir _dir;
			QString _baseName;
		
			Item(const QString & path);
			QString logFilePath()const;
			QString loadFromFile(const QFileInfo & entry);//returns error, isEmpty() -> ok
			QString removeFiles();//returns error, isEmpty() -> ok
			QString pathByExt(const QString & extension)const;
			virtual void add(const QString & key, const QString & value, bool replace)override;
		};
		Item* itemBy(int row)const;
		void reload();
		int indexByFile(const QString & s)const;
		void removeRows(const QModelIndexList & rows);
		virtual int rowCount(const QModelIndex& index = QModelIndex())const override;
		virtual int columnCount(const QModelIndex& index = QModelIndex())const override;
		virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole)const override;
		virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
		virtual Qt::ItemFlags flags(const QModelIndex &index)const override;
	protected:
		QList<Item*> _rows;
};
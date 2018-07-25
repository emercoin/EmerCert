//InfoCard.h by Emercoin developers
#pragma once

class InfoCard {
	public:
		QHash<QString, QString> _values;
		QString _text;
		const QString _fileName;

		InfoCard(const QString& fileName);
		QString load();//"" -> ok
		QString save()const;//"" -> ok
		virtual void parse();
		static QString tr(const char *t);
		QString encrypt();//"" -> ok
	protected:
		QString indexAndPassFromText(QString & index, QString & pass);
		virtual void add(const QString & key, const QString & value, bool replace);
		static void removeComment(QString & line);
		static void removeComments(QString & text);
		void parseLine(QString & line, QString & lastKey);
		InfoCard()=delete;
};
//InfoCard.h by Emercoin developers
#pragma once

class InfoCard {
	public:
		QHash<QString, QString> _values;
		QString _text;

		void parse(const QString & file);
	protected:
		virtual void add(const QString & key, const QString & value, bool replace);
		static void removeComment(QString & line);
		void parseLine(QString & line, QString & lastKey);
};
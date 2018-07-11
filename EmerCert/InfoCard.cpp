//InfoCard.cpp by Emercoin developers
#include "pch.h"
#include "InfoCard.h"

void InfoCard::parse(const QString & file_) {
	QString file = file_;
	file.replace('\r', '\n');
	file.replace('\t', ' ');
	auto lines = file.split('\n', QString::SkipEmptyParts);
	QString lastKey;
	for(QString & line : lines) {
		parseLine(line, lastKey);
	}
}
void InfoCard::add(const QString & key_, const QString & value_, bool replace) {
	QString key = key_.trimmed();
	QString value = value_.trimmed();
	if(key.endsWith('+')) {
		key.truncate(key.length()-2);
		replace = false;
	}
	for(QChar c: key) {
		Q_ASSERT(!c.isSpace());
		if(c.isSpace())
			return;
	}
	if(replace)
		_values.insert(key, value);
	else
		_values.insertMulti(key, value);
}
void InfoCard::parseLine(QString & line, QString & lastKey) {
	removeComment(line);
	if(line.isEmpty())
		return;
	if(line[0].isSpace()) {
		if(lastKey.isEmpty())
			return;
		line = line.trimmed();
		if(line.isEmpty())
			return;
		add(lastKey, line, false);
		return;
	}
	for(int i = 1; i < line.count(); ++i) {
		if(line[i].isSpace()) {
			lastKey = line.left(i);
			QString val = line.mid(i).trimmed();
			if(!val.isEmpty())
				add(lastKey, val, true);
			break;
		}
	}
}
void InfoCard::removeComment(QString & line) {
	for(int i = line.indexOf('#'); i < line.count(); ) {
		if(-1==i)
			return;
		if(i>0 && line[i-1]=='\\') {//escaped
			++i;
			i = line.indexOf('#', i);
			continue;
		}
		line.truncate(i);
		return;
	}
}
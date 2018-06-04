//ValidatorToLabel.h by Emercoin developers
#pragma once

class ValidatorToLabel: public QValidator {
	public:
		QLabel* _labelError = 0;//if set - show error there
		ValidatorToLabel(QObject*parent): QValidator(parent) {}
		QValidator::State set(QValidator::State state, QString str = QString())const;
		QValidator::State set(const QString & str)const { return set(QValidator::Intermediate, str); }
		QValidator::State setOk()const { return set(QValidator::Acceptable); }
};
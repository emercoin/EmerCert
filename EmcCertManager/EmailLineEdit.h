//EmailLineEdit.h by Emercoin developers
#pragma once
#include "EmailValidator.h"

class EmailLineEdit: public QLineEdit {
	public:
		EmailLineEdit();
		EmailValidator* validator()const { return _validator; }
	protected:
		EmailValidator* _validator = 0;
};
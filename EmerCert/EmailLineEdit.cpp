//EmailLineEdit.cpp by Emercoin developers
#include "pch.h"
#include "EmailLineEdit.h"

EmailLineEdit::EmailLineEdit() {
	_validator = new EmailValidator(this);
	setValidator(_validator);
}
//PhoneNumberLineEdit.h by Emercoin developers

struct PhoneNumberLineEdit: public QLineEdit {
	PhoneNumberLineEdit();
	QString toPhoneNumber()const;
};
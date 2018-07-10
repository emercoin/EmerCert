//EnumerDialog.h by Emercoin developers
#pragma once
#include "NameValueEditWidget.h"
class PhoneNumberLineEdit;

class EnumerDialog: public QWidget {
	public:
		EnumerDialog();
	protected:
		PhoneNumberLineEdit* _phone = 0;
		QSpinBox* _antiSquatter = new QSpinBox;
		
		NameValueEditWidget* _NVEdit = 0;
		void generateNVPair();
};
//EnumerDialog.h by Emercoin developers - 2018.07.03 12:33:17
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
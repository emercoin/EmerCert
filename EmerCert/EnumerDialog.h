//EnumerDialog.h by Emercoin developers
#pragma once
#include "NameValueLineEdits.h"
class PhoneNumberLineEdit;

class EnumerDialog: public QWidget {
	public:
		EnumerDialog();
	protected:
		PhoneNumberLineEdit* _phone = 0;
		QSpinBox* _antiSquatter = new QSpinBox;
		
		NameValueLineEdits* _NVEdit = 0;
		void generateNVPair();
};
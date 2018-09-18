//DpoRegisterDocWidget.h by Emercoin developers
#pragma once
#include "NameValueLineEdits.h"

class DpoRegisterDocWidget: public QWidget {
	public:
		DpoRegisterDocWidget();
	protected:
		void openFileDialog();
		void recalcValue();

		//QLineEdit* _editFile = 0;
		QLineEdit* _editHash = 0;
		QLineEdit* _editSignature = 0;
		QLineEdit* _editName = 0;
		QLineEdit* _signLabel= 0;
		NameValueLineEdits* _NVPair = 0;
};
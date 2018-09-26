//DpoRegisterDocWidget.h by Emercoin developers
#pragma once
#include "NameValueLineEdits.h"

class DpoRegisterDocWidget: public QWidget {
	public:
		DpoRegisterDocWidget();

		NameValueLineEdits* _NVPair = 0;
		QLineEdit* _editName = 0;
	protected:
		void openFileDialog();
		void recalcValue();

		QLineEdit* _editFile = 0;
		QLineEdit* _editDocName = 0;
		QLineEdit* _editHash = 0;
		QLineEdit* _editSignature = 0;
		QLineEdit* _signLabel= 0;
};
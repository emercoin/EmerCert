//DpoRegisterDocWidget.h by Emercoin developers
#pragma once
#include "NameValueLineEdits.h"

class DpoRegisterDocWidget: public QWidget {
	public:
		DpoRegisterDocWidget();
	protected:
		void openFileDialog();
		QLineEdit* _editHash = 0;
};
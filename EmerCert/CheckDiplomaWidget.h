//CheckDiplomaWidget.h by Emercoin developers
#pragma once

class CheckDiplomaWidget: public QWidget {
	public:
		CheckDiplomaWidget();
	protected:
		QLineEdit* _name = 0;
		QLineEdit* _university = 0;
		QSpinBox* _year = 0;
		void onSearch();
};
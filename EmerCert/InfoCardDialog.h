//InfoCardDialog.h by Emercoin developers
#pragma once

class InfoCardDialog: public QDialog {
	public:
		InfoCardDialog(QWidget*parent = 0);
	protected:
		QFormLayout* _lay = 0;
		struct Row {
			QString _name;
			bool _multiline = false;
			QLineEdit* _line = 0;
			QPlainTextEdit* _text = 0;
			QString text()const;
			QWidget* widget()const;
		};
		QList<Row> _rows;
		void add(Row & row);
};
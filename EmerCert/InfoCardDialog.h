//InfoCardDialog.h by Emercoin developers
#pragma once

class InfoCardDialog: public QDialog {
	public:
		InfoCardDialog(QWidget*parent=0);
		bool allValid()const;
		void addExample(QTabWidget*tabs, int n);
		void enableOk();
		virtual void accept()override;

		QLabel* _id = new QLabel;
		QTextEdit* _text = new QTextEdit;
		QPushButton* _okBtn = 0;
		QString text()const;
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
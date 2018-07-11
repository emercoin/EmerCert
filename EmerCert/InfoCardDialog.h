//InfoCardDialog.h by Emercoin developers
#pragma once
class InfoCardTextEdit;

class InfoCardDialog: public QDialog {
	public:
		InfoCardDialog(QWidget*parent=0);
		bool allValid()const;
		void addExample(QTabWidget*tabs, int n);
		void enableOk();
		virtual void accept()override;

		QLabel* _id = new QLabel;
		QPushButton* _okBtn = 0;
		QString text()const;
		void setText(const QString & s);
	protected:
		InfoCardTextEdit* _text = 0;
		QFormLayout* _lay = 0;
		struct Item {
			QString _name;
			bool _multiline = false;
			QLineEdit* _line = 0;
			QPlainTextEdit* _text = 0;
			QString text()const;
			QWidget* widget()const;
		};
		QList<Item> _rows;
		void add(Item & row);
};
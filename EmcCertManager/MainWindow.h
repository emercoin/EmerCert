#pragma once

class MainWindow: public QSplitter {
	Q_OBJECT
	public:
		MainWindow(QWidget *parent = 0);
	protected:
		void add(QWidget *w);
};
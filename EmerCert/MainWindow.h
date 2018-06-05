#pragma once

class MainWindow: public QSplitter {
	public:
		MainWindow(QWidget *parent = 0);
	protected:
		void add(QWidget *w);
};
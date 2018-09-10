#pragma once

class MainWindow: public QTabWidget {
	public:
		MainWindow(QWidget *parent = 0);
		~MainWindow();
	protected:
		void add(QWidget *w);
};
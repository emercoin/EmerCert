#pragma once

class MainWindow: public QTabWidget {
	public:
		MainWindow(QWidget *parent = 0);
	protected:
		void add(QWidget *w);
		virtual void closeEvent(QCloseEvent *e)override;
};
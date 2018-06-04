//InfoCardsWidget.h by Emercoin developers
#pragma once

class InfoCardsWidget: public QWidget {
	public:
		InfoCardsWidget(QWidget*parent=0);
		virtual ~InfoCardsWidget() {}
	protected:
		QPushButton* _btnDelete = 0;

		void onDelete();
		void onCreate();
		void onView();

		struct View;
		struct Model;
};
//InfoCardsWidget.cpp by Emercoin developers
#include "pch.h"
#include "InfoCardsWidget.h"

struct InfoCardsWidget::View: public QListWidget {
	View() {

	}
};
InfoCardsWidget::InfoCardsWidget(QWidget*parent): QWidget(parent) {
	setWindowTitle(tr("InfoCard"));
	auto lay = new QVBoxLayout(this);
	{
		auto lay2 = new QHBoxLayout;
		lay->addLayout(lay2);

		auto btnNew = new QPushButton(tr("New"));
		connect(btnNew, &QAbstractButton::clicked, this, &InfoCardsWidget::onCreate);
		lay2->addWidget(btnNew);

		_btnDelete = new QPushButton(QIcon(":/qt-project.org/styles/commonstyle/images/standardbutton-cancel-32.png"), tr("Delete"));
		connect(_btnDelete, &QAbstractButton::clicked, this, &InfoCardsWidget::onDelete);
		lay2->addWidget(_btnDelete);
	}

	auto view = new View;
	lay->addWidget(view);
}
void InfoCardsWidget::onDelete() {

}
void InfoCardsWidget::onCreate() {

}
void InfoCardsWidget::onView() {

}
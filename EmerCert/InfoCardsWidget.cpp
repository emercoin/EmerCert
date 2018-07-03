//InfoCardsWidget.cpp by Emercoin developers
#include "pch.h"
#include "InfoCardsWidget.h"
#include "InfoCardDialog.h"

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

		auto btnNew = new QPushButton(tr("New InfoCard"));
		btnNew->setIcon(QIcon(":/qt-project.org/styles/commonstyle/images/file-32.png"));
		btnNew->setShortcut(QKeySequence("Ctrl+N"));
		connect(btnNew, &QAbstractButton::clicked, this, &InfoCardsWidget::onCreate);
		lay2->addWidget(btnNew);

		_btnDelete = new QPushButton(tr("Delete"));
		_btnDelete->setIcon(QIcon(":/qt-project.org/styles/commonstyle/images/standardbutton-cancel-32.png"));
		connect(_btnDelete, &QAbstractButton::clicked, this, &InfoCardsWidget::onDelete);
		lay2->addWidget(_btnDelete);

		lay2->addStretch();
	}

	auto view = new View;
	lay->addWidget(view);

	//onCreate();
}
void InfoCardsWidget::onDelete() {

}
void InfoCardsWidget::onCreate() {
	InfoCardDialog d(this);
	d.exec();
}
void InfoCardsWidget::onView() {

}
//DpoUseCaseScheme.cpp by Emercoin developers - 2018.09.27 15:00:50
#include "pch.h"
#include "DpoUseCaseScheme.h"

DpoUseCaseScheme::DpoUseCaseScheme() {
	setWindowTitle(tr("Scheme"));

	auto lay = new QVBoxLayout(this);
	//auto text = new QLabel(tr(
	//R"HTML(<b>Assignment of responsibilities for DPO</b><br>
	//The system allows to verify users, who can add  authenicated documents that can be trusted)HTML"));
	//lay->addWidget(text);

	auto image = new QLabel;
	image->setPixmap(QPixmap(":/icons/DPO use case 2.png"));
	lay->addWidget(image);
}

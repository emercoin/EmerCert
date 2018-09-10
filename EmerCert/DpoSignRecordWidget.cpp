﻿//DpoSignRecord.cpp by Emercoin developers
#include "pch.h"
#include "DpoSignRecordWidget.h"

DpoSignRecordWidget::DpoSignRecordWidget() {
	setAlignment(Qt::AlignLeft|Qt::AlignTop);
	setWindowTitle(tr("3) Sign ownership record from step 2"));
	setWordWrap(true);
	setText(tr(R"TXT(<b>If you created record</b> (with name like dpo:NDI:somePerson), email this name to organization which invited you.<br>
If you are organization, use 'File - Verify message', insert message like 'dpo:NDI:somePerson:1' and sign it with address from your dpo name.
Email this Signature back to person.
Person now must use NAME_UPDATE with text Signature=XXX
)TXT"));
}
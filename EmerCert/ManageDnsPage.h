//ManageDnsPage.h by emercoin developers
#pragma once
#include <QDialog>
#include <QLineEdit>
class QLineEdit;
class QFormLayout;
class QString;

class ManageDnsPage: public QWidget {
    public:
	    ManageDnsPage(QWidget*parent=0);

        QLineEdit* _editName = 0;
        struct LineEdit: public QLineEdit {
            QString _dnsRecord;
        };
        QList<LineEdit*> _edits;

        QLineEdit* _resultingName = 0;
        QLineEdit* _resultingValue = 0;
    protected:
        void recalcValue();
        LineEdit* addLineEdit(QFormLayout*form, QString dnsParam, QString text, QString tooltipq);
};
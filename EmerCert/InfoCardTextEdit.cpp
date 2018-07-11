//InfoCardTextEdit.cpp by Emercoin developers
#include "pch.h"
#include "InfoCardTextEdit.h"
#include "InfoCardHighlighter.h"

InfoCardTextEdit::InfoCardTextEdit() {
	setWordWrapMode(QTextOption::NoWrap);
	new InfoCardHighlighter(document());

	auto completer = new QCompleter(this);
	QStringList keywords = QString("Import Alias FirstName LastName HomeAddress HomePhone CellPhone Gender Birthdate Email WEB Facebook Twitter EMC BTC").split(' ');
	qSort(keywords);
	auto model = new QStringListModel(keywords, this);
    completer->setModel(model);
    completer->setFilterMode(Qt::MatchContains);
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    //completer->setWrapAround(false);
    setCompleter(completer);
}
void InfoCardTextEdit::setCompleter(QCompleter *completer) {
    if (c)
        QObject::disconnect(c, 0, this, 0);
    c = completer;
    if (!c)
        return;

    c->setWidget(this);
    c->setCompletionMode(QCompleter::PopupCompletion);
    c->setCaseSensitivity(Qt::CaseInsensitive);
    connect(c, static_cast<void(QCompleter::*)(const QString&)>(&QCompleter::activated), this, &InfoCardTextEdit::insertCompletion);
}
QCompleter *InfoCardTextEdit::completer() const {
    return c;
}
void InfoCardTextEdit::insertCompletion(const QString& completion) {
    if (c->widget() != this)
        return;
    QTextCursor tc = textCursor();
	tc.select(QTextCursor::WordUnderCursor);
	tc.removeSelectedText();
	tc.insertText(completion);
}
QString InfoCardTextEdit::textUnderCursor()const {
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}
void InfoCardTextEdit::focusInEvent(QFocusEvent *e) {
    if (c)
        c->setWidget(this);
    QTextEdit::focusInEvent(e);
}
void InfoCardTextEdit::keyPressEvent(QKeyEvent *e) {
    if (c && c->popup()->isVisible()) {
        // The following keys are forwarded by the completer to the widget
       switch (e->key()) {
       case Qt::Key_Enter:
       case Qt::Key_Return:
       case Qt::Key_Escape:
       case Qt::Key_Tab:
       case Qt::Key_Backtab:
            e->ignore();
            return; // let the completer do default behavior
       default:
           break;
       }
    }

    bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_Space); // CTRL+Space
    if (!c || !isShortcut) // do not process the shortcut when we have a completer
        QTextEdit::keyPressEvent(e);

    const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if (!c || (ctrlOrShift && e->text().isEmpty()))
        return;

    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
    bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
    QString completionPrefix = textUnderCursor();

    //if (!isShortcut && (hasModifier || e->text().isEmpty()|| completionPrefix.length() < 3
    //                  || eow.contains(e->text().right(1)))) {
    //    c->popup()->hide();
    //    return;
    //}

    if (completionPrefix != c->completionPrefix()) {
        c->setCompletionPrefix(completionPrefix);
        c->popup()->setCurrentIndex(c->completionModel()->index(0, 0));
    }
    QRect cr = cursorRect();
    cr.setWidth(c->popup()->sizeHintForColumn(0)
                + c->popup()->verticalScrollBar()->sizeHint().width());
    c->complete(cr); // popup it up!
}
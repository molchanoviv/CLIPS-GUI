#include "consoleclass.h"

#include <QMimeData>

consoleClass::consoleClass(QWidget *parent) :
	QPlainTextEdit(parent)
{
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	connect(this, SIGNAL(enterPressed()), this, SLOT(exec()));
	prompt = ">";
	isLocked = false;
	isCommand = false;
	insertPrompt(false);
	history = new QStringList;
}

void consoleClass::exec()
{
	if(textCursor().positionInBlock() == prompt.length())
	{
		insertPrompt(true);
		return;
	}
	QTextCursor cursor = textCursor();
	cursor.movePosition(QTextCursor::End);
	setTextCursor(cursor);
	QString cmd = textCursor().block().text().mid(prompt.length()).simplified();
	isLocked = true;
	isCommand = true;
	historyAdd(cmd);
	emit execSignal(cmd);
}

void consoleClass::insertPrompt(bool insertNewBlock)
{
	if(insertNewBlock)
		textCursor().insertBlock();
	textCursor().insertText(prompt);
	position = textCursor().position();
	scrollDown();
}

void consoleClass::output(QString s)
{
	if(!isCommand)
	{
		if(s.isEmpty())
			return;
		else
		{
			emit outputSignal(s);
			return;
		}
	}
	if(s != "")
	{
		textCursor().insertBlock();
		textCursor().insertText(s);
	}
	insertPrompt(true);
	isLocked = false;
	isCommand = false;
	emit refreshAllSignal();
}

void consoleClass::historyAdd(QString cmd)
{
	history->append(cmd);
	historyPos = history->length();
}

void consoleClass::historyBack()
{
	if(history->isEmpty())
		return;
	if(!historyPos)
		return;
	QTextCursor cursor = textCursor();
	cursor.movePosition(QTextCursor::StartOfBlock);
	cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
	cursor.removeSelectedText();
	cursor.insertText(prompt + history->at(historyPos-1));
	setTextCursor(cursor);
	historyPos--;
}

void consoleClass::historyForward()
{
	if(history->isEmpty())
		return;
	if(historyPos == history->length())
		return;
	QTextCursor cursor = textCursor();
	cursor.movePosition(QTextCursor::StartOfBlock);
	cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
	cursor.removeSelectedText();
	if(historyPos == history->length() - 1)
		cursor.insertText(prompt);
	else
		cursor.insertText(prompt + history->at(historyPos + 1));
	setTextCursor(cursor);
	historyPos++;
}

void consoleClass::scrollDown()
{
	QScrollBar *vbar = verticalScrollBar();
	vbar->setValue(vbar->maximum());
}

void consoleClass::insertFromMimeData(const QMimeData* mimeData)
{
	if(textCursor().position() < position)
	{
		QTextCursor cursor = textCursor();
		cursor.movePosition(QTextCursor::End);
		setTextCursor(cursor);
	}
	if(mimeData->hasText())
		textCursor().insertText(mimeData->text().simplified());
}

void consoleClass::keyPressEvent( QKeyEvent * event )
{
	if(isLocked)
		return;
	if(event->key() == Qt::Key_Backspace)
	{
		if(textCursor().positionInBlock() > prompt.length())
			QPlainTextEdit::keyPressEvent(event);
		else if(textCursor().positionInBlock() == prompt.length())
		{
			if(this->textCursor().selection().isEmpty())
				event->ignore();
			else
				QPlainTextEdit::keyPressEvent(event);
		}
		else
			event->ignore();
	}
	else if(event->key() == Qt::Key_Return && event->modifiers() == Qt::NoModifier)
	{
		emit enterPressed();
		event->ignore();
	}
	else if(event->key() == Qt::Key_Enter && event->modifiers() == Qt::NoModifier)
	{
		emit enterPressed();
		event->ignore();
	}
	else if(event->key() == Qt::Key_Up)
		historyBack();
	else if(event->key() == Qt::Key_Down)
		historyForward();
	else if(event->key() == Qt::Key_Home)
	{
		QTextCursor cursor = textCursor();
		cursor.setPosition(position);
		setTextCursor(cursor);
	}
	else if(event->key() == Qt::Key_Left&& textCursor().positionInBlock() > prompt.length())
		QPlainTextEdit::keyPressEvent(event);
	else if(event->key() == Qt::Key_Right  && textCursor().positionInBlock() > prompt.length()-1)
		QPlainTextEdit::keyPressEvent(event);
	else if(	event->key() == Qt::Key_Backspace	||
			event->key() == Qt::Key_Return		||
			event->key() == Qt::Key_Enter		||
			event->key() == Qt::Key_Left		||
			event->key() == Qt::Key_Right		||
			event->key() == Qt::Key_PageDown	||
			event->key() == Qt::Key_PageUp)
		event->ignore();
	else
	{
		if(textCursor().positionInBlock() > prompt.length()-1)
			QPlainTextEdit::keyPressEvent(event);
	}
}

void consoleClass::mousePressEvent(QMouseEvent *event)
{
	setFocus();
//	QPlainTextEdit::mousePressEvent(event);
}


#include "consoleclass.h"

consoleClass::consoleClass(QWidget *parent) :
	QPlainTextEdit(parent)
{
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	connect(this, SIGNAL(enterPressed()), this, SLOT(exec()));
	prompt = ">";
	isLocked = false;
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
	QString cmd = textCursor().block().text().mid(prompt.length());
	isLocked = true;
	historyAdd(cmd);
	QRegExp command_split_rx("\\. ");
	QStringList commands = cmd.split(command_split_rx);
	QString str;
	foreach(str, commands)
	{
		/************************Создать*факт************************************/
		QRegExp assertStringCommandRx("(.*)(добавить|новый|создать)(.*)(факт) (.*)");
		int pos = assertStringCommandRx.indexIn(str.toLower());
		if (pos > -1)
		{
			QString fact = assertStringCommandRx.cap(5).simplified();
			emit assertStringSignal(fact, true);
		}
		/*************************Показать*все*факты*******************************/
		QRegExp factsCommandRx("(.*)(отобразить|показать|вывести)(.*)(факты)(.*)");
		if(str.contains(factsCommandRx))
		{
			emit factsSignal(1);
		}
		/*************************Удалить*факт*************************************/
		QRegExp retractCommandRx("(.*)(удалить|стереть)(.*)(факт) ([0-9]*)(.*)");
		pos = retractCommandRx.indexIn(str.toLower());
		if (pos > -1)
		{
			if(!retractCommandRx.cap(5).isEmpty())
			{
				int fact = retractCommandRx.cap(5).toInt();
				emit retractSignal(fact, true);
			}
			else
				output("");
		}
		/*************************Сохранить*факты*в*файл*****************************/
		QRegExp saveFactsCommandRx(".*(сохранить|записать).* в .* файл (.*)");
		pos = saveFactsCommandRx.indexIn(str.toLower());
		if (pos > -1)
		{
			QString fact = saveFactsCommandRx.cap(2);
			emit saveFactsSignal(fact);
		}
		/*************************Включить*дублирование*фактов***********************/
		QRegExp setFactDuplicationTrueRx(".*включить.* дублирование.*фактов.*");
		if(str.contains(setFactDuplicationTrueRx))
		{
			emit setFactDuplicationSignal(true, true);
		}
		/************************Выключить*дублирование*фактов***********************/
		QRegExp setFactDuplicationFalseRx(".*выключить.* дублирование.*фактов.*");
		if(str.contains(setFactDuplicationFalseRx))
		{
			emit setFactDuplicationSignal(false, true);
		}
		/************************Создать*проект**************************************/
		QRegExp createProjectRx(".*создать.* проект.*");
		if(str.contains(createProjectRx))
		{
			emit createProjectSignal();
			output("");
		}
	}
	//output("");
}

void consoleClass::insertPrompt(bool insertNewBlock)
{
	if(insertNewBlock)
		textCursor().insertBlock();
	textCursor().insertText(prompt);
	scrollDown();
}

void consoleClass::output(QString s)
{
	if(s != "")
	{
		textCursor().insertBlock();
		textCursor().insertText(s);
	}
	insertPrompt(true);
	isLocked = false;
}

void consoleClass::historyAdd(QString cmd)
{
	history->append(cmd);
	historyPos = history->length();
}

void consoleClass::historyBack()
{
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
		emit enterPressed();
	else if(event->key() == Qt::Key_Enter && event->modifiers() == Qt::NoModifier)
		emit enterPressed();
	else if(event->key() == Qt::Key_Up)
		historyBack();
	else if(event->key() == Qt::Key_Down)
		historyForward();
	else if(event->key() == Qt::Key_Home)
	{
		QTextCursor cursor = textCursor();
		cursor.setPosition(prompt.length());
		setTextCursor(cursor);
	}
	else if(event->key() == Qt::Key_Left&& textCursor().positionInBlock() > prompt.length())
		QPlainTextEdit::keyPressEvent(event);
	else if(event->key() == Qt::Key_Right  && textCursor().positionInBlock() > prompt.length()-1)
		QPlainTextEdit::keyPressEvent(event);
	else if(event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter || event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
		event->ignore();
	else
	{
		if(textCursor().positionInBlock() > prompt.length()-1)
			QPlainTextEdit::keyPressEvent(event);
	}
}

void consoleClass::mousePressEvent(QMouseEvent *)
{
	setFocus();
}
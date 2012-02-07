#ifndef CONSOLECLASS_H
#define CONSOLECLASS_H

#include <QPlainTextEdit>
#include <QTextBlock>
#include <QKeyEvent>
#include <QDebug>
#include <QRegExp>
#include <QString>
#include <QStringList>
#include <QScrollBar>
#include <QTextDocumentFragment>
#include <QTextCodec>

class consoleClass : public QPlainTextEdit
{
	Q_OBJECT
public:
	explicit consoleClass(QWidget *parent = 0);

signals:
	void enterPressed();
	void execSignal(QString);
	void refreshAllSignal();
	void outputSignal(QString);

public slots:
	void exec();
	void output(QString);


protected:
	void keyPressEvent(QKeyEvent *);
	void mousePressEvent(QMouseEvent *);
	void mouseDoubleClickEvent(QMouseEvent *){};
	void insertPrompt(bool);
	bool isLocked;
	bool isCommand;
	QStringList *history;
	int historyPos;
	void historyAdd(QString);
	void historyBack();
	void historyForward();
	void scrollDown();
	virtual void insertFromMimeData (const QMimeData*);

private:
	QString prompt;

};

#endif // CONSOLECLASS_H

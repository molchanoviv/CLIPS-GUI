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
	void assertStringSignal(QString, bool);
	void factsSignal(bool);
	void retractSignal(int, bool);
	void saveFactsSignal(QString);
	void setFactDuplicationSignal(bool, bool);
	void createProjectSignal();
	void openProjectSignal();
	void quitSignal();

public slots:
	void exec();
	void output(QString);

protected:
	void keyPressEvent(QKeyEvent *);
	void mousePressEvent(QMouseEvent *);
	void insertPrompt(bool);
	bool isLocked;
	QStringList *history;
	int historyPos;
	void historyAdd(QString);
	void historyBack();
	void historyForward();
	void scrollDown();

private:
	QString prompt;

};

#endif // CONSOLECLASS_H

#ifndef ADDMESSAGEHANDLERDIALOG_H
#define ADDMESSAGEHANDLERDIALOG_H

#include "ui_addmessagehandlerdialog.h"

#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QStringList>

class addMessageHandlerDialog : public QDialog, private Ui::addMessageHandlerDialog
{
	Q_OBJECT
	
public:
	explicit addMessageHandlerDialog(QWidget *parent = 0, QStringList classesList = QStringList(), QStringList handlerTypeList = QStringList());
	QComboBox *classNameComboBox;
	QLineEdit *messageNameLineEdit;
	QComboBox *handlerTypeComboBox;
	QLineEdit *commentLineEdit;
	QLineEdit *parameterLineEdit;
	QLineEdit *wildcardParameterLineEdit;
	QTextEdit *actionTextEdit;

};

#endif // ADDMESSAGEHANDLERDIALOG_H

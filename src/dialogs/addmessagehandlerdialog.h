#ifndef ADDMESSAGEHANDLERDIALOG_H
#define ADDMESSAGEHANDLERDIALOG_H

#include "ui_addmessagehandlerdialog.h"

class QStringList;
class QComboBox;
class QLineEdit;
class QTextEdit;

class addMessageHandlerDialog : public QDialog, private Ui::addMessageHandlerDialog
{
	Q_OBJECT
	
public:
	explicit addMessageHandlerDialog(QWidget *parent = 0, QStringList classesList = QStringList(), QStringList handlerTypeList = QStringList());
	~addMessageHandlerDialog();
	QComboBox *classNameComboBox;
	QLineEdit *messageNameLineEdit;
//	QComboBox *handlerTypeComboBox;
//	QLineEdit *commentLineEdit;
//	QLineEdit *parameterLineEdit;
//	QLineEdit *wildcardParameter;
//	QTextEdit *actionTextEdit;

};

#endif // ADDMESSAGEHANDLERDIALOG_H

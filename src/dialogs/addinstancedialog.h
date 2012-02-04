#ifndef ADDINSTANCEDIALOG_H
#define ADDINSTANCEDIALOG_H

#include "ui_addinstancedialog.h"

#include <QLineEdit>
#include <QCheckBox>

class addInstanceDialog : public QDialog, private Ui::addInstanceDialog
{
	Q_OBJECT
	
public:
	explicit addInstanceDialog(QWidget *parent = 0);
	QLineEdit *nameLineEdit;
	QCheckBox *activeCheckBox;
	QLineEdit *commentLineEdit;
	QLineEdit *instanceTemplateLineEdit;
};

#endif // ADDINSTANCEDIALOG_H

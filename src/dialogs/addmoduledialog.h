#ifndef ADDMODULEDIALOG_H
#define ADDMODULEDIALOG_H

#include "ui_addmoduledialog.h"

#include <QLineEdit>

class addModuleDialog : public QDialog, private Ui::addModuleDialog
{
	Q_OBJECT
	
public:
	explicit addModuleDialog(QWidget *parent = 0);
	QLineEdit *nameLineEdit;
	QLineEdit *commentLineEdit;
	QLineEdit *specificationLineEdit;
};

#endif // ADDMODULEDIALOG_H

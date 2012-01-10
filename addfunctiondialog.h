#ifndef ADDFUNCTIONDIALOG_H
#define ADDFUNCTIONDIALOG_H

#include "ui_addfunctiondialog.h"

class addFunctionDialog : public QDialog, public Ui::addFunctionDialog
{
	Q_OBJECT
	
public:
	explicit addFunctionDialog(QWidget *parent = 0);
	
protected:
	void changeEvent(QEvent *e);
};

#endif // ADDFUNCTIONDIALOG_H

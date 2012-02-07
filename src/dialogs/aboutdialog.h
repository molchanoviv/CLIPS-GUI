#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include "ui_aboutdialog.h"

class aboutDialog : public QDialog, private Ui::aboutDialog
{
	Q_OBJECT
	
public:
	explicit aboutDialog(QWidget *parent = 0);
	
protected:
	void changeEvent(QEvent *e);
};

#endif // ABOUTDIALOG_H

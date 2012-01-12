#ifndef ADDDEFFACTSDIALOG_H
#define ADDDEFFACTSDIALOG_H

#include "ui_adddeffactsdialog.h"

class addDeffactsDialog : public QDialog, private Ui::addDeffactsDialog
{
	Q_OBJECT
	
public:
	explicit addDeffactsDialog(QWidget *parent = 0, int factsCount = 1);
	QList<QLineEdit *> lineEditList;
	QLineEdit *nameLineEdit;
};

#endif // ADDDEFFACTSDIALOG_H

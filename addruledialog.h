#ifndef ADDRULEDIALOG_H
#define ADDRULEDIALOG_H

#include "ui_addruledialog.h"

class QLineEdit;

class addRuleDialog : public QDialog, private Ui::addRuleDialog
{
	Q_OBJECT
	
public:
	explicit addRuleDialog(QWidget *parent = 0, int antecedensCount =1, int consequentsCount=1);
	QList<QLineEdit *> antecedentsLineEditList;
	QList<QLineEdit *> consequentsLineEditList;
	QLineEdit *nameLineEdit;
	QLineEdit *commentLineEdit;
	QLineEdit *declarationLineEdit;
};

#endif // ADDRULEDIALOG_H

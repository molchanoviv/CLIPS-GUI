#include "addfunctiondialog.h"

addFunctionDialog::addFunctionDialog(QWidget *parent) :
	QDialog(parent)
{
	setupUi(this);
}

void addFunctionDialog::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type()) {
		case QEvent::LanguageChange:
			retranslateUi(this);
			break;
		default:
			break;
	}
}

#include "aboutdialog.h"

aboutDialog::aboutDialog(QWidget *parent) :
	QDialog(parent)
{
	setupUi(this);
}

void aboutDialog::changeEvent(QEvent *e)
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

#include "addfactbytemplatedialog.h"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRegExpValidator>

addFactByTemplateDialog::addFactByTemplateDialog(QWidget *parent, QList<slotsPair> *slotsList) :
	QDialog(parent)
{
	setupUi(this);
	if(slotsList->isEmpty())
		return;
	QRegExp rx("\\S*");
	QValidator *validator = new QRegExpValidator(rx, this);
	QGridLayout *mainLayout = new QGridLayout;
	int i=0;
	for(i ;i<slotsList->count(); i++)
	{
		QLineEdit *lineEdit = new QLineEdit;
		QString mltSltLbl = "";
		if(!slotsList->at(i).first)
		{
			mltSltLbl = "slot";
			lineEdit->setValidator(validator);
		}
		else
			mltSltLbl = "multislot";
		QLabel *label = new QLabel(slotsList->at(i).second+"("+mltSltLbl+"): ");
		mainLayout->addWidget(label, i, 1);
		mainLayout->addWidget(lineEdit, i, 2);
		lineEditList.append(lineEdit);
	}
	mainLayout->addWidget(buttonBox, i+1, 1, i+1, 2);
	setLayout(mainLayout);
}

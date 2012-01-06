#include "adddeffactsdialog.h"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

addDeffactsDialog::addDeffactsDialog(QWidget *parent, int factsCount) :
	QDialog(parent)
{
	setupUi(this);
	QGridLayout *mainLayout = new QGridLayout;
	QLabel *nameLabel = new QLabel("Name: ");
	nameLineEdit = new QLineEdit;
	mainLayout->addWidget(nameLabel, 0, 1);
	mainLayout->addWidget(nameLineEdit, 0, 2);
	int i=0;
	for(i; i<factsCount;i++)
	{
		QLabel *label = new QLabel;
		label->setText(QString("Fact ")+QString::number(i+1)+QString(": "));
		QLineEdit *lineEdit = new QLineEdit;
		lineEditList.append(lineEdit);
		mainLayout->addWidget(label, i+1, 1);
		mainLayout->addWidget(lineEdit, i+1, 2);
	}
	mainLayout->addWidget(buttonBox, i+2, 1, i+2, 2);
	setLayout(mainLayout);
}

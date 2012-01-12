#include "addtemplatedialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>
#include <QCheckBox>

addTemplateDialog::addTemplateDialog(QWidget *parent, int slotsCount) :
	QDialog(parent)
{
	setupUi(this);
	QVBoxLayout *mainLayout = new QVBoxLayout;
	QLabel *nameLabel = new QLabel;
	nameLabel->setText("Template name:");
	nameLineEdit = new QLineEdit;
	QHBoxLayout *nameHorizontalLayout = new QHBoxLayout;
	nameHorizontalLayout->addWidget(nameLabel);
	nameHorizontalLayout->addWidget(nameLineEdit);
	mainLayout->addLayout(nameHorizontalLayout);
	for(int i=0; i<slotsCount;i++)
	{
		QCheckBox *box = new QCheckBox;
		box->setText("Multislot");
		QLineEdit *lineEdit = new QLineEdit;
		QLabel *label = new QLabel;
		label->setText("Slot name:");
		QHBoxLayout *layout = new QHBoxLayout;
		layout->addWidget(label);
		layout->addWidget(lineEdit);
		layout->addWidget(box);
		mainLayout->addLayout(layout);
		checkBoxList.append(box);
		lineEditList.append(lineEdit);
	}



	mainLayout->addWidget(buttonBox);
	setLayout(mainLayout);
}

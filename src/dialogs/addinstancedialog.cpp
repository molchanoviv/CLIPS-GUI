#include "addinstancedialog.h"

#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>

addInstanceDialog::addInstanceDialog(QWidget *parent) :
	QDialog(parent)
{
	setupUi(this);
	QGridLayout *mainLayout = new QGridLayout;
	QLabel *nameLabel = new QLabel(tr("Name: "));
	nameLineEdit = new QLineEdit;
	QLabel *activeLabel = new QLabel(tr("Active: "));
	activeCheckBox = new QCheckBox;
	QLabel *commentLabel = new QLabel(tr("Comment(not necessarily): "));
	commentLineEdit = new QLineEdit;
	QLabel *instanceTemplateLabel = new QLabel(tr("Instance Template"));
	instanceTemplateLineEdit = new QLineEdit;
	mainLayout->addWidget(nameLabel, 1, 1);
	mainLayout->addWidget(nameLineEdit, 1, 2);
	mainLayout->addWidget(activeLabel, 2, 1);
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addStretch();
	layout->addWidget(activeCheckBox);
	mainLayout->addLayout(layout, 2, 2);
	mainLayout->addWidget(commentLabel, 3, 1);
	mainLayout->addWidget(commentLineEdit, 3, 2);
	mainLayout->addWidget(instanceTemplateLabel, 4, 1);
	mainLayout->addWidget(instanceTemplateLineEdit, 4, 2);
	mainLayout->addWidget(buttonBox, 5, 1, 5, 2);
	setLayout(mainLayout);
}

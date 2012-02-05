#include "addmoduledialog.h"

#include <QLabel>
#include <QGridLayout>

addModuleDialog::addModuleDialog(QWidget *parent) :
	QDialog(parent)
{
	setupUi(this);
	QGridLayout *mainLayout = new QGridLayout;
	QLabel *nameLabel = new QLabel(tr("Name: "));
	nameLineEdit = new QLineEdit;
	QLabel *commentLabel = new QLabel(tr("Comment(not necessarily): "));
	commentLineEdit = new QLineEdit;
	QLabel *specificationLabel = new QLabel(tr("Port Specification: "));
	specificationLineEdit = new QLineEdit;
	mainLayout->addWidget(nameLabel, 1, 1);
	mainLayout->addWidget(nameLineEdit, 1, 2);
	mainLayout->addWidget(commentLabel, 2, 1);
	mainLayout->addWidget(commentLineEdit, 2, 2);
	mainLayout->addWidget(specificationLabel, 3, 1);
	mainLayout->addWidget(specificationLineEdit, 3, 2);
	mainLayout->addWidget(buttonBox, 4, 1, 4, 2);
	setLayout(mainLayout);
}

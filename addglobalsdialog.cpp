#include "addglobalsdialog.h"
#include <QComboBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

addGlobalsDialog::addGlobalsDialog(QWidget *parent, int variablesCount, QStringList modules) :
	QDialog(parent)
{
	setupUi(this);
	if(modules.isEmpty())
		return;
	QVBoxLayout *mainLayout = new QVBoxLayout;
	QHBoxLayout *topLayout = new QHBoxLayout;
	QGridLayout *gridLayout = new QGridLayout;
	modulesComboBox = new QComboBox;
	modulesComboBox->addItems(modules);
	QLabel *modulesLabel = new QLabel(tr("Module: "));
	topLayout->addWidget(modulesLabel);
	topLayout->addWidget(modulesComboBox);
	for(int i=0; i<variablesCount; i++)
	{
		QString lblNm = QString(tr("Assignment "))+QString::number(i+1)+QString(tr(": "));
		QLabel *label = new QLabel(lblNm);
		QLineEdit *variableLineEdit = new QLineEdit;
		QLabel *sLabel = new QLabel(tr("="));
		QLineEdit *expressionLineEdit = new QLineEdit;
		gridLayout->addWidget(label, i, 1);
		gridLayout->addWidget(variableLineEdit, i, 2);
		gridLayout->addWidget(sLabel, i, 3);
		gridLayout->addWidget(expressionLineEdit, i, 4);
		lineEditsPair pair(variableLineEdit, expressionLineEdit);
		assignmentsLineEditsList.append(pair);
	}
	mainLayout->addLayout(topLayout);
	mainLayout->addLayout(gridLayout);
	mainLayout->addWidget(buttonBox);
	setLayout(mainLayout);
}

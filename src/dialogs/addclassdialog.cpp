#include "addclassdialog.h"
#include <QStringList>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>

addClassDialog::addClassDialog(QWidget *parent, int parentsCount, int slotsCount, int handlersCount, QStringList classesList) :
	QDialog(parent)
{
	setupUi(this);
	QVBoxLayout *mainLayout = new QVBoxLayout;
	QGridLayout *topLayout = new QGridLayout;
	topLayout->addWidget(nameLabel, 1, 1);
	topLayout->addWidget(nameLineEdit, 1, 2);
	topLayout->addWidget(commentLabel, 2, 1);
	topLayout->addWidget(commentLineEdit, 2, 2);
	QGridLayout *middleLayout = new QGridLayout;
	for(int i=0; i<parentsCount; i++)
	{
		QLabel *label = new QLabel(tr("Parent %1:").arg(QString::number(i+1)));
		QComboBox *comboBox = new QComboBox;
		comboBox->addItems(classesList);
		int index=0;
		for(int i=0; i<classesList.count(); i++)
		{
			if(classesList.at(i)=="OBJECT")
				index=i;
		}
		comboBox->setCurrentIndex(index);
		isAList.append(comboBox);
		middleLayout->addWidget(label, i, 1);
		middleLayout->addWidget(comboBox, i, 2);
	}
	QGridLayout *bottomLayout = new QGridLayout;
	roleComboBox->addItems(QStringList()<<"abstract"<<"concrete");
	bottomLayout->addWidget(roleLabel, 1, 1);
	bottomLayout->addWidget(roleComboBox, 1, 2);
	patternMatchRoleComboBox->addItems(QStringList()<<"non-reactive"<<"reactive");
	bottomLayout->addWidget(patternMatchRoleLabel, 2, 1);
	bottomLayout->addWidget(patternMatchRoleComboBox, 2, 2);
	mainLayout->addLayout(topLayout);
	mainLayout->addLayout(middleLayout);
	mainLayout->addLayout(bottomLayout);
	for(int i=0; i<slotsCount; i++)
	{
		QGridLayout *layout = new QGridLayout;
		QLabel *slotLabel = new QLabel(tr("Slot %1:").arg(i+1));
		QLineEdit *slotLineEdit = new QLineEdit;
		slotsList.append(slotLineEdit);
		layout->addWidget(slotLabel, 1, 1);
		layout->addWidget(slotLineEdit, 1, 2);
		mainLayout->addLayout(layout);
	}
	for(int i=0; i<handlersCount; i++)
	{
		QGridLayout *layout = new QGridLayout;
		QLabel *handlerDocumentationLabel = new QLabel(tr("Handler documentation %1:").arg(i+1));
		QLineEdit *handlerDocumentationLineEdit = new QLineEdit;
		handlerDocumentationList.append(handlerDocumentationLineEdit);
		layout->addWidget(handlerDocumentationLabel, 1, 1);
		layout->addWidget(handlerDocumentationLineEdit, 1, 2);
		mainLayout->addLayout(layout);
	}
	mainLayout->addWidget(buttonBox);
	setLayout(mainLayout);
}


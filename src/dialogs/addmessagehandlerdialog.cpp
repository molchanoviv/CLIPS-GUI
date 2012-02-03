#include "addmessagehandlerdialog.h"
#include <QLabel>
#include <QGridLayout>


addMessageHandlerDialog::addMessageHandlerDialog(QWidget *parent, QStringList classesList, QStringList handlerTypeList) :
	QDialog(parent)
{
	setupUi(this);
	QGridLayout *mainLayout = new QGridLayout;
	QLabel *classNameLabel = new QLabel(tr("Class Name: "));
	classNameComboBox = new QComboBox();
	classNameComboBox->addItems(classesList);
	QLabel *messageNameLabel = new QLabel(tr("Message Name: "));
	messageNameLineEdit = new QLineEdit;
	QLabel *handlerTypeLabel = new QLabel(tr("Handler Type: "));
	handlerTypeComboBox = new QComboBox();
	handlerTypeComboBox->addItems(handlerTypeList);
	QLabel *commentLabel = new QLabel(tr("Comment(not necessarily): "));
	commentLineEdit = new QLineEdit;
	QLabel *parameterLabel = new QLabel(tr("Parameter: "));
	parameterLineEdit = new QLineEdit;
	QLabel *wildcardParameterLabel = new QLabel(tr("Wildcard Parameter(not necessarily): "));
	wildcardParameterLineEdit = new QLineEdit;
	QLabel *actionLabel = new QLabel(tr("Action: "));
	actionTextEdit = new QTextEdit;
	mainLayout->addWidget(classNameLabel, 1, 1);
	mainLayout->addWidget(classNameComboBox, 1, 2);
	mainLayout->addWidget(messageNameLabel, 2, 1);
	mainLayout->addWidget(messageNameLineEdit, 2, 2);
	mainLayout->addWidget(handlerTypeLabel, 3, 1);
	mainLayout->addWidget(handlerTypeComboBox, 3, 2);
	mainLayout->addWidget(commentLabel, 4, 1);
	mainLayout->addWidget(commentLineEdit, 4, 2);
	mainLayout->addWidget(parameterLabel, 5, 1);
	mainLayout->addWidget(parameterLineEdit, 5, 2);
	mainLayout->addWidget(wildcardParameterLabel, 6, 1);
	mainLayout->addWidget(wildcardParameterLineEdit, 6, 2);
	mainLayout->addWidget(actionLabel, 7, 1);
	mainLayout->addWidget(actionTextEdit, 7, 2);
	mainLayout->addWidget(buttonBox, 8, 1, 8, 2);
	setLayout(mainLayout);
}


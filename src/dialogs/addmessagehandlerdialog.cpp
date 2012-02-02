#include "addmessagehandlerdialog.h"
#include <QStringList>;
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QTextEdit>

addMessageHandlerDialog::addMessageHandlerDialog(QWidget *parent, QStringList classesList, QStringList handlerTypeList) :
	QDialog(parent)
{
	setupUi(this);
	QGridLayout *mainLayout = new QGridLayout;
	QLabel *classNameLabel = new QLabel(tr("Class Name: "));
	classNameComboBox = new QComboBox;
	classNameComboBox->addItems(classesList);
	QLabel *messageNameLabel = new QLabel(tr("Message Name: "));
	messageNameLineEdit = new QLineEdit;
//	QLabel *handlerTypeLabel = new QLabel(tr("Handler Type: "));
//	handlerTypeComboBox = new QComboBox;
//	QLabel *commentLabel = new QLabel(tr("Comment(not necessarily): "));
//	commentLineEdit = new QLineEdit;
//	QLabel *parameterLabel = new QLabel(tr("Parameter: "));
//	parameterLineEdit = new QLineEdit;
//	QLabel *wildcardParameterLabel = new QLabel(tr("Wildcard Parameter(not necessarily): "));
//	wildcardParameter = new QLineEdit;
//	QLabel *ActionLabel = new QLabel(tr("Action: "));
//	actionTextEdit = new QTextEdit;
	mainLayout->addWidget(classNameLabel, 1, 1);
	mainLayout->addWidget(classNameComboBox, 1, 2);
	mainLayout->addWidget(messageNameLabel, 2, 1);
	mainLayout->addWidget(messageNameLineEdit, 2, 2);
//	mainLayout->addWidget(commentLabel, 3, 1);
//	mainLayout->addWidget(commentLineEdit, 3, 2);
	setLayout(mainLayout);
}

addMessageHandlerDialog::~addMessageHandlerDialog()
{
//	delete classNameComboBox;
//	delete messageNameLineEdit;
//	delete handlerTypeComboBox;
//	delete commentLineEdit;
//	delete parameterLineEdit;
//	delete wildcardParameter;
//	delete actionTextEdit;
}

#include "addruledialog.h"
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>

addRuleDialog::addRuleDialog(QWidget *parent, int antecedensCount, int consequentsCount) :
	QDialog(parent)
{
	setupUi(this);
	QVBoxLayout *mainLayout = new QVBoxLayout;
	QGridLayout *topGridLayout = new QGridLayout;
	QLabel *nameLabel = new QLabel(tr("Rule name: "));
	nameLineEdit = new QLineEdit;
	QLabel *commentLabel = new QLabel(tr("Comment (not necessarily):"));
	commentLineEdit = new QLineEdit;
	QLabel *declarationLabel = new QLabel(tr("Declaration (not necessarily): "));
	declarationLineEdit = new QLineEdit;
	QGridLayout *antecedensLayout = new QGridLayout;
	for(int i=0; i<antecedensCount; i++)
	{
		QString lbl = tr("Antecedent ")+QString::number(i+1)+tr("(LHS-pattern): ");
		QLabel *label = new QLabel(lbl);
		QLineEdit *lineEdit = new QLineEdit;
		antecedentsLineEditList.append(lineEdit);
		antecedensLayout->addWidget(label, i+1, 1);
		antecedensLayout->addWidget(lineEdit, i+1, 2);
	}
	QGridLayout *consequentsLayout = new QGridLayout;
	for(int i=0; i<consequentsCount; i++)
	{
		QString lbl = tr("Consequent ")+QString::number(i+1)+tr("(RHS-pattern): ");
		QLabel *label = new QLabel(lbl);
		QLineEdit *lineEdit = new QLineEdit;
		consequentsLineEditList.append(lineEdit);
		consequentsLayout->addWidget(label, i+1, 1);
		consequentsLayout->addWidget(lineEdit, i+1, 2);
	}
	QGroupBox *antecedentsGroupBox = new QGroupBox(tr("Antecedents"));
	antecedentsGroupBox->setLayout(antecedensLayout);
	QGroupBox *consequentsGroupBox = new QGroupBox(tr("Consequents"));
	consequentsGroupBox->setLayout(consequentsLayout);
	topGridLayout->addWidget(nameLabel, 1, 1);
	topGridLayout->addWidget(nameLineEdit, 1, 2);
	topGridLayout->addWidget(commentLabel, 2, 1);
	topGridLayout->addWidget(commentLineEdit, 2, 2);
	topGridLayout->addWidget(declarationLabel, 3, 1);
	topGridLayout->addWidget(declarationLineEdit, 3, 2);
	mainLayout->addLayout(topGridLayout);
	mainLayout->addWidget(antecedentsGroupBox);
	mainLayout->addWidget(consequentsGroupBox);
	mainLayout->addWidget(buttonBox);
	setLayout(mainLayout);
}

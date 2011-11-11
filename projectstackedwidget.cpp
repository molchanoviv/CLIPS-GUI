#include "projectstackedwidget.h"
#include <QInputDialog>
#include <QListWidgetItem>

ProjectStackedWidget::ProjectStackedWidget(QWidget *parent) :
	QStackedWidget(parent)
{
	/**************************Templates***************************************/
	QGroupBox *templatesWidget = new QGroupBox(tr("Templates"));
	QVBoxLayout *templatesLayout = new QVBoxLayout;
	QPushButton *button = new QPushButton(tr("..."));
	QHBoxLayout *templatesTopLayout = new QHBoxLayout;
	templatesTopLayout->addWidget(button);
	templatesTopLayout->addStretch();
	templatesListWidget = new QListWidget;
	QPushButton *addTemplateButton = new QPushButton(tr("Add Template"));
	QPushButton *removeTemplateButton = new QPushButton(tr("Remove Template"));
	QHBoxLayout *templatesBottomLayout = new QHBoxLayout;
	templatesBottomLayout->addStretch();
	templatesBottomLayout->addWidget(addTemplateButton);
	templatesBottomLayout->addWidget(removeTemplateButton);
	templatesLayout->addLayout(templatesTopLayout);
	templatesLayout->addWidget(templatesListWidget);
	templatesLayout->addLayout(templatesBottomLayout);
	templatesWidget->setLayout(templatesLayout);
	/*****************************Facts****************************************/
	QGroupBox *factsWidget = new QGroupBox(tr("Facts"));
	QVBoxLayout *factsLayout = new QVBoxLayout;
	QPushButton *duplicationButton = new QPushButton(tr("Enable Duplication"));
	duplicationButton->setCheckable(true);
	QHBoxLayout *factsTopLayout = new QHBoxLayout;
	factsTopLayout->addWidget(duplicationButton);
	factsTopLayout->addStretch();
	factsListWidget = new QListWidget;
	QPushButton *addFactButton = new QPushButton(tr("Add Fact"));
	QPushButton *removeFactButton = new QPushButton(tr("Remove Fact"));
	QHBoxLayout *factsBottomLayout = new QHBoxLayout;
	factsBottomLayout->addStretch();
	factsBottomLayout->addWidget(addFactButton);
	factsBottomLayout->addWidget(removeFactButton);
	factsLayout->addLayout(factsTopLayout);
	factsLayout->addWidget(factsListWidget);
	factsLayout->addLayout(factsBottomLayout);
	factsWidget->setLayout(factsLayout);
	connect(addFactButton, SIGNAL(clicked()), this, SLOT(addFactSlot()));
	/*****************************Rules****************************************/
	QGroupBox *rulesWidget = new QGroupBox(tr("Rules"));
	QVBoxLayout *rulesLayout = new QVBoxLayout;
	QPushButton *ruleButton = new QPushButton(tr("..."));
	QHBoxLayout *rulesTopLayout = new QHBoxLayout;
	rulesTopLayout->addWidget(ruleButton);
	rulesTopLayout->addStretch();
	rulesListWidget = new QListWidget;
	QPushButton *addRuleButton = new QPushButton(tr("Add Rule"));
	QPushButton *removeRuleButton = new QPushButton(tr("Remove Rule"));
	QHBoxLayout *rulesBottomLayout = new QHBoxLayout;
	rulesBottomLayout->addStretch();
	rulesBottomLayout->addWidget(addRuleButton);
	rulesBottomLayout->addWidget(removeRuleButton);
	rulesLayout->addLayout(rulesTopLayout);
	rulesLayout->addWidget(rulesListWidget);
	rulesLayout->addLayout(rulesBottomLayout);
	rulesWidget->setLayout(rulesLayout);
	/*****************************Functions************************************/
	QGroupBox *functionsWidget = new QGroupBox(tr("Functions"));
	QVBoxLayout *functionsLayout = new QVBoxLayout;
	QPushButton *functionButton = new QPushButton(tr("..."));
	QHBoxLayout *functionsTopLayout = new QHBoxLayout;
	functionsTopLayout->addWidget(functionButton);
	functionsTopLayout->addStretch();
	functionsListWidget = new QListWidget;
	QPushButton *addFunctionButton = new QPushButton(tr("Add Function"));
	QPushButton *removeFunctionButton = new QPushButton(tr("Remove Function"));
	QHBoxLayout *functionsBottomLayout = new QHBoxLayout;
	functionsBottomLayout->addStretch();
	functionsBottomLayout->addWidget(addFunctionButton);
	functionsBottomLayout->addWidget(removeFunctionButton);
	functionsLayout->addLayout(functionsTopLayout);
	functionsLayout->addWidget(functionsListWidget);
	functionsLayout->addLayout(functionsBottomLayout);
	functionsWidget->setLayout(functionsLayout);
	/*****************************Classes**************************************/
	QGroupBox *classesWidget = new QGroupBox(tr("Classes"));
	QVBoxLayout *classesLayout = new QVBoxLayout;
	QPushButton *classButton = new QPushButton(tr("..."));
	QHBoxLayout *classesTopLayout = new QHBoxLayout;
	classesTopLayout->addWidget(classButton);
	classesTopLayout->addStretch();
	classesListWidget = new QListWidget;
	QPushButton *addClassButton = new QPushButton(tr("Add Class"));
	QPushButton *removeClassButton = new QPushButton(tr("Remove Class"));
	QHBoxLayout *classesBottomLayout = new QHBoxLayout;
	classesBottomLayout->addStretch();
	classesBottomLayout->addWidget(addClassButton);
	classesBottomLayout->addWidget(removeClassButton);
	classesLayout->addLayout(classesTopLayout);
	classesLayout->addWidget(classesListWidget);
	classesLayout->addLayout(classesBottomLayout);
	classesWidget->setLayout(classesLayout);

	this->addWidget(templatesWidget);
	this->addWidget(factsWidget);
	this->addWidget(rulesWidget);
	this->addWidget(functionsWidget);
	this->addWidget(classesWidget);

	connect(duplicationButton, SIGNAL(toggled(bool)), this, SLOT(duplicationProxySlot(bool)));
	connect(removeFactButton, SIGNAL(clicked()), this, SLOT(removeFactSlot()));
}


void ProjectStackedWidget::addFactSlot()
{
	bool ok;
	QString text = QInputDialog::getText(this, tr("Add Fact"),
						tr("Fact name:"), QLineEdit::Normal,
						tr("Fact"), &ok);
	if (ok && !text.isEmpty())
		emit addFactSignal(text, false);
}

void ProjectStackedWidget::removeFactSlot()
{
	QList<QListWidgetItem*> facts = factsListWidget->selectedItems();
	if(!facts.isEmpty())
		emit removeFactSignal(facts.at(0)->data(Qt::UserRole).toInt(), false);
}

void ProjectStackedWidget::refreshFacts(QString facts)
{
	factsListWidget->clear();
	QStringList list = facts.split("\n");
	list.removeLast();
	QString str;
	foreach(str, list)
	{
		QStringList fact;
		fact = str.split(" ", QString::SkipEmptyParts);
		QString num = fact.at(0);
		int index = num.remove(0, 2).toInt();
		QString name = fact.at(1);
		QListWidgetItem *item = new QListWidgetItem(factsListWidget);
		item->setData(Qt::UserRole, index);
		item->setText(name);
	}
}

void ProjectStackedWidget::duplicationProxySlot(bool state)
{
	emit setFactDuplicationSignal(state, false);
}

void ProjectStackedWidget::clearSlot()
{
	templatesListWidget->clear();
	factsListWidget->clear();
	rulesListWidget->clear();
	functionsListWidget->clear();
	classesListWidget->clear();
}

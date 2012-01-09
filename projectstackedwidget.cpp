#include "projectstackedwidget.h"
#include <QListWidgetItem>
#include <QList>
#include <QDebug>
#include <QRegExp>

ProjectStackedWidget::ProjectStackedWidget(QWidget *parent) :
	QStackedWidget(parent)
{
	/**************************Templates***************************************/
	QGroupBox *templatesWidget = new QGroupBox(tr("Templates"));
	QVBoxLayout *templatesLayout = new QVBoxLayout;
	templatesListWidget = new QListWidget;
	addTemplateButton = new QPushButton(tr("Add"));
	addTemplateButton->setIcon(QIcon::fromTheme("list-add"));
	refreshTemplatesButton = new QPushButton(tr("Refresh"));
	refreshTemplatesButton->setIcon(QIcon::fromTheme("view-refresh"));
	QPushButton *removeTemplateButton = new QPushButton(tr("Remove"));
	removeTemplateButton->setIcon(QIcon::fromTheme("list-remove"));
	QHBoxLayout *templatesTopLayout = new QHBoxLayout;
	templatesTopLayout->addWidget(addTemplateButton);
	templatesTopLayout->addWidget(removeTemplateButton);
	templatesTopLayout->addWidget(refreshTemplatesButton);
	templatesTopLayout->addStretch();
	templatesLayout->addLayout(templatesTopLayout);
	templatesLayout->addWidget(templatesListWidget);
	templatesWidget->setLayout(templatesLayout);
	/*****************************Facts****************************************/
	QGroupBox *factsWidget = new QGroupBox(tr("Facts"));
	QVBoxLayout *factsLayout = new QVBoxLayout;
	QPushButton *duplicationButton = new QPushButton(tr("Enable Duplication"));
	duplicationButton->setCheckable(true);
	duplicationButton->setIcon(QIcon::fromTheme("edit-copy"));
	factsListWidget = new QListWidget;
	addFactButton = new QPushButton(tr("Add"));
	addFactButton->setIcon(QIcon::fromTheme("list-add"));
	addFactByTemplateButton = new QPushButton(tr("Add By Template"));
	addFactByTemplateButton->setIcon(QIcon::fromTheme("list-add"));
	refreshFactsButton = new QPushButton(tr("Refresh"));
	refreshFactsButton->setIcon(QIcon::fromTheme("view-refresh"));
	QPushButton *removeFactButton = new QPushButton(tr("Remove"));
	removeFactButton->setIcon(QIcon::fromTheme("list-remove"));
	QHBoxLayout *factsTopLayout = new QHBoxLayout;
	factsTopLayout->addWidget(addFactByTemplateButton);
	factsTopLayout->addWidget(addFactButton);
	factsTopLayout->addWidget(removeFactButton);
	factsTopLayout->addWidget(refreshFactsButton);
	factsTopLayout->addStretch();
	factsTopLayout->addWidget(duplicationButton);
	factsLayout->addLayout(factsTopLayout);
	factsLayout->addWidget(factsListWidget);
	factsWidget->setLayout(factsLayout);
	/***************************Deffacts***************************************/
	QGroupBox *deffactsWidget = new QGroupBox(tr("Facts List"));
	QVBoxLayout *deffactsLayout = new QVBoxLayout;
	deffactsListWidget = new QListWidget;
	addDeffactButton = new QPushButton(tr("Add"));
	addDeffactButton->setIcon(QIcon::fromTheme("list-add"));
	refreshDeffactsButton = new QPushButton(tr("Refresh"));
	refreshDeffactsButton->setIcon(QIcon::fromTheme("view-refresh"));
	QPushButton *removeDeffactButton = new QPushButton(tr("Remove"));
	removeDeffactButton->setIcon(QIcon::fromTheme("list-remove"));
	QHBoxLayout *deffactsTopLayout = new QHBoxLayout;
	deffactsTopLayout->addWidget(addDeffactButton);
	deffactsTopLayout->addWidget(removeDeffactButton);
	deffactsTopLayout->addWidget(refreshDeffactsButton);
	deffactsTopLayout->addStretch();
	deffactsLayout->addLayout(deffactsTopLayout);
	deffactsLayout->addWidget(deffactsListWidget);
	deffactsWidget->setLayout(deffactsLayout);
	/*****************************Rules****************************************/
	QGroupBox *rulesWidget = new QGroupBox(tr("Rules"));
	QVBoxLayout *rulesLayout = new QVBoxLayout;
	rulesListWidget = new QListWidget;
	addRuleButton = new QPushButton(tr("Add"));
	addRuleButton->setIcon(QIcon::fromTheme("list-add"));
	QPushButton *removeRuleButton = new QPushButton(tr("Remove"));
	removeRuleButton->setIcon(QIcon::fromTheme("list-remove"));
	refreshRulesButton = new QPushButton(tr("Refresh"));
	refreshRulesButton->setIcon(QIcon::fromTheme("view-refresh"));
	setBreakpointPushButton = new QPushButton(tr("Set Breakpoint"));
	setBreakpointPushButton->setIcon(QIcon::fromTheme("format-add-node"));
	removeBreakpointPushButton = new QPushButton(tr("Remove Breakpoint"));
	removeBreakpointPushButton->setIcon(QIcon::fromTheme("format-remove-node"));
	QHBoxLayout *rulesTopLayout = new QHBoxLayout;
	rulesTopLayout->addWidget(addRuleButton);
	rulesTopLayout->addWidget(removeRuleButton);
	rulesTopLayout->addWidget(refreshRulesButton);
	rulesTopLayout->addStretch();
	rulesTopLayout->addWidget(setBreakpointPushButton);
	rulesTopLayout->addWidget(removeBreakpointPushButton);
	rulesLayout->addLayout(rulesTopLayout);
	rulesLayout->addWidget(rulesListWidget);
	rulesWidget->setLayout(rulesLayout);
	/*****************************Activations**********************************/
	QGroupBox *activationsWidget = new QGroupBox(tr("Activations"));
	QVBoxLayout *activationsLayout = new QVBoxLayout;
	activationsListWidget = new QListWidget;
	QPushButton *removeActivationButton = new QPushButton(tr("Remove"));
	removeActivationButton->setIcon(QIcon::fromTheme("list-remove"));
	refreshActivationsButton = new QPushButton(tr("Refresh"));
	refreshActivationsButton->setIcon(QIcon::fromTheme("view-refresh"));
	runButton = new QPushButton(tr("Run"));
	runButton->setIcon(QIcon::fromTheme("arrow-right"));
	setActivationSaliencePushButton = new QPushButton(tr("Set Salience"));
	setActivationSaliencePushButton->setIcon(QIcon::fromTheme("view-statistics"));
	setStrategyPushButton = new QPushButton(tr("Set Strategy"));
	setStrategyPushButton->setIcon(QIcon::fromTheme("task-attention"));
	QHBoxLayout *activationsTopLayout = new QHBoxLayout;
	activationsTopLayout->addWidget(removeActivationButton);
	activationsTopLayout->addWidget(refreshActivationsButton);
	activationsTopLayout->addWidget(runButton);
	activationsTopLayout->addStretch();
	activationsTopLayout->addWidget(setActivationSaliencePushButton);
	activationsTopLayout->addWidget(setStrategyPushButton);
	activationsLayout->addLayout(activationsTopLayout);
	activationsLayout->addWidget(activationsListWidget);
	activationsWidget->setLayout(activationsLayout);
	/*****************************Globals*************************************/
	QGroupBox *globalsWidget = new QGroupBox(tr("Globals"));
	QVBoxLayout *globalsLayout = new QVBoxLayout;
	globalsListWidget = new QListWidget;
	addGlobalButton = new QPushButton(tr("Add"));
	addGlobalButton->setIcon(QIcon::fromTheme("list-add"));
	QPushButton *removeGlobalButton = new QPushButton(tr("Remove"));
	removeGlobalButton->setIcon(QIcon::fromTheme("list-remove"));
	refreshGlobalsButton = new QPushButton(tr("Refresh"));
	refreshGlobalsButton->setIcon(QIcon::fromTheme("view-refresh"));
	watchGlobalPushButton = new QPushButton(tr("Watch"));
	watchGlobalPushButton->setIcon(QIcon::fromTheme("layer-visible-on"));
	QHBoxLayout *globalsTopLayout = new QHBoxLayout;
	globalsTopLayout->addWidget(addGlobalButton);
	globalsTopLayout->addWidget(removeGlobalButton);
	globalsTopLayout->addWidget(refreshGlobalsButton);
	globalsTopLayout->addStretch();
	globalsTopLayout->addWidget(watchGlobalPushButton);
	globalsLayout->addLayout(globalsTopLayout);
	globalsLayout->addWidget(globalsListWidget);
	globalsWidget->setLayout(globalsLayout);
	/*****************************Functions************************************/
	QGroupBox *functionsWidget = new QGroupBox(tr("Functions"));
	QVBoxLayout *functionsLayout = new QVBoxLayout;
	functionsListWidget = new QListWidget;
	addFunctionButton = new QPushButton(tr("Add"));
	addFunctionButton->setIcon(QIcon::fromTheme("list-add"));
	QPushButton *removeFunctionButton = new QPushButton(tr("Remove"));
	removeFunctionButton->setIcon(QIcon::fromTheme("list-remove"));
	refreshFunctionsButton = new QPushButton(tr("Refresh"));
	refreshFunctionsButton->setIcon(QIcon::fromTheme("view-refresh"));
	QHBoxLayout *functionsTopLayout = new QHBoxLayout;
	functionsTopLayout->addWidget(addFunctionButton);
	functionsTopLayout->addWidget(removeFunctionButton);
	functionsTopLayout->addWidget(refreshFunctionsButton);
	functionsTopLayout->addStretch();
	functionsLayout->addLayout(functionsTopLayout);
	functionsLayout->addWidget(functionsListWidget);
	functionsWidget->setLayout(functionsLayout);
	/*****************************Classes**************************************/
	QGroupBox *classesWidget = new QGroupBox(tr("Classes"));
	QVBoxLayout *classesLayout = new QVBoxLayout;
	classesListWidget = new QListWidget;
	addClassButton = new QPushButton(tr("Add"));
	addClassButton->setIcon(QIcon::fromTheme("list-add"));
	QPushButton *removeClassButton = new QPushButton(tr("Remove"));
	removeClassButton->setIcon(QIcon::fromTheme("list-remove"));
	refreshClassesButton = new QPushButton(tr("Refresh"));
	refreshClassesButton->setIcon(QIcon::fromTheme("view-refresh"));
	QHBoxLayout *classesTopLayout = new QHBoxLayout;
	classesTopLayout->addWidget(addClassButton);
	classesTopLayout->addWidget(removeClassButton);
	classesTopLayout->addWidget(refreshClassesButton);
	classesTopLayout->addStretch();
	classesLayout->addLayout(classesTopLayout);
	classesLayout->addWidget(classesListWidget);
	classesWidget->setLayout(classesLayout);

	this->addWidget(templatesWidget);
	this->addWidget(factsWidget);
	this->addWidget(deffactsWidget);
	this->addWidget(rulesWidget);
	this->addWidget(activationsWidget);
	this->addWidget(globalsWidget);
	this->addWidget(functionsWidget);
	this->addWidget(classesWidget);

	connect(duplicationButton, SIGNAL(toggled(bool)), this, SLOT(duplicationProxySlot(bool)));
	connect(setBreakpointPushButton, SIGNAL(clicked()), this, SLOT(setBreakpointSlot()));
	connect(removeBreakpointPushButton, SIGNAL(clicked()), this, SLOT(removeBreakpointSlot()));
	connect(removeTemplateButton, SIGNAL(clicked()), this, SLOT(removeTemplateSlot()));
	connect(removeFactButton, SIGNAL(clicked()), this, SLOT(removeFactSlot()));
	connect(removeDeffactButton, SIGNAL(clicked()), this, SLOT(removeDeffactsSlot()));
	connect(removeRuleButton, SIGNAL(clicked()), this, SLOT(removeDefruleSlot()));
	connect(removeActivationButton, SIGNAL(clicked()), this, SLOT(removeActivationSlot()));
	connect(removeGlobalButton, SIGNAL(clicked()), this, SLOT(removeGlobalSlot()));
	connect(watchGlobalPushButton, SIGNAL(clicked()), this, SLOT(watchGlobalSlot()));
}

void ProjectStackedWidget::refreshFacts(QStringList list)
{
	factsListWidget->clear();
	QString str;
	foreach(str, list)
	{
		QString name = str;
		int index = str.remove(str.indexOf(" "), str.length() - str.indexOf(" ")).remove(0, 2).toInt();
		name.remove(0, name.indexOf(" "));
		name = name.simplified();
		QListWidgetItem *item = new QListWidgetItem(factsListWidget);
		item->setData(Qt::UserRole, index);
		item->setText(name);
	}
}

void ProjectStackedWidget::refreshDeffacts(QStringList deffactsList)
{
	deffactsListWidget->clear();
	QString str;
	foreach(str, deffactsList)
	{
		QListWidgetItem *item = new QListWidgetItem(deffactsListWidget);
		item->setText(str);
	}
}

void ProjectStackedWidget::refreshTemplates(QStringList templates)
{
	templatesListWidget->clear();
	QString str;
	foreach(str, templates)
	{
		QListWidgetItem *item = new QListWidgetItem(templatesListWidget);
		item->setText(str);
	}
}

void ProjectStackedWidget::refreshRules(QStringList rules)
{
	rulesListWidget->clear();
	QString str;
	foreach(str, rules)
	{
		QListWidgetItem *item = new QListWidgetItem(rulesListWidget);
		if(str.indexOf("[bp]/")==0)
		{
			str.remove(0, 5);
			item->setIcon(QIcon::fromTheme("snap-node"));
		}
		item->setText(str);
	}
}

void ProjectStackedWidget::refreshActivations(QStringList activations)
{
	activationsListWidget->clear();
	QString str;
	foreach(str, activations)
	{
		QListWidgetItem *item = new QListWidgetItem(activationsListWidget);
		item->setText(str);
	}
}

void ProjectStackedWidget::refreshGlobals(QStringList globals)
{
	globalsListWidget->clear();
	QString str;
	foreach(str, globals)
	{
		QListWidgetItem *item = new QListWidgetItem(globalsListWidget);
		item->setText(str);
	}
}

void ProjectStackedWidget::watchGlobalSlot()
{
	QList<QListWidgetItem*> globals = globalsListWidget->selectedItems();
	if(!globals.isEmpty())
		emit watchGlobalSignal(globals.at(0)->text());
}

void ProjectStackedWidget::duplicationProxySlot(bool state)
{
	emit setFactDuplicationSignal(state, false);
}

void ProjectStackedWidget::setBreakpointSlot()
{
	QList<QListWidgetItem*> rules = rulesListWidget->selectedItems();
	if(!rules.isEmpty())
		emit setBreakpointSignal(rules.at(0)->text(), false);
}

void ProjectStackedWidget::removeBreakpointSlot()
{
	QList<QListWidgetItem*> rules = rulesListWidget->selectedItems();
	if(!rules.isEmpty())
		emit removeBreakpointSignal(rules.at(0)->text(), false);
}

void ProjectStackedWidget::removeTemplateSlot()
{
	QList<QListWidgetItem*> templates = templatesListWidget->selectedItems();
	if(!templates.isEmpty())
		emit removeTemplateSignal(templates.at(0)->text(), false);
}

void ProjectStackedWidget::removeFactSlot()
{
	QList<QListWidgetItem*> facts = factsListWidget->selectedItems();
	if(!facts.isEmpty())
		emit removeFactSignal(facts.at(0)->data(Qt::UserRole).toInt(), false);
}

void ProjectStackedWidget::removeDeffactsSlot()
{
	QList<QListWidgetItem*> deffacts = deffactsListWidget->selectedItems();
	if(!deffacts.isEmpty())
		emit removeFactsListSignal(deffacts.at(0)->text(), false);
}

void ProjectStackedWidget::removeDefruleSlot()
{
	QList<QListWidgetItem*> rules = rulesListWidget->selectedItems();
	if(!rules.isEmpty())
		emit removeRuleSignal(rules.at(0)->text(), false);
}

void ProjectStackedWidget::removeActivationSlot()
{
	QList<QListWidgetItem*> activations = activationsListWidget->selectedItems();
	if(!activations.isEmpty())
		emit removeActivationSignal(activations.at(0)->text(), false);
}

void ProjectStackedWidget::removeGlobalSlot()
{
	QList<QListWidgetItem*> globals = globalsListWidget->selectedItems();
	if(!globals.isEmpty())
		emit removeGlobalSignal(globals.at(0)->text(), false);
}

void ProjectStackedWidget::clearSlot()
{
	templatesListWidget->clear();
	factsListWidget->clear();
	deffactsListWidget->clear();
	rulesListWidget->clear();
	activationsListWidget->clear();
	globalsListWidget->clear();
	functionsListWidget->clear();
	classesListWidget->clear();
}

#include "projectstackedwidget.h"
#include <QListWidgetItem>
#include <QList>
#include <QDebug>
#include <QRegExp>
#include <QAction>
#include <QMenu>

ProjectStackedWidget::ProjectStackedWidget(QWidget *parent) :
	QStackedWidget(parent)
{
	/**************************Templates***************************************/
	QGroupBox *templatesWidget = new QGroupBox(tr("Templates"));
	QVBoxLayout *templatesLayout = new QVBoxLayout;
	templatesListWidget = new QListWidget;
	addTemplatePushButton = new QPushButton(tr("Add"));
	addTemplatePushButton->setIcon(QIcon::fromTheme("list-add"));
	refreshTemplatesPushButton = new QPushButton(tr("Refresh"));
	refreshTemplatesPushButton->setIcon(QIcon::fromTheme("view-refresh"));
	viewTemplatePushButton = new QPushButton(tr("View"));
	viewTemplatePushButton->setIcon(QIcon::fromTheme("layer-visible-on"));
	QPushButton *removeTemplateButton = new QPushButton(tr("Remove"));
	removeTemplateButton->setIcon(QIcon::fromTheme("list-remove"));
	QHBoxLayout *templatesTopLayout = new QHBoxLayout;
	templatesTopLayout->addWidget(addTemplatePushButton);
	templatesTopLayout->addWidget(removeTemplateButton);
	templatesTopLayout->addWidget(refreshTemplatesPushButton);
	templatesTopLayout->addStretch();
	templatesTopLayout->addWidget(viewTemplatePushButton);
	templatesLayout->addLayout(templatesTopLayout);
	templatesLayout->addWidget(templatesListWidget);
	templatesWidget->setLayout(templatesLayout);
	/*****************************Facts****************************************/
	QGroupBox *factsWidget = new QGroupBox(tr("Facts"));
	QVBoxLayout *factsLayout = new QVBoxLayout;
	duplicationPushButton = new QPushButton(tr("Enable Duplication"));
	duplicationPushButton->setCheckable(true);
	duplicationPushButton->setIcon(QIcon::fromTheme("edit-copy"));
	factsListWidget = new QListWidget;
	addFactPushButton = new QPushButton(tr("Add"));
	addFactPushButton->setIcon(QIcon::fromTheme("list-add"));
	addFactByTemplatePushButton = new QPushButton(tr("Add By Template"));
	addFactByTemplatePushButton->setIcon(QIcon::fromTheme("list-add"));
	refreshFactsPushButton = new QPushButton(tr("Refresh"));
	refreshFactsPushButton->setIcon(QIcon::fromTheme("view-refresh"));
	QPushButton *removeFactButton = new QPushButton(tr("Remove"));
	removeFactButton->setIcon(QIcon::fromTheme("list-remove"));
	QHBoxLayout *factsTopLayout = new QHBoxLayout;
	factsTopLayout->addWidget(addFactByTemplatePushButton);
	factsTopLayout->addWidget(addFactPushButton);
	factsTopLayout->addWidget(removeFactButton);
	factsTopLayout->addWidget(refreshFactsPushButton);
	factsTopLayout->addStretch();
	factsTopLayout->addWidget(duplicationPushButton);
	factsLayout->addLayout(factsTopLayout);
	factsLayout->addWidget(factsListWidget);
	factsWidget->setLayout(factsLayout);
	/***************************Deffacts***************************************/
	QGroupBox *deffactsWidget = new QGroupBox(tr("Facts List"));
	QVBoxLayout *deffactsLayout = new QVBoxLayout;
	deffactsListWidget = new QListWidget;
	addDeffactPushButton = new QPushButton(tr("Add"));
	addDeffactPushButton->setIcon(QIcon::fromTheme("list-add"));
	refreshDeffactsPushButton = new QPushButton(tr("Refresh"));
	refreshDeffactsPushButton->setIcon(QIcon::fromTheme("view-refresh"));
	viewDeffactPushButton = new QPushButton(tr("View"));
	viewDeffactPushButton->setIcon(QIcon::fromTheme("layer-visible-on"));
	QPushButton *removeDeffactButton = new QPushButton(tr("Remove"));
	removeDeffactButton->setIcon(QIcon::fromTheme("list-remove"));
	QHBoxLayout *deffactsTopLayout = new QHBoxLayout;
	deffactsTopLayout->addWidget(addDeffactPushButton);
	deffactsTopLayout->addWidget(removeDeffactButton);
	deffactsTopLayout->addWidget(refreshDeffactsPushButton);
	deffactsTopLayout->addStretch();
	deffactsTopLayout->addWidget(viewDeffactPushButton);
	deffactsLayout->addLayout(deffactsTopLayout);
	deffactsLayout->addWidget(deffactsListWidget);
	deffactsWidget->setLayout(deffactsLayout);
	/*****************************Rules****************************************/
	QGroupBox *rulesWidget = new QGroupBox(tr("Rules"));
	QVBoxLayout *rulesLayout = new QVBoxLayout;
	rulesListWidget = new QListWidget;
	addRulePushButton = new QPushButton(tr("Add"));
	addRulePushButton->setIcon(QIcon::fromTheme("list-add"));
	QPushButton *removeRuleButton = new QPushButton(tr("Remove"));
	removeRuleButton->setIcon(QIcon::fromTheme("list-remove"));
	refreshRulesPushButton = new QPushButton(tr("Refresh"));
	refreshRulesPushButton->setIcon(QIcon::fromTheme("view-refresh"));
	viewRulePushButton = new QPushButton(tr("View"));
	viewRulePushButton->setIcon(QIcon::fromTheme("layer-visible-on"));
	setBreakpointPushButton = new QPushButton(tr("Set Breakpoint"));
	setBreakpointPushButton->setIcon(QIcon::fromTheme("format-add-node"));
	removeBreakpointPushButton = new QPushButton(tr("Remove Breakpoint"));
	removeBreakpointPushButton->setIcon(QIcon::fromTheme("format-remove-node"));
	QHBoxLayout *rulesTopLayout = new QHBoxLayout;
	rulesTopLayout->addWidget(addRulePushButton);
	rulesTopLayout->addWidget(removeRuleButton);
	rulesTopLayout->addWidget(refreshRulesPushButton);
	rulesTopLayout->addStretch();
	rulesTopLayout->addWidget(setBreakpointPushButton);
	rulesTopLayout->addWidget(removeBreakpointPushButton);
	rulesTopLayout->addWidget(viewRulePushButton);
	rulesLayout->addLayout(rulesTopLayout);
	rulesLayout->addWidget(rulesListWidget);
	rulesWidget->setLayout(rulesLayout);
	/*****************************Activations**********************************/
	QGroupBox *activationsWidget = new QGroupBox(tr("Activations"));
	QVBoxLayout *activationsLayout = new QVBoxLayout;
	activationsListWidget = new QListWidget;
	QPushButton *removeActivationButton = new QPushButton(tr("Remove"));
	removeActivationButton->setIcon(QIcon::fromTheme("list-remove"));
	refreshActivationsPushButton = new QPushButton(tr("Refresh"));
	refreshActivationsPushButton->setIcon(QIcon::fromTheme("view-refresh"));
	runPushButton = new QPushButton(tr("Run"));
	runPushButton->setIcon(QIcon::fromTheme("arrow-right"));
	setActivationSaliencePushButton = new QPushButton(tr("Set Salience"));
	setActivationSaliencePushButton->setIcon(QIcon::fromTheme("view-statistics"));
	setStrategyPushButton = new QPushButton(tr("Set Strategy"));
	setStrategyPushButton->setIcon(QIcon::fromTheme("task-attention"));
	QHBoxLayout *activationsTopLayout = new QHBoxLayout;
	activationsTopLayout->addWidget(removeActivationButton);
	activationsTopLayout->addWidget(refreshActivationsPushButton);
	activationsTopLayout->addWidget(runPushButton);
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
	addGlobalPushButton = new QPushButton(tr("Add"));
	addGlobalPushButton->setIcon(QIcon::fromTheme("list-add"));
	QPushButton *removeGlobalButton = new QPushButton(tr("Remove"));
	removeGlobalButton->setIcon(QIcon::fromTheme("list-remove"));
	refreshGlobalsPushButton = new QPushButton(tr("Refresh"));
	refreshGlobalsPushButton->setIcon(QIcon::fromTheme("view-refresh"));
	viewGlobalPushButton = new QPushButton(tr("View"));
	viewGlobalPushButton->setIcon(QIcon::fromTheme("layer-visible-on"));
	QHBoxLayout *globalsTopLayout = new QHBoxLayout;
	globalsTopLayout->addWidget(addGlobalPushButton);
	globalsTopLayout->addWidget(removeGlobalButton);
	globalsTopLayout->addWidget(refreshGlobalsPushButton);
	globalsTopLayout->addStretch();
	globalsTopLayout->addWidget(viewGlobalPushButton);
	globalsLayout->addLayout(globalsTopLayout);
	globalsLayout->addWidget(globalsListWidget);
	globalsWidget->setLayout(globalsLayout);
	/*****************************Functions************************************/
	QGroupBox *functionsWidget = new QGroupBox(tr("Functions"));
	QVBoxLayout *functionsLayout = new QVBoxLayout;
	functionsListWidget = new QListWidget;
	addFunctionPushButton = new QPushButton(tr("Add"));
	addFunctionPushButton->setIcon(QIcon::fromTheme("list-add"));
	QPushButton *removeFunctionButton = new QPushButton(tr("Remove"));
	removeFunctionButton->setIcon(QIcon::fromTheme("list-remove"));
	refreshFunctionsPushButton = new QPushButton(tr("Refresh"));
	refreshFunctionsPushButton->setIcon(QIcon::fromTheme("view-refresh"));
	viewFunctionPushButton = new QPushButton(tr("View"));
	viewFunctionPushButton->setIcon(QIcon::fromTheme("layer-visible-on"));
	QHBoxLayout *functionsTopLayout = new QHBoxLayout;
	functionsTopLayout->addWidget(addFunctionPushButton);
	functionsTopLayout->addWidget(removeFunctionButton);
	functionsTopLayout->addWidget(refreshFunctionsPushButton);
	functionsTopLayout->addStretch();
	functionsTopLayout->addWidget(viewFunctionPushButton);
	functionsLayout->addLayout(functionsTopLayout);
	functionsLayout->addWidget(functionsListWidget);
	functionsWidget->setLayout(functionsLayout);
	/*****************************Generic**************************************/
	QGroupBox *genericWidget = new QGroupBox(tr("Generic Functions"));
	QVBoxLayout *genericLayout = new QVBoxLayout;
	genericListWidget = new QListWidget;
	addGenericPushButton = new QPushButton(tr("Add"));
	addGenericPushButton->setIcon(QIcon::fromTheme("list-add"));
	QPushButton *removeGenericButton = new QPushButton(tr("Remove"));
	removeGenericButton->setIcon(QIcon::fromTheme("list-remove"));
	refreshGenericPushButton = new QPushButton(tr("Refresh"));
	refreshGenericPushButton->setIcon(QIcon::fromTheme("view-refresh"));
	viewGenericPushButton = new QPushButton(tr("View"));
	viewGenericPushButton->setIcon(QIcon::fromTheme("layer-visible-on"));
	QHBoxLayout *genericTopLayout = new QHBoxLayout;
	genericTopLayout->addWidget(addGenericPushButton);
	genericTopLayout->addWidget(removeGenericButton);
	genericTopLayout->addWidget(refreshGenericPushButton);
	genericTopLayout->addStretch();
	genericTopLayout->addWidget(viewGenericPushButton);
	genericLayout->addLayout(genericTopLayout);
	genericLayout->addWidget(genericListWidget);
	genericWidget->setLayout(genericLayout);
	/*****************************Methods***************************************/
	QGroupBox *methodsWidget = new QGroupBox(tr("Methods"));
	QVBoxLayout *methodsLayout = new QVBoxLayout;
	methodsListWidget = new QListWidget;
	addMethodPushButton = new QPushButton(tr("Add"));
	addMethodPushButton->setIcon(QIcon::fromTheme("list-add"));
	QPushButton *removeMethodButton = new QPushButton(tr("Remove"));
	removeMethodButton->setIcon(QIcon::fromTheme("list-remove"));
	refreshMethodsPushButton = new QPushButton(tr("Refresh"));
	refreshMethodsPushButton->setIcon(QIcon::fromTheme("view-refresh"));
	viewMethodPushButton = new QPushButton(tr("View"));
	viewMethodPushButton->setIcon(QIcon::fromTheme("layer-visible-on"));
	QHBoxLayout *methodsTopLayout = new QHBoxLayout;
	methodsTopLayout->addWidget(addMethodPushButton);
	methodsTopLayout->addWidget(removeMethodButton);
	methodsTopLayout->addWidget(refreshMethodsPushButton);
	methodsTopLayout->addStretch();
	methodsTopLayout->addWidget(viewMethodPushButton);
	methodsLayout->addLayout(methodsTopLayout);
	methodsLayout->addWidget(methodsListWidget);
	methodsWidget->setLayout(methodsLayout);
	/*****************************Classes**************************************/
	QGroupBox *classesWidget = new QGroupBox(tr("Classes"));
	QVBoxLayout *classesLayout = new QVBoxLayout;
	classesListWidget = new QListWidget;
	addClassPushButton = new QPushButton(tr("Add"));
	addClassPushButton->setIcon(QIcon::fromTheme("list-add"));
	QPushButton *removeClassButton = new QPushButton(tr("Remove"));
	removeClassButton->setIcon(QIcon::fromTheme("list-remove"));
	refreshClassesPushButton = new QPushButton(tr("Refresh"));
	refreshClassesPushButton->setIcon(QIcon::fromTheme("view-refresh"));
	defaultsModePushButton = new QPushButton(tr("Set Defaults Mode"));
	defaultsModePushButton->setIcon(QIcon::fromTheme("preferences-other"));
	viewClassPushButton = new QPushButton(tr("View"));
	viewClassPushButton->setIcon(QIcon::fromTheme("layer-visible-on"));
	classInfoPushButton = new QPushButton(tr("Class Info"));
	classInfoPushButton->setIcon(QIcon::fromTheme("documentinfo"));
	QMenu *classInfoMenu = new QMenu;
	subClassesAction = new QAction(QIcon::fromTheme("code-class"), tr("Subclasses"), this);
	superClassesAction = new QAction(QIcon::fromTheme("code-class"), tr("Superclasses"), this);
	metaInformationAction = new QAction(QIcon::fromTheme("metacontact_unknown"), tr("Meta Information"), this);
	classInfoMenu->addAction(subClassesAction);
	classInfoMenu->addAction(superClassesAction);
	classInfoMenu->addAction(metaInformationAction);
	classInfoPushButton->setMenu(classInfoMenu);
	QHBoxLayout *classesTopLayout = new QHBoxLayout;
	classesTopLayout->addWidget(addClassPushButton);
	classesTopLayout->addWidget(removeClassButton);
	classesTopLayout->addWidget(refreshClassesPushButton);
	classesTopLayout->addStretch();
	classesTopLayout->addWidget(defaultsModePushButton);
	classesTopLayout->addWidget(viewClassPushButton);
	classesTopLayout->addWidget(classInfoPushButton);
	classesLayout->addLayout(classesTopLayout);
	classesLayout->addWidget(classesListWidget);
	classesWidget->setLayout(classesLayout);
	/************************Message*Handlers**********************************/
	QGroupBox *messageHandlersWidget = new QGroupBox(tr("Message Handlers"));
	QVBoxLayout *messageHandlersLayout = new QVBoxLayout;
	messageHandlersListWidget = new QListWidget;
	addMessageHandlerPushButton = new QPushButton(tr("Add"));
	addMessageHandlerPushButton->setIcon(QIcon::fromTheme("list-add"));
	QPushButton *removeMessageHandlerPushButton = new QPushButton(tr("Remove"));
	removeMessageHandlerPushButton->setIcon(QIcon::fromTheme("list-remove"));
	refreshMessageHandlersPushButton = new QPushButton(tr("Refresh"));
	refreshMessageHandlersPushButton->setIcon(QIcon::fromTheme("view-refresh"));
	viewMessageHandlerPushButton = new QPushButton(tr("View"));
	viewMessageHandlerPushButton->setIcon(QIcon::fromTheme("layer-visible-on"));
	QHBoxLayout *messageHandlersTopLayout = new QHBoxLayout;
	messageHandlersTopLayout->addWidget(addMessageHandlerPushButton);
	messageHandlersTopLayout->addWidget(removeMessageHandlerPushButton);
	messageHandlersTopLayout->addWidget(refreshMessageHandlersPushButton);
	messageHandlersTopLayout->addStretch();
	messageHandlersTopLayout->addWidget(viewMessageHandlerPushButton);
	messageHandlersLayout->addLayout(messageHandlersTopLayout);
	messageHandlersLayout->addWidget(messageHandlersListWidget);
	messageHandlersWidget->setLayout(messageHandlersLayout);
	/*****************************Instances************************************/
	QGroupBox *instancesWidget = new QGroupBox(tr("Instances"));
	QVBoxLayout *instancesLayout = new QVBoxLayout;
	instancesListWidget = new QListWidget;
	addInstancePushButton = new QPushButton(tr("Add"));
	addInstancePushButton->setIcon(QIcon::fromTheme("list-add"));
	QPushButton *removeInstanceButton = new QPushButton(tr("Remove"));
	removeInstanceButton->setIcon(QIcon::fromTheme("list-remove"));
	refreshInstancesPushButton = new QPushButton(tr("Refresh"));
	refreshInstancesPushButton->setIcon(QIcon::fromTheme("view-refresh"));
	viewInstancePushButton = new QPushButton(tr("View"));
	viewInstancePushButton->setIcon(QIcon::fromTheme("layer-visible-on"));
	QHBoxLayout *instancesTopLayout = new QHBoxLayout;
	instancesTopLayout->addWidget(addInstancePushButton);
	instancesTopLayout->addWidget(removeInstanceButton);
	instancesTopLayout->addWidget(refreshInstancesPushButton);
	instancesTopLayout->addStretch();
	instancesTopLayout->addWidget(viewInstancePushButton);
	instancesLayout->addLayout(instancesTopLayout);
	instancesLayout->addWidget(instancesListWidget);
	instancesWidget->setLayout(instancesLayout);
	/*****************************Modules**************************************/
	QGroupBox *modulesWidget = new QGroupBox(tr("Modules"));
	QVBoxLayout *modulesLayout = new QVBoxLayout;
	modulesListWidget = new QListWidget;
	addModulePushButton = new QPushButton(tr("Add"));
	addModulePushButton->setIcon(QIcon::fromTheme("list-add"));
	refreshModulesPushButton = new QPushButton(tr("Refresh"));
	refreshModulesPushButton->setIcon(QIcon::fromTheme("view-refresh"));
	viewModulePushButton = new QPushButton(tr("View"));
	viewModulePushButton->setIcon(QIcon::fromTheme("layer-visible-on"));
	currentModulePushButton = new QPushButton(tr("Set Current Module"));
	currentModulePushButton->setIcon(QIcon::fromTheme("pattern-basis"));
	QHBoxLayout *modulesTopLayout = new QHBoxLayout;
	modulesTopLayout->addWidget(addModulePushButton);
	modulesTopLayout->addWidget(refreshModulesPushButton);
	modulesTopLayout->addStretch();
	modulesTopLayout->addWidget(currentModulePushButton);
	modulesTopLayout->addWidget(viewModulePushButton);
	modulesLayout->addLayout(modulesTopLayout);
	modulesLayout->addWidget(modulesListWidget);
	modulesWidget->setLayout(modulesLayout);

	this->addWidget(templatesWidget);
	this->addWidget(factsWidget);
	this->addWidget(deffactsWidget);
	this->addWidget(rulesWidget);
	this->addWidget(activationsWidget);
	this->addWidget(globalsWidget);
	this->addWidget(functionsWidget);
	this->addWidget(genericWidget);
	this->addWidget(methodsWidget);
	this->addWidget(classesWidget);
	this->addWidget(messageHandlersWidget);
	this->addWidget(instancesWidget);
	this->addWidget(modulesWidget);

	connect(setBreakpointPushButton, SIGNAL(clicked()), this, SLOT(setBreakpointSlot()));
	connect(removeBreakpointPushButton, SIGNAL(clicked()), this, SLOT(removeBreakpointSlot()));
	connect(removeTemplateButton, SIGNAL(clicked()), this, SLOT(removeTemplateSlot()));
	connect(viewTemplatePushButton, SIGNAL(clicked()), this, SLOT(viewTemplateSlot()));
	connect(removeFactButton, SIGNAL(clicked()), this, SLOT(removeFactSlot()));
	connect(removeDeffactButton, SIGNAL(clicked()), this, SLOT(removeDeffactsSlot()));
	connect(viewDeffactPushButton, SIGNAL(clicked()), this, SLOT(viewFactsListSlot()));
	connect(removeRuleButton, SIGNAL(clicked()), this, SLOT(removeDefruleSlot()));
	connect(viewRulePushButton, SIGNAL(clicked()), this, SLOT(viewRuleSlot()));
	connect(removeActivationButton, SIGNAL(clicked()), this, SLOT(removeActivationSlot()));
	connect(removeGlobalButton, SIGNAL(clicked()), this, SLOT(removeGlobalSlot()));
	connect(viewGlobalPushButton, SIGNAL(clicked()), this, SLOT(viewGlobalSlot()));
	connect(removeFunctionButton, SIGNAL(clicked()), this, SLOT(removeFunctionSlot()));
	connect(viewFunctionPushButton, SIGNAL(clicked()), this, SLOT(viewFunctionSlot()));
	connect(removeGenericButton, SIGNAL(clicked()), this, SLOT(removeGenericSlot()));
	connect(viewGenericPushButton, SIGNAL(clicked()), this, SLOT(viewGenericSlot()));
	connect(removeMethodButton, SIGNAL(clicked()), this, SLOT(removeMethodSlot()));
	connect(viewMethodPushButton, SIGNAL(clicked()), this, SLOT(viewMethodSlot()));
	connect(removeClassButton, SIGNAL(clicked()), this, SLOT(removeClassSlot()));
	connect(viewClassPushButton, SIGNAL(clicked()), this, SLOT(viewClassSlot()));
	connect(metaInformationAction, SIGNAL(triggered()), this, SLOT(metaInformationSlot()));
	connect(subClassesAction, SIGNAL(triggered()), this, SLOT(subClassesSlot()));
	connect(superClassesAction, SIGNAL(triggered()), this, SLOT(superClassesSlot()));
	connect(removeMessageHandlerPushButton, SIGNAL(clicked()), this, SLOT(removeMessageHandlerSlot()));
	connect(viewMessageHandlerPushButton, SIGNAL(clicked()), this, SLOT(viewMessageHandlerSlot()));
	connect(removeInstanceButton, SIGNAL(clicked()), this, SLOT(removeInstanceSlot()));
	connect(viewInstancePushButton, SIGNAL(clicked()), this, SLOT(viewInstanceSlot()));
	connect(viewModulePushButton, SIGNAL(clicked()), this, SLOT(viewModuleSlot()));
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
	genericListWidget->clear();
	methodsListWidget->clear();
	classesListWidget->clear();
}

//Templates

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

void ProjectStackedWidget::viewTemplateSlot()
{
	QList<QListWidgetItem*> templates = templatesListWidget->selectedItems();
	if(!templates.isEmpty())
		emit viewTemplateSignal(templates.at(0)->text());
}

void ProjectStackedWidget::removeTemplateSlot()
{
	QList<QListWidgetItem*> templates = templatesListWidget->selectedItems();
	if(!templates.isEmpty())
		emit removeTemplateSignal(templates.at(0)->text());
}

//Facts

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

void ProjectStackedWidget::removeFactSlot()
{
	QList<QListWidgetItem*> facts = factsListWidget->selectedItems();
	if(!facts.isEmpty())
		emit removeFactSignal(facts.at(0)->data(Qt::UserRole).toInt());
}

//Facts Lists

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

void ProjectStackedWidget::viewFactsListSlot()
{
	QList<QListWidgetItem*> factsList = deffactsListWidget->selectedItems();
	if(!factsList.isEmpty())
		emit viewFactsListSignal(factsList.at(0)->text());
}

void ProjectStackedWidget::removeDeffactsSlot()
{
	QList<QListWidgetItem*> deffacts = deffactsListWidget->selectedItems();
	if(!deffacts.isEmpty())
		emit removeFactsListSignal(deffacts.at(0)->text());
}

//Rules

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

void ProjectStackedWidget::viewRuleSlot()
{
	QList<QListWidgetItem*> rules = rulesListWidget->selectedItems();
	if(!rules.isEmpty())
		emit viewRuleSignal(rules.at(0)->text());
}

void ProjectStackedWidget::removeDefruleSlot()
{
	QList<QListWidgetItem*> rules = rulesListWidget->selectedItems();
	if(!rules.isEmpty())
		emit removeRuleSignal(rules.at(0)->text());
}

void ProjectStackedWidget::setBreakpointSlot()
{
	QList<QListWidgetItem*> rules = rulesListWidget->selectedItems();
	if(!rules.isEmpty())
		emit setBreakpointSignal(rules.at(0)->text());
}

void ProjectStackedWidget::removeBreakpointSlot()
{
	QList<QListWidgetItem*> rules = rulesListWidget->selectedItems();
	if(!rules.isEmpty())
		emit removeBreakpointSignal(rules.at(0)->text());
}

//Agenda

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

void ProjectStackedWidget::removeActivationSlot()
{
	QList<QListWidgetItem*> activations = activationsListWidget->selectedItems();
	if(!activations.isEmpty())
		emit removeActivationSignal(activations.at(0)->text());
}

//Globals

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

void ProjectStackedWidget::viewGlobalSlot()
{
	QList<QListWidgetItem*> globals = globalsListWidget->selectedItems();
	if(!globals.isEmpty())
		emit viewGlobalSignal(globals.at(0)->text());
}

void ProjectStackedWidget::removeGlobalSlot()
{
	QList<QListWidgetItem*> globals = globalsListWidget->selectedItems();
	if(!globals.isEmpty())
		emit removeGlobalSignal(globals.at(0)->text());
}

//Functions

void ProjectStackedWidget::refreshFunctions(QStringList functions)
{
	functionsListWidget->clear();
	QString str;
	foreach(str, functions)
	{
		QListWidgetItem *item = new QListWidgetItem(functionsListWidget);
		item->setText(str);
	}
}

void ProjectStackedWidget::viewFunctionSlot()
{
	QList<QListWidgetItem*> functions = functionsListWidget->selectedItems();
	if(!functions.isEmpty())
		emit viewFunctionSignal(functions.at(0)->text());
}

void ProjectStackedWidget::removeFunctionSlot()
{
	QList<QListWidgetItem*> functions = functionsListWidget->selectedItems();
	if(!functions.isEmpty())
		emit removeFunctionSignal(functions.at(0)->text());
}

//Generic

void ProjectStackedWidget::refreshGeneric(QStringList generic)
{
	genericListWidget->clear();
	QString str;
	foreach(str, generic)
	{
		QListWidgetItem *item = new QListWidgetItem(genericListWidget);
		item->setText(str);
	}
}

void ProjectStackedWidget::viewGenericSlot()
{
	QList<QListWidgetItem*> generic = genericListWidget->selectedItems();
	if(!generic.isEmpty())
		emit viewGenericSignal(generic.at(0)->text());
}

void ProjectStackedWidget::removeGenericSlot()
{
	QList<QListWidgetItem*> generic = genericListWidget->selectedItems();
	if(!generic.isEmpty())
		emit removeGenericSignal(generic.at(0)->text());
}

//Methods

void ProjectStackedWidget::refreshMethods(QHash<QString, int> methods)
{
	methodsListWidget->clear();
	QHashIterator<QString, int> i(methods);
	while (i.hasNext())
	{
		i.next();
		QListWidgetItem *item = new QListWidgetItem(methodsListWidget);
		item->setText(i.key());
		item->setData(Qt::UserRole, i.value());
	}
}

void ProjectStackedWidget::viewMethodSlot()
{
	QList<QListWidgetItem*> methods = methodsListWidget->selectedItems();
	if(!methods.isEmpty())
		emit viewMethodSignal(methods.at(0)->text(), methods.at(0)->data(Qt::UserRole).toInt());
}

void ProjectStackedWidget::removeMethodSlot()
{
	QList<QListWidgetItem*> methods = methodsListWidget->selectedItems();
	if(!methods.isEmpty())
		emit removeMethodSignal(methods.at(0)->text(), methods.at(0)->data(Qt::UserRole).toInt());
}

//Classes

void ProjectStackedWidget::refreshClasses(QStringList classes)
{
	classesListWidget->clear();
	QString str;
	foreach(str, classes)
	{
		QListWidgetItem *item = new QListWidgetItem(classesListWidget);
		item->setText(str);
	}
}

void ProjectStackedWidget::viewClassSlot()
{
	QList<QListWidgetItem*> classes = classesListWidget->selectedItems();
	if(!classes.isEmpty())
		emit viewClassSignal(classes.at(0)->text());
}

void ProjectStackedWidget::removeClassSlot()
{
	QList<QListWidgetItem*> classes = classesListWidget->selectedItems();
	if(!classes.isEmpty())
		emit removeClassSignal(classes.at(0)->text());
}

void ProjectStackedWidget::metaInformationSlot()
{
	QList<QListWidgetItem*> classes = classesListWidget->selectedItems();
	if(!classes.isEmpty())
		emit metaInformationSignal(classes.at(0)->text());
}

void ProjectStackedWidget::subClassesSlot()
{
	QList<QListWidgetItem*> classes = classesListWidget->selectedItems();
	if(!classes.isEmpty())
		emit subClassesSignal(classes.at(0)->text());
}

void ProjectStackedWidget::superClassesSlot()
{
	QList<QListWidgetItem*> classes = classesListWidget->selectedItems();
	if(!classes.isEmpty())
		emit superClassesSignal(classes.at(0)->text());
}

//Message Handlers

void ProjectStackedWidget::refreshMessageHandlers(QHash<QString, unsigned int> messageHandlers)
{
	messageHandlersListWidget->clear();
	QHashIterator<QString, unsigned int> i(messageHandlers);
	while(i.hasNext())
	{
		i.next();
		QListWidgetItem *item = new QListWidgetItem(messageHandlersListWidget);
		item->setText(i.key());
		item->setData(Qt::UserRole, i.value());
	}
}

void ProjectStackedWidget::viewMessageHandlerSlot()
{
	QList<QListWidgetItem*> messageHandlers = messageHandlersListWidget->selectedItems();
	if(!messageHandlers.isEmpty())
		emit viewMessageHandlerSignal(messageHandlers.at(0)->text(), unsigned(messageHandlers.at(0)->data(Qt::UserRole).toInt()));
}

void ProjectStackedWidget::removeMessageHandlerSlot()
{
	QList<QListWidgetItem*> messageHandlers = messageHandlersListWidget->selectedItems();
	if(!messageHandlers.isEmpty())
		emit removeMessageHandlerSignal(messageHandlers.at(0)->text(), unsigned(messageHandlers.at(0)->data(Qt::UserRole).toInt()));
}

//Instances

void ProjectStackedWidget::refreshInstancesSlot(QStringList instances)
{
	instancesListWidget->clear();
	QString str;
	foreach(str, instances)
	{
		QListWidgetItem *item = new QListWidgetItem(instancesListWidget);
		item->setText(str);
	}
}

void ProjectStackedWidget::viewInstanceSlot()
{
	QList<QListWidgetItem*> instances = instancesListWidget->selectedItems();
	if(!instances.isEmpty())
		emit viewInstanceSignal(instances.at(0)->text());
}

void ProjectStackedWidget::removeInstanceSlot()
{
	QList<QListWidgetItem*> instances = instancesListWidget->selectedItems();
	if(!instances.isEmpty())
		emit removeInstanceSignal(instances.at(0)->text());
}

//Modules

void ProjectStackedWidget::refreshModulesSlot(QStringList modules)
{
	modulesListWidget->clear();
	QString str;
	foreach(str, modules)
	{
		QListWidgetItem *item = new QListWidgetItem(modulesListWidget);
		item->setText(str);
	}
}

void ProjectStackedWidget::viewModuleSlot()
{
	QList<QListWidgetItem*> modules = modulesListWidget->selectedItems();
	if(!modules.isEmpty())
		emit viewModuleSignal(modules.at(0)->text());
}

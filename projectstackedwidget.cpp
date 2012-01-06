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
	addTemplateButton = new QPushButton(tr("Add Template"));
	addTemplateButton->setIcon(QIcon::fromTheme("list-add"));
	refreshTemplatesButton = new QPushButton(tr("Refresh Templates"));
	refreshTemplatesButton->setIcon(QIcon::fromTheme("view-refresh"));
	QPushButton *removeTemplateButton = new QPushButton(tr("Remove Template"));
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
	addFactButton = new QPushButton(tr("Add Fact"));
	addFactButton->setIcon(QIcon::fromTheme("list-add"));
	addFactByTemplateButton = new QPushButton(tr("Add Fact By Template"));
	addFactByTemplateButton->setIcon(QIcon::fromTheme("list-add"));
	refreshFactsButton = new QPushButton(tr("Refresh Facts"));
	refreshFactsButton->setIcon(QIcon::fromTheme("view-refresh"));
	QPushButton *removeFactButton = new QPushButton(tr("Remove Fact"));
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
	addDeffactButton = new QPushButton(tr("Add Facts List"));
	addDeffactButton->setIcon(QIcon::fromTheme("list-add"));
	refreshDeffactsButton = new QPushButton(tr("Refresh Facts Lists"));
	refreshDeffactsButton->setIcon(QIcon::fromTheme("view-refresh"));
	QPushButton *removeDeffactButton = new QPushButton(tr("Remove Facts List"));
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
	QPushButton *addRuleButton = new QPushButton(tr("Add Rule"));
	addRuleButton->setIcon(QIcon::fromTheme("list-add"));
	QPushButton *removeRuleButton = new QPushButton(tr("Remove Rule"));
	removeRuleButton->setIcon(QIcon::fromTheme("list-remove"));
	refreshRulesButton = new QPushButton(tr("Refresh Rules"));
	refreshRulesButton->setIcon(QIcon::fromTheme("view-refresh"));
	QHBoxLayout *rulesTopLayout = new QHBoxLayout;
	rulesTopLayout->addWidget(addRuleButton);
	rulesTopLayout->addWidget(removeRuleButton);
	rulesTopLayout->addWidget(refreshRulesButton);
	rulesTopLayout->addStretch();
	rulesLayout->addLayout(rulesTopLayout);
	rulesLayout->addWidget(rulesListWidget);
	rulesWidget->setLayout(rulesLayout);
	/*****************************Functions************************************/
	QGroupBox *functionsWidget = new QGroupBox(tr("Functions"));
	QVBoxLayout *functionsLayout = new QVBoxLayout;
	functionsListWidget = new QListWidget;
	QPushButton *addFunctionButton = new QPushButton(tr("Add Function"));
	addFunctionButton->setIcon(QIcon::fromTheme("list-add"));
	QPushButton *removeFunctionButton = new QPushButton(tr("Remove Function"));
	removeFunctionButton->setIcon(QIcon::fromTheme("list-remove"));
	refreshFunctionsButton = new QPushButton(tr("Refresh Functions"));
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
	QPushButton *addClassButton = new QPushButton(tr("Add Class"));
	addClassButton->setIcon(QIcon::fromTheme("list-add"));
	QPushButton *removeClassButton = new QPushButton(tr("Remove Class"));
	removeClassButton->setIcon(QIcon::fromTheme("list-remove"));
	refreshClassesButton = new QPushButton(tr("Refresh Classes"));
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
	this->addWidget(functionsWidget);
	this->addWidget(classesWidget);

	connect(duplicationButton, SIGNAL(toggled(bool)), this, SLOT(duplicationProxySlot(bool)));
	connect(removeTemplateButton, SIGNAL(clicked()), this, SLOT(removeTemplateSlot()));
	connect(removeFactButton, SIGNAL(clicked()), this, SLOT(removeFactSlot()));
	connect(removeDeffactButton, SIGNAL(clicked()), this, SLOT(removeDeffactsSlot()));
}

void ProjectStackedWidget::removeFactSlot()
{
	QList<QListWidgetItem*> facts = factsListWidget->selectedItems();
	if(!facts.isEmpty())
		emit removeFactSignal(facts.at(0)->data(Qt::UserRole).toInt(), false);
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

void ProjectStackedWidget::duplicationProxySlot(bool state)
{
	emit setFactDuplicationSignal(state, false);
}

void ProjectStackedWidget::removeTemplateSlot()
{
	QList<QListWidgetItem*> templates = templatesListWidget->selectedItems();
	if(!templates.isEmpty())
		emit removeTemplateSignal(templates.at(0)->text(), false);
}

void ProjectStackedWidget::removeDeffactsSlot()
{
	QList<QListWidgetItem*> deffacts = deffactsListWidget->selectedItems();
	if(!deffacts.isEmpty())
		emit removeFactsListSignal(deffacts.at(0)->text(), false);
}

void ProjectStackedWidget::clearSlot()
{
	templatesListWidget->clear();
	factsListWidget->clear();
	deffactsListWidget->clear();
	rulesListWidget->clear();
	functionsListWidget->clear();
	classesListWidget->clear();
}

#include "projectstackedwidget.h"
#include "addtemplatedialog.h"
#include <QInputDialog>
#include <QListWidgetItem>
#include <QList>
#include <QCheckBox>
#include <QDebug>

ProjectStackedWidget::ProjectStackedWidget(QWidget *parent) :
	QStackedWidget(parent)
{
	/**************************Templates***************************************/
	QGroupBox *templatesWidget = new QGroupBox(tr("Templates"));
	QVBoxLayout *templatesLayout = new QVBoxLayout;
	templatesListWidget = new QListWidget;
	QPushButton *addTemplateButton = new QPushButton(tr("Add Template"));
	QPushButton *removeTemplateButton = new QPushButton(tr("Remove Template"));
	QHBoxLayout *templatesBottomLayout = new QHBoxLayout;
	templatesBottomLayout->addStretch();
	templatesBottomLayout->addWidget(addTemplateButton);
	templatesBottomLayout->addWidget(removeTemplateButton);
	templatesLayout->addWidget(templatesListWidget);
	templatesLayout->addLayout(templatesBottomLayout);
	templatesWidget->setLayout(templatesLayout);
	/*****************************Facts****************************************/
	QGroupBox *factsWidget = new QGroupBox(tr("Facts"));
	QVBoxLayout *factsLayout = new QVBoxLayout;
	QPushButton *duplicationButton = new QPushButton(tr("Enable Duplication"));
	duplicationButton->setCheckable(true);
	factsListWidget = new QListWidget;
	QPushButton *addFactButton = new QPushButton(tr("Add Fact"));
	QPushButton *removeFactButton = new QPushButton(tr("Remove Fact"));
	QHBoxLayout *factsBottomLayout = new QHBoxLayout;
	factsBottomLayout->addWidget(duplicationButton);
	factsBottomLayout->addStretch();
	factsBottomLayout->addWidget(addFactButton);
	factsBottomLayout->addWidget(removeFactButton);
	factsLayout->addWidget(factsListWidget);
	factsLayout->addLayout(factsBottomLayout);
	factsWidget->setLayout(factsLayout);
	connect(addFactButton, SIGNAL(clicked()), this, SLOT(addFactSlot()));
	/*****************************Rules****************************************/
	QGroupBox *rulesWidget = new QGroupBox(tr("Rules"));
	QVBoxLayout *rulesLayout = new QVBoxLayout;
	rulesListWidget = new QListWidget;
	QPushButton *addRuleButton = new QPushButton(tr("Add Rule"));
	QPushButton *removeRuleButton = new QPushButton(tr("Remove Rule"));
	QHBoxLayout *rulesBottomLayout = new QHBoxLayout;
	rulesBottomLayout->addStretch();
	rulesBottomLayout->addWidget(addRuleButton);
	rulesBottomLayout->addWidget(removeRuleButton);
	rulesLayout->addWidget(rulesListWidget);
	rulesLayout->addLayout(rulesBottomLayout);
	rulesWidget->setLayout(rulesLayout);
	/*****************************Functions************************************/
	QGroupBox *functionsWidget = new QGroupBox(tr("Functions"));
	QVBoxLayout *functionsLayout = new QVBoxLayout;
	functionsListWidget = new QListWidget;
	QPushButton *addFunctionButton = new QPushButton(tr("Add Function"));
	QPushButton *removeFunctionButton = new QPushButton(tr("Remove Function"));
	QHBoxLayout *functionsBottomLayout = new QHBoxLayout;
	functionsBottomLayout->addStretch();
	functionsBottomLayout->addWidget(addFunctionButton);
	functionsBottomLayout->addWidget(removeFunctionButton);
	functionsLayout->addWidget(functionsListWidget);
	functionsLayout->addLayout(functionsBottomLayout);
	functionsWidget->setLayout(functionsLayout);
	/*****************************Classes**************************************/
	QGroupBox *classesWidget = new QGroupBox(tr("Classes"));
	QVBoxLayout *classesLayout = new QVBoxLayout;
	classesListWidget = new QListWidget;
	QPushButton *addClassButton = new QPushButton(tr("Add Class"));
	QPushButton *removeClassButton = new QPushButton(tr("Remove Class"));
	QHBoxLayout *classesBottomLayout = new QHBoxLayout;
	classesBottomLayout->addStretch();
	classesBottomLayout->addWidget(addClassButton);
	classesBottomLayout->addWidget(removeClassButton);
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
	connect(addTemplateButton, SIGNAL(clicked()), this, SLOT(addTemplateSlot()));
	connect(removeTemplateButton, SIGNAL(clicked()), this, SLOT(removeTemplateSlot()));
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

void ProjectStackedWidget::refreshFacts(QStringList list)
{
	factsListWidget->clear();
	//QStringList list = facts.split("\n");
	//list.removeLast();
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

void ProjectStackedWidget::addTemplateSlot()
{
	bool ok;
	int i = QInputDialog::getInt(this, tr("Slots count"), tr("Enter slots count:"), 1, 1, 100, 1, &ok);
	if (ok)
	{
		addTemplateDialog dialog(this,i);
		if(dialog.exec() == QDialog::Accepted)
		{
			QString name = dialog.nameLineEdit->text();
			if(name.isEmpty())
				return;
			QList<QCheckBox *> checkBoxList = dialog.checkBoxList;
			QList<QLineEdit *> lineEditList = dialog.lineEditList;
			QList<slotsPair> slotsList;
			for(int i=0; i<lineEditList.count();i++)
			{
				slotsPair pair;
				pair.first = checkBoxList.at(i)->checkState();
				pair.second = lineEditList.at(i)->text();
				if(pair.second.isEmpty())
					return;
				slotsList.append(pair);
			}
			emit addTemplateSignal(name, slotsList);
		}
	}
}

void ProjectStackedWidget::removeTemplateSlot()
{
	QList<QListWidgetItem*> templates = templatesListWidget->selectedItems();
	if(!templates.isEmpty())
		emit removeTemplateSignal(templates.at(0)->text(), false);
}

void ProjectStackedWidget::clearSlot()
{
	templatesListWidget->clear();
	factsListWidget->clear();
	rulesListWidget->clear();
	functionsListWidget->clear();
	classesListWidget->clear();
}

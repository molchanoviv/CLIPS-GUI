#ifndef PROJECTSTACKEDWIDGET_H
#define PROJECTSTACKEDWIDGET_H

#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QGroupBox>
#include <QLabel>
#include <QWidget>
#include <QStringList>

typedef QPair<bool, QString> slotsPair;

class ProjectStackedWidget : public QStackedWidget
{
	Q_OBJECT
public:
	explicit ProjectStackedWidget(QWidget *parent = 0);
	//Templates
	QListWidget *templatesListWidget;
	QPushButton *addTemplateButton;
	QPushButton *refreshTemplatesButton;
	QPushButton *viewTemplatePushButton;
	//Facts
	QListWidget *factsListWidget;
	QPushButton *addFactByTemplateButton;
	QPushButton *addFactButton;
	QPushButton *refreshFactsButton;
	QPushButton *duplicationButton;
	//Facts List
	QListWidget *deffactsListWidget;
	QPushButton *addDeffactButton;
	QPushButton *refreshDeffactsButton;
	QPushButton *viewDeffactPushButton;
	//Rules
	QListWidget *rulesListWidget;
	QPushButton *addRuleButton;
	QPushButton *refreshRulesButton;
	QPushButton *viewRulePushButton;
	QPushButton *setBreakpointPushButton;
	QPushButton *removeBreakpointPushButton;
	//Agenda
	QListWidget *activationsListWidget;
	QPushButton *refreshActivationsButton;
	QPushButton *runButton;
	QPushButton *setActivationSaliencePushButton;
	QPushButton *setStrategyPushButton;
	//Globals
	QListWidget *globalsListWidget;
	QPushButton *addGlobalButton;
	QPushButton *refreshGlobalsButton;
	QPushButton *viewGlobalPushButton;
	//Functions
	QListWidget *functionsListWidget;
	QPushButton *addFunctionButton;
	QPushButton *refreshFunctionsButton;
	QPushButton *viewFunctionPushButton;
	//Generics
	QListWidget *genericListWidget;
	QPushButton *addGenericButton;
	QPushButton *refreshGenericButton;
	QPushButton *viewGenericPushButton;
	//Methods
	QListWidget *methodsListWidget;
	QPushButton *addMethodButton;
	QPushButton *refreshMethodsButton;
	QPushButton *viewMethodPushButton;
	//Classes
	QListWidget *classesListWidget;
	QPushButton *addClassButton;
	QPushButton *refreshClassesButton;
	//Message Handlers
	/*****/
	//Modules
	/*****/

signals:
	//Templates
	void removeTemplateSignal(QString);
	void viewTemplateSignal(QString);
	//Facts
	void removeFactSignal(int);
	//Facts List
	void removeFactsListSignal(QString);
	void viewFactsListSignal(QString);
	//Rules
	void removeRuleSignal(QString);
	void viewRuleSignal(QString);
	void setBreakpointSignal(QString);
	void removeBreakpointSignal(QString);
	//Agenda
	void removeActivationSignal(QString);
	//Globals
	void removeGlobalSignal(QString);
	void viewGlobalSignal(QString);
	//Function
	void removeFunctionSignal(QString);
	void viewFunctionSignal(QString);
	//Generic Functions
	void removeGenericSignal(QString);
	void viewGenericSignal(QString);
	//Methods
	void removeMethodSignal(QString, int);
	void viewMethodSignal(QString, int);
	//Classes
	/*****/
	//Message Handlers
	/*****/
	//Modules
	/*****/

public slots:
	void clearSlot();
	//Templates
	void refreshTemplates(QStringList);
	void viewTemplateSlot();
	void removeTemplateSlot();
	//Facts
	void refreshFacts(QStringList);
	void removeFactSlot();
	//Facts Lists
	void refreshDeffacts(QStringList);
	void viewFactsListSlot();
	void removeDeffactsSlot();
	//Rules
	void refreshRules(QStringList);
	void viewRuleSlot();
	void removeDefruleSlot();
	void setBreakpointSlot();
	void removeBreakpointSlot();
	//Agenda
	void refreshActivations(QStringList);
	void removeActivationSlot();
	//Globals
	void refreshGlobals(QStringList);
	void viewGlobalSlot();
	void removeGlobalSlot();
	//Functions
	void refreshFunctions(QStringList);
	void viewFunctionSlot();
	void removeFunctionSlot();
	//Generic Functions
	void refreshGeneric(QStringList);
	void viewGenericSlot();
	void removeGenericSlot();
	//Methods
	void refreshMethods(QHash<QString, int>);
	void viewMethodSlot();
	void removeMethodSlot();
	//Classes
	/*****/
	//Message Handlers
	/*****/
	//Modules
	/*****/
};

#endif // PROJECTSTACKEDWIDGET_H

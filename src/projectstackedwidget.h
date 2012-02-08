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

class QAction;

typedef QPair<bool, QString> slotsPair;

class ProjectStackedWidget : public QStackedWidget
{
	Q_OBJECT
public:
	explicit ProjectStackedWidget(QWidget *parent = 0);
	//Templates
	QListWidget *templatesListWidget;
	QPushButton *addTemplatePushButton;
	QPushButton *refreshTemplatesPushButton;
	QPushButton *viewTemplatePushButton;
	//Facts
	QListWidget *factsListWidget;
	QPushButton *addFactByTemplatePushButton;
	QPushButton *addFactPushButton;
	QPushButton *refreshFactsPushButton;
	QPushButton *duplicationPushButton;
	//Facts List
	QListWidget *deffactsListWidget;
	QPushButton *addDeffactPushButton;
	QPushButton *refreshDeffactsPushButton;
	QPushButton *viewDeffactPushButton;
	//Rules
	QListWidget *rulesListWidget;
	QPushButton *addRulePushButton;
	QPushButton *refreshRulesPushButton;
	QPushButton *viewRulePushButton;
	QPushButton *setBreakpointPushButton;
	QPushButton *removeBreakpointPushButton;
	//Agenda
	QListWidget *activationsListWidget;
	QPushButton *refreshActivationsPushButton;
	QPushButton *runPushButton;
	QPushButton *setActivationSaliencePushButton;
	QPushButton *setStrategyPushButton;
	//Globals
	QListWidget *globalsListWidget;
	QPushButton *addGlobalPushButton;
	QPushButton *refreshGlobalsPushButton;
	QPushButton *viewGlobalPushButton;
	//Functions
	QListWidget *functionsListWidget;
	QPushButton *addFunctionPushButton;
	QPushButton *refreshFunctionsPushButton;
	QPushButton *viewFunctionPushButton;
	//Generics
	QListWidget *genericListWidget;
	QPushButton *addGenericPushButton;
	QPushButton *refreshGenericPushButton;
	QPushButton *viewGenericPushButton;
	//Methods
	QListWidget *methodsListWidget;
	QPushButton *addMethodPushButton;
	QPushButton *refreshMethodsPushButton;
	QPushButton *viewMethodPushButton;
	//Classes
	QListWidget *classesListWidget;
	QPushButton *addClassPushButton;
	QPushButton *refreshClassesPushButton;
	QPushButton *defaultsModePushButton;
	QPushButton *viewClassPushButton;
	QPushButton *classInfoPushButton;
	QAction *metaInformationAction;
	QAction *subClassesAction;
	QAction *superClassesAction;
	//Message Handlers
	QListWidget *messageHandlersListWidget;
	QPushButton *addMessageHandlerPushButton;
	QPushButton *refreshMessageHandlersPushButton;
	QPushButton *viewMessageHandlerPushButton;
	//Instances
	QListWidget *instancesListWidget;
	QPushButton *addInstancePushButton;
	QPushButton *refreshInstancesPushButton;
	QPushButton *viewInstancePushButton;
	//Modules
	QListWidget *modulesListWidget;
	QPushButton *addModulePushButton;
	QPushButton *refreshModulesPushButton;
	QPushButton *viewModulePushButton;
	QPushButton *currentModulePushButton;

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
	void removeClassSignal(QString);
	void viewClassSignal(QString);
	void metaInformationSignal(QString);
	void subClassesSignal(QString);
	void superClassesSignal(QString);
	//Message Handlers
	void removeMessageHandlerSignal(QString, unsigned int);
	void viewMessageHandlerSignal(QString, unsigned int);
	//Instances
	void removeInstanceSignal(QString);
	void viewInstanceSignal(QString);
	//Modules
	void viewModuleSignal(QString);

public slots:
	void clearSlot();
	//Templates
	void refreshTemplates(QStringList);
	void viewTemplateSlot();
	void removeTemplateSlot();
	//Facts
	void refreshFacts(QStringList);
	void removeFactSlot();
	void restoreDuplicationState(bool);
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
	void refreshClasses(QStringList);
	void viewClassSlot();
	void removeClassSlot();
	void metaInformationSlot();
	void subClassesSlot();
	void superClassesSlot();
	//Message Handlers
	void refreshMessageHandlers(QHash<QString, unsigned int>);
	void removeMessageHandlerSlot();
	void viewMessageHandlerSlot();
	//Instances
	void refreshInstancesSlot(QStringList);
	void removeInstanceSlot();
	void viewInstanceSlot();
	//Modules
	void refreshModulesSlot(QStringList);
	void viewModuleSlot();
};

#endif // PROJECTSTACKEDWIDGET_H

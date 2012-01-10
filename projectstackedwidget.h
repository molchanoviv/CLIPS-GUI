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
	QListWidget *templatesListWidget;
	QListWidget *factsListWidget;
	QListWidget *deffactsListWidget;
	QListWidget *rulesListWidget;
	QListWidget *activationsListWidget;
	QListWidget *globalsListWidget;
	QListWidget *functionsListWidget;
	QListWidget *genericListWidget;
	QListWidget *classesListWidget;
	QPushButton *addFactButton;
	QPushButton *addDeffactButton;
	QPushButton *addFactByTemplateButton;
	QPushButton *addTemplateButton;
	QPushButton *addRuleButton;
	QPushButton *addGlobalButton;
	QPushButton *addFunctionButton;
	QPushButton *addGenericButton;
	QPushButton *addClassButton;
	QPushButton *refreshTemplatesButton;
	QPushButton *refreshFactsButton;
	QPushButton *refreshDeffactsButton;
	QPushButton *refreshRulesButton;
	QPushButton *refreshActivationsButton;
	QPushButton *refreshGlobalsButton;
	QPushButton *refreshFunctionsButton;
	QPushButton *refreshGenericButton;
	QPushButton *refreshClassesButton;
	QPushButton *setBreakpointPushButton;
	QPushButton *removeBreakpointPushButton;
	QPushButton *runButton;
	QPushButton *setActivationSaliencePushButton;
	QPushButton *setStrategyPushButton;
	QPushButton *watchGlobalPushButton;
	QPushButton *watchFunctionPushButton;
	QPushButton *watchGenericPushButton;

private:


signals:
	void setFactDuplicationSignal(bool, bool);
	void removeFactSignal(int, bool);
	void removeTemplateSignal(QString, bool);
	void removeFactsListSignal(QString, bool);
	void removeRuleSignal(QString, bool);
	void removeActivationSignal(QString, bool);
	void removeGlobalSignal(QString, bool);
	void removeFunctionSignal(QString, bool);
	void removeGenericSignal(QString, bool);
	void setBreakpointSignal(QString, bool);
	void removeBreakpointSignal(QString, bool);
	void watchGlobalSignal(QString);
	void watchFunctionSignal(QString);
	void watchGenericSignal(QString);

public slots:
	void refreshTemplates(QStringList);
	void refreshFacts(QStringList);
	void refreshDeffacts(QStringList);
	void refreshRules(QStringList);
	void refreshActivations(QStringList);
	void refreshGlobals(QStringList);
	void refreshFunctions(QStringList);
	void refreshGeneric(QStringList);
	void duplicationProxySlot(bool);
	void watchGlobalSlot();
	void watchFunctionSlot();
	void watchGenericSlot();
	void setBreakpointSlot();
	void removeBreakpointSlot();
	void removeTemplateSlot();
	void removeFactSlot();
	void removeDeffactsSlot();
	void removeDefruleSlot();
	void removeActivationSlot();
	void removeGlobalSlot();
	void removeFunctionSlot();
	void removeGenericSlot();
	void clearSlot();

};

#endif // PROJECTSTACKEDWIDGET_H

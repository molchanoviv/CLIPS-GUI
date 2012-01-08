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
	QListWidget *functionsListWidget;
	QListWidget *classesListWidget;
	QPushButton *addFactButton;
	QPushButton *addDeffactButton;
	QPushButton *addFactByTemplateButton;
	QPushButton *addTemplateButton;
	QPushButton *addRuleButton;
	QPushButton *addFunctionButton;
	QPushButton *addClassButton;
	QPushButton *refreshTemplatesButton;
	QPushButton *refreshFactsButton;
	QPushButton *refreshDeffactsButton;
	QPushButton *refreshRulesButton;
	QPushButton *refreshActivationsButton;
	QPushButton *refreshFunctionsButton;
	QPushButton *refreshClassesButton;
	QPushButton *setBreakpointPushButton;
	QPushButton *removeBreakpointPushButton;
	QPushButton *runButton;
	QPushButton *setActivationSaliencePushButton;
	QPushButton *setStrategyPushButton;

private:


signals:
	void setFactDuplicationSignal(bool, bool);
	void removeFactSignal(int, bool);
	void removeTemplateSignal(QString, bool);
	void removeFactsListSignal(QString, bool);
	void removeRuleSignal(QString, bool);
	void setBreakpointSignal(QString, bool);
	void removeBreakpointSignal(QString, bool);
	void removeActivationSignal(QString, bool);

public slots:
	void refreshTemplates(QStringList);
	void refreshFacts(QStringList);
	void refreshDeffacts(QStringList);
	void refreshRules(QStringList);
	void refreshActivations(QStringList);
	void duplicationProxySlot(bool);
	void setBreakpointSlot();
	void removeBreakpointSlot();
	void removeTemplateSlot();
	void removeFactSlot();
	void removeDeffactsSlot();
	void removeDefruleSlot();
	void removeActivationSlot();
	void clearSlot();

};

#endif // PROJECTSTACKEDWIDGET_H

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
	QListWidget *functionsListWidget;
	QListWidget *classesListWidget;
	QPushButton *addFactButton;
	QPushButton *addDeffactButton;
	QPushButton *addFactByTemplateButton;
	QPushButton *addTemplateButton;
	QPushButton *refreshTemplatesButton;
	QPushButton *refreshFactsButton;
	QPushButton *refreshDeffactsButton;
	QPushButton *refreshRulesButton;
	QPushButton *refreshFunctionsButton;
	QPushButton *refreshClassesButton;

private:


signals:
	void setFactDuplicationSignal(bool, bool);
	void removeFactSignal(int, bool);
	void removeTemplateSignal(QString, bool);
	void removeFactsListSignal(QString, bool);

public slots:
	void refreshTemplates(QStringList);
	void refreshFacts(QStringList);
	void refreshDeffacts(QStringList);
	void duplicationProxySlot(bool);
	void removeTemplateSlot();
	void removeFactSlot();
	void removeDeffactsSlot();
	void clearSlot();

};

#endif // PROJECTSTACKEDWIDGET_H

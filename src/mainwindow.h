#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "clipsclass.h"
#include "projectstackedwidget.h"
#include <QMainWindow>
#include <QSplitter>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QCloseEvent>
#include <QList>
#include <QStackedWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QPair>
#include <QString>

namespace Ui {
	class MainWindow;
}

class consoleClass;

class MainWindow : public QMainWindow
{
	Q_OBJECT
	typedef QPair<QString, QString> StringPair;
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;
	CLIPSClass *clips;
	void closeEvent(QCloseEvent*);
	void writeSettings();
	void readSettings();
	QSplitter *splitter;
	QSplitter *centerSplitter;
	QTreeWidget *projectsTreeWidget;
	ProjectStackedWidget *projectWidget;
	int removeFolder(QDir);
	void disableWidgets(bool);
	void createProjectTreeWidgetItems(QString);
	StringPair projectPair;
	bool unsaved;
	void redrawTitle();
	consoleClass *console;


private slots:
	void refreshAll();
	void treeWidgetItemClicked(QTreeWidgetItem*,int);
	void newProject();
	void openProject();
	void closeProject();
	void removeProject();
	void saveProject();
	void saveProjectAs();
	void dataChangedSlot();
	//Templates
	void addTemplateSlot();
	void refreshTemplatesSlot();
	void viewTemplateSlot(QString);
	//Facts
	void addFactSlot();
	void addFactByTemplateSlot();
	void refreshFactsSlot();
	//Facts Lists
	void addFactsListSlot();
	void refreshDeffactsSlot();
	void viewDeffactsSlot(QString);
	//Rules
	void addRuleSlot();
	void refreshRulesSlot();
	void viewRuleSlot(QString);
	//Agenda
	void refreshActivationsSlot();
	void setActivationSalienceSlot();
	void setConflictStrategySlot();
	//Globals
	void addGlobalSlot();
	void refreshGlobalsSlot();
	void viewGlobalSlot(QString);
	//Functions
	void addFunctionSlot();
	void refreshFunctionsSlot();
	void viewFunctionSlot(QString);
	//Generic Functions
	void addGenericSlot();
	void refreshGenericSlot();
	void viewGenericSlot(QString);
	//Methods
	void addMethodSlot();
	void refreshMethodsSlot();
	void viewMethodSlot(QString, int);
	//Classes
	void refreshClassesSlot();
	//Message Handlers
	/*****/
	//Modules
	/*****/

signals:
	void treeWidgetItemClickedSignal(int);
	void addTemplateSignal(QString, QList<slotsPair>);
	void addFactSignal(QString);
	void addFactsListSignal(QString, QStringList);
	void addRuleSignal(QString, QString, QString, QStringList, QStringList);
	void setActivationSalienceSignal(QString, int);
	void setStrategySignal(int);
	void addGlobalSignal(QString, QHash<QString, QString>);
	void addFunctionSignal(QString, QString, QString, QString, QString);
	void addGenericSignal(QString);
	void addMethodSignal(QString, QString, QString, QString, QString, QString);
};

#endif // MAINWINDOW_H

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
	void refreshAll(bool);
	void createProjectTreeWidgetItems(QString);
	StringPair projectPair;


private slots:
	void treeWidgetItemClicked(QTreeWidgetItem*,int);
	void newProject();
	void openProject();
	void closeProject();
	void removeProject();
	void saveProject();
	void saveProjectAs();
	void addTemplateSlot();
	void addFactSlot();
	void addFactByTemplateSlot();
	void addFactsListSlot();
	void addRuleSlot();
	void addGlobalSlot();
	void addFunctionSlot();
	void addGenericSlot();
	void refreshTemplatesSlot();
	void refreshFactsSlot();
	void refreshDeffactsSlot();
	void refreshRulesSlot();
	void refreshActivationsSlot();
	void refreshGlobalsSlot();
	void refreshFunctionsSlot();
	void refreshGenericSlot();
	void refreshClassesSlot();
	void setActivationSalienceSlot();
	void setConflictStrategySlot();
	void watchGlobalSlot(QString);
	void watchFunctionSlot(QString);
	void watchGenericSlot(QString);

signals:
	void treeWidgetItemClickedSignal(int);
	void addFactSignal(QString, bool);
	void addFactsListSignal(QString, QStringList);
	void addTemplateSignal(QString, QList<slotsPair>);
	void addRuleSignal(QString, QString, QString, QStringList, QStringList);
	void setActivationSalienceSignal(QString, int, bool);
	void setStrategySignal(int);
	void addGlobalSignal(QString, QHash<QString, QString>);
	void addFunctionSignal(QString, QString, QString, QString, QString);
	void addGenericSignal(QString);
};

#endif // MAINWINDOW_H

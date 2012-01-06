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
	StringPair projectPair;


private slots:
	void treeWidgetItemClicked(QTreeWidgetItem*,int);
	void newProject();
	void openProject();
	void closeProject();
	void removeProject();
	void saveProject();
	void saveProjectAs();
	void addFactSlot();
	void refreshTemplatesSlot();
	void refreshFactsSlot();
	void refreshDeffactsSlot();
	void refreshRulesSlot();
	void refreshFunctionsSlot();
	void refreshClassesSlot();
	void addFactByTemplateSlot();
	void addFactsListSlot();
	void addTemplateSlot();

signals:
	void treeWidgetItemClickedSignal(int);
	void addFactSignal(QString, bool);
	void addFactsListSignal(QString, QStringList);
	void addTemplateSignal(QString, QList<slotsPair>);
};

#endif // MAINWINDOW_H

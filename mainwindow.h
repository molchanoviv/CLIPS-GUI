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
	int projectIndex;
	QList<StringPair> projectsList;


private slots:
	void treeWidgetItemClicked(QTreeWidgetItem*,int);

	void newProject();
	void openProject();
	void closeProject();
	void removeProject();
	void changeProjectSlot(int);

signals:
	void treeWidgetItemClickedSignal(int);
	void changeProjectSignal(int);
};

#endif // MAINWINDOW_H

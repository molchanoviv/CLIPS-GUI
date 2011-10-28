#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "consoleclass.h"
#include "newprojectdialog.h"
#include <QToolBar>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	ui->actionShow_Hide_console->setIcon(QIcon::fromTheme("terminal"));
	ui->actionQuit->setIcon(QIcon::fromTheme("exit"));
	ui->mainToolBar->addAction(ui->actionShow_Hide_console);
	ui->mainToolBar->addAction(ui->actionQuit);
	ui->actionNew->setIcon(QIcon::fromTheme("filenew"));
	ui->actionOpen->setIcon(QIcon::fromTheme("fileopen"));
	ui->actionRemove->setIcon(QIcon::fromTheme("remove"));
	ui->actionClose->setIcon(QIcon::fromTheme("document-close"));
	QToolBar *projectToolbar = new QToolBar;
	projectToolbar->addAction(ui->actionNew);
	projectToolbar->addAction(ui->actionOpen);
	projectToolbar->addAction(ui->actionClose);
	projectToolbar->addAction(ui->actionRemove);
	addToolBar(projectToolbar);
	consoleClass *console = new consoleClass;
	console->hide();
	ui->actionShow_Hide_console->setCheckable(true);
	connect(ui->actionShow_Hide_console, SIGNAL(toggled(bool)), console, SLOT(setShown(bool)));
	projectsTreeWidget = new QTreeWidget;
	projectsTreeWidget->setHeaderLabel("CLIPS-GUI");
	projectWidget = new ProjectStackedWidget;
	centerSplitter = new QSplitter(this);
	centerSplitter->setOrientation(Qt::Horizontal);
	centerSplitter->addWidget(projectsTreeWidget);
	centerSplitter->addWidget(projectWidget);
	splitter = new QSplitter(this);
	splitter->setOrientation(Qt::Vertical);
	setCentralWidget(splitter);
	splitter->addWidget(centerSplitter);
	splitter->addWidget(console);
	clips = new CLIPSClass;
	connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newProject()));
	connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openProject()));
	connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(closeProject()));
	connect(ui->actionRemove, SIGNAL(triggered()), this, SLOT(removeProject()));
	connect(projectsTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(treeWidgetItemClicked(QTreeWidgetItem*,int)));
	connect(projectWidget, SIGNAL(addFactSignal(QString,bool)), clips, SLOT(assertStringSlot(QString,bool)));
	connect(projectWidget, SIGNAL(setFactDuplicationSignal(bool,bool)), clips, SLOT(setFactDuplicationSlot(bool,bool)));
	connect(this, SIGNAL(treeWidgetItemClickedSignal(int)), projectWidget, SLOT(setCurrentIndex(int)));
	connect(this, SIGNAL(changeProjectSignal(int)), this, SLOT(changeProjectSlot(int)));
	connect(console, SIGNAL(assertStringSignal(QString,bool)), clips, SLOT(assertStringSlot(QString,bool)));
	connect(console, SIGNAL(factsSignal(bool)), clips, SLOT(factsSlot(bool)));
	connect(console, SIGNAL(retractSignal(int,bool)), clips, SLOT(retractSlot(int,bool)));
	connect(console, SIGNAL(saveFactsSignal(QString)), clips, SLOT(saveFactsSlot(QString)));
	connect(console, SIGNAL(setFactDuplicationSignal(bool,bool)), clips, SLOT(setFactDuplicationSlot(bool,bool)));
	connect(clips, SIGNAL(factsChangedSignal(QString)), projectWidget, SLOT(refreshFacts(QString)));
	connect(clips, SIGNAL(outputSignal(QString)), console, SLOT(output(QString)));
	readSettings();
	projectIndex = 0;
}


void MainWindow::newProject()
{
	NewProjectDialog dialog(this);
	if(dialog.exec() == QDialog::Accepted)
	{
		QString projectName = dialog.projectNameLineEdit->text();
		QString projectPath = dialog.projectPathLineEdit->text();
		QTreeWidgetItem *item = new QTreeWidgetItem();
		item->setText(0, projectName);
		item->setText(1, QString::number(projectsTreeWidget->topLevelItemCount()));
		QTreeWidgetItem *templatesItem = new QTreeWidgetItem();
		templatesItem->setText(0, tr("Templates"));
		QTreeWidgetItem *factsItem = new QTreeWidgetItem();
		factsItem->setText(0, tr("Facts"));
		QTreeWidgetItem *rulesItem = new QTreeWidgetItem();
		rulesItem->setText(0, tr("Rules"));
		QTreeWidgetItem *functionsItem = new QTreeWidgetItem();
		functionsItem->setText(0, tr("Functions"));
		QTreeWidgetItem *classesItem = new QTreeWidgetItem();
		classesItem->setText(0, tr("Classes"));
		item->addChild(templatesItem);
		item->addChild(factsItem);
		item->addChild(rulesItem);
		item->addChild(functionsItem);
		item->addChild(classesItem);
		projectsTreeWidget->insertTopLevelItem(0, item);
		item->setExpanded(1);
		projectsTreeWidget->clearSelection();
		QDir dir(projectPath);
		dir.mkdir(projectName);
		QFile file(projectPath+"/"+projectName+"/"+projectName+".clp.prj");
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
			qDebug()<<"can not open file";
		QTextStream out(&file);
		out << "[project]\n";
		out<<"name="+projectName+"\n";
		file.close();
		QPair<QString, QString> pair;
		pair.first = projectName;
		pair.second = projectPath+"/"+projectName+"/"+projectName;
		projectsList<<pair;
		projectWidget->refreshFacts(clips->factsSlot(false));
	}

}

void MainWindow::openProject()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Project"), QDir::homePath(), tr("GLIPS-GUI Projects (*.clp.prj);;All files (*.*)"));
	if(!fileName.isEmpty())
	{
		QSettings settings(fileName, QSettings::IniFormat);
		settings.beginGroup("project");
		QString projectName = settings.value("name").toString();
		settings.endGroup();
		QTreeWidgetItem *item = new QTreeWidgetItem();
		item->setText(0, projectName);
		item->setText(1, QString::number(projectsTreeWidget->topLevelItemCount()));
		QTreeWidgetItem *templatesItem = new QTreeWidgetItem();
		templatesItem->setText(0, tr("Templates"));
		QTreeWidgetItem *factsItem = new QTreeWidgetItem();
		factsItem->setText(0, tr("Facts"));
		QTreeWidgetItem *rulesItem = new QTreeWidgetItem();
		rulesItem->setText(0, tr("Rules"));
		QTreeWidgetItem *functionsItem = new QTreeWidgetItem();
		functionsItem->setText(0, tr("Functions"));
		QTreeWidgetItem *classesItem = new QTreeWidgetItem();
		classesItem->setText(0, tr("Classes"));
		item->addChild(templatesItem);
		item->addChild(factsItem);
		item->addChild(rulesItem);
		item->addChild(functionsItem);
		item->addChild(classesItem);
		projectsTreeWidget->insertTopLevelItem(0, item);
		item->setExpanded(1);
		projectsTreeWidget->clearSelection();
		StringPair pair;
		pair.first = projectName;
		pair.second = fileName.remove(fileName.lastIndexOf(QRegExp("(/|\\\\)")), fileName.length());
		projectsList<<pair;
		int newIndex = projectsList.count()-1;
		if(newIndex>0)
		{
			StringPair oldPair = projectsList.at(projectIndex);
			clips->saveFactsSlot(oldPair.second+"/facts.clp");
			clips->clearSlot();
			clips->loadFactsSlot(pair.second+"/facts.clp");
			projectIndex = newIndex;
		}
		else
		{
			clips->clearSlot();
			clips->loadFactsSlot(pair.second+"/facts.clp");
		}
		projectWidget->refreshFacts(clips->factsSlot(false));
	}
}

void MainWindow::closeProject()
{
	int index = 0;
	if(!projectsTreeWidget->selectedItems().isEmpty())
	{
		QTreeWidgetItem *item = projectsTreeWidget->selectedItems().first();
		if(!item->parent())
			index = projectsTreeWidget->indexOfTopLevelItem(item);
		else
			index = projectsTreeWidget->indexOfTopLevelItem(item->parent());
		projectsTreeWidget->takeTopLevelItem(index);
		projectsList.removeAt(index);
	}
	else
	{
		QMessageBox::warning(this, tr("No selected projects"),
					tr("No selected projects. Select project in projects tree and retry close it"),
					QMessageBox::Ok, QMessageBox::Ok);
	}
}

void MainWindow::removeProject()
{
	int index = 0;
	if(!projectsTreeWidget->selectedItems().isEmpty())
	{
		QString path = "";
		QTreeWidgetItem *item = projectsTreeWidget->selectedItems().first();
		if(!item->parent())
		{
			path = item->text(2);
			index = projectsTreeWidget->indexOfTopLevelItem(item);
		}
		else
		{
			path = item->parent()->text(2);
			index = projectsTreeWidget->indexOfTopLevelItem(item->parent());
		}
		projectsTreeWidget->takeTopLevelItem(index);
		projectsList.removeAt(index);
		removeFolder(QDir(path));
	}
	else
	{
		QMessageBox::warning(this, tr("No selected projects"),
					tr("No selected projects. Select project in projects tree and retry remove it"),
					QMessageBox::Ok, QMessageBox::Ok);
	}
}

void MainWindow::changeProjectSlot(int newIndex)
{
	if(newIndex!=projectIndex)
	{
		StringPair oldPair = projectsList.at(projectIndex);
		StringPair newPair = projectsList.at(newIndex);
		clips->saveFactsSlot(oldPair.second+"/facts.clp");
		clips->clearSlot();
		clips->loadFactsSlot(newPair.second+"/facts.clp");
		projectIndex = newIndex;
	}
}

int MainWindow::removeFolder(QDir dir)
{
	int res = 0;
	QStringList lstDirs = dir.entryList(QDir::Dirs|QDir::AllDirs|QDir::NoDotAndDotDot);
	QStringList lstFiles = dir.entryList(QDir::Files);
	foreach (QString entry, lstFiles)
	{
		QString entryAbsPath = dir.absolutePath() + "/" + entry;
		QFile::remove(entryAbsPath);
	}
	foreach (QString entry, lstDirs)
	{
		QString entryAbsPath = dir.absolutePath() + "/" + entry;
		removeFolder(QDir(entryAbsPath));
	}
	if (!QDir().rmdir(dir.absolutePath()))
		res = 1;
	return res;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	Q_UNUSED(event);
	StringPair pair = projectsList.at(projectIndex);
	clips->saveFactsSlot(pair.second+"/facts.clp");
	writeSettings();
};

void MainWindow::writeSettings()
{
	QSettings settings("CLIPS-GUI", "clipsgui");
	settings.beginGroup("/MainWindow");
	settings.setValue("/geometry", this->saveGeometry());
	settings.setValue( "/state", saveState() );
	settings.setValue("/splitterSizes", splitter->saveState());
	settings.setValue("/centerSplitterSizes", centerSplitter->saveState());
	settings.setValue("/consoleState", ui->actionShow_Hide_console->isChecked());
	settings.endGroup();
	settings.deleteLater();
};

void MainWindow::readSettings()
{
	QSettings settings("CLIPS-GUI", "clipsgui");
	settings.beginGroup("/MainWindow");
	this->restoreGeometry(settings.value("/geometry").toByteArray());
	restoreState( settings.value("/state" ).toByteArray() );
	splitter->restoreState(settings.value("/splitterSizes").toByteArray());
	centerSplitter->restoreState(settings.value("/centerSplitterSizes").toByteArray());
	ui->actionShow_Hide_console->setChecked(settings.value("/consoleState").toBool());
	settings.endGroup();
	settings.deleteLater();

};

void MainWindow::treeWidgetItemClicked(QTreeWidgetItem* item, int column)
{
	bool ok;
	Q_UNUSED(column);
	if(!item->parent())
	{
		emit changeProjectSignal(item->text(1).toInt(&ok, 10));
		emit treeWidgetItemClickedSignal(0);
	}
	else
	{
		emit changeProjectSignal(item->parent()->text(1).toInt(&ok, 10));
		emit treeWidgetItemClickedSignal(item->parent()->indexOfChild(item));
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "consoleclass.h"
#include "addtemplatedialog.h"
#include "newprojectdialog.h"
#include "addfactbytemplatedialog.h"
#include <QToolBar>
#include <QInputDialog>
#include <QCheckBox>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	ui->actionShow_Hide_console->setIcon(QIcon::fromTheme("utilities-terminal"));
	ui->actionQuit->setIcon(QIcon::fromTheme("dialog-close"));
	ui->mainToolBar->addAction(ui->actionShow_Hide_console);
	ui->mainToolBar->addAction(ui->actionQuit);
	ui->actionNew->setIcon(QIcon::fromTheme("document-new"));
	ui->actionOpen->setIcon(QIcon::fromTheme("document-open"));
	ui->actionRemove->setIcon(QIcon::fromTheme("edit-delete"));
	ui->actionClose->setIcon(QIcon::fromTheme("document-close"));
	ui->actionSave->setIcon(QIcon::fromTheme("document-save"));
	ui->actionSave_As->setIcon(QIcon::fromTheme("document-save"));
	QToolBar *projectToolbar = new QToolBar;
	projectToolbar->addAction(ui->actionNew);
	projectToolbar->addAction(ui->actionOpen);
	projectToolbar->addAction(ui->actionSave);
	projectToolbar->addAction(ui->actionSave_As);
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
	connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveProject()));
	connect(ui->actionSave_As, SIGNAL(triggered()), this, SLOT(saveProjectAs()));
	connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(closeProject()));
	connect(ui->actionRemove, SIGNAL(triggered()), this, SLOT(removeProject()));
	connect(projectsTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(treeWidgetItemClicked(QTreeWidgetItem*,int)));
	connect(projectWidget, SIGNAL(setFactDuplicationSignal(bool,bool)), clips, SLOT(setFactDuplicationSlot(bool,bool)));
	connect(projectWidget, SIGNAL(removeFactSignal(int,bool)), clips, SLOT(retractSlot(int,bool)));
	connect(projectWidget, SIGNAL(removeTemplateSignal(QString,bool)), clips, SLOT(unDeftemplateSlot(QString,bool)));
	connect(projectWidget->addFactButton, SIGNAL(clicked()), this, SLOT(addFactSlot()));
	connect(projectWidget->addFactByTemplateButton, SIGNAL(clicked()), this, SLOT(addFactByTemplateSlot()));
	connect(projectWidget->addTemplateButton, SIGNAL(clicked()), this, SLOT(addTemplateSlot()));
	connect(this, SIGNAL(addFactSignal(QString,bool)), clips, SLOT(assertStringSlot(QString,bool)));
	connect(this,SIGNAL(addTemplateSignal(QString,QList<slotsPair>)), clips, SLOT(deftemplateSlot(QString,QList<slotsPair>)));
	connect(this, SIGNAL(treeWidgetItemClickedSignal(int)), projectWidget, SLOT(setCurrentIndex(int)));
	connect(console, SIGNAL(assertStringSignal(QString,bool)), clips, SLOT(assertStringSlot(QString,bool)));
	connect(console, SIGNAL(factsSignal(bool)), clips, SLOT(factsSlot(bool)));
	connect(console, SIGNAL(retractSignal(int,bool)), clips, SLOT(retractSlot(int,bool)));
	connect(console, SIGNAL(saveFactsSignal(QString)), clips, SLOT(saveFactsSlot(QString)));
	connect(console, SIGNAL(setFactDuplicationSignal(bool,bool)), clips, SLOT(setFactDuplicationSlot(bool,bool)));
	connect(console, SIGNAL(createProjectSignal()), this, SLOT(newProject()));
	connect(console, SIGNAL(openProjectSignal()), this, SLOT(openProject()));
	connect(console, SIGNAL(quitSignal()), qApp, SLOT(quit()));
	connect(clips, SIGNAL(factsChangedSignal(QStringList)), projectWidget, SLOT(refreshFacts(QStringList)));
	connect(clips, SIGNAL(templatesChangedSignal(QStringList)), projectWidget, SLOT(refreshTemplates(QStringList)));
	connect(clips, SIGNAL(clearSignal()), projectWidget, SLOT(clearSlot()));
	connect(clips, SIGNAL(outputSignal(QString)), console, SLOT(output(QString)));
	disableWidgets(true);
	readSettings();

}


void MainWindow::newProject()
{
	NewProjectDialog dialog(this);
	if(dialog.exec() == QDialog::Accepted)
	{
		if(!projectPair.first.isEmpty())
		{
			QMessageBox msgBox;
			msgBox.setText(tr("You have opened Project. This project will be closed."));
			msgBox.setInformativeText(tr("Do you want to save your changes?"));
			msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
			msgBox.setDefaultButton(QMessageBox::Save);
			if(msgBox.exec() == QMessageBox::Save)
				clips->saveFactsSlot(projectPair.second+"/facts.clp");
		}
		QString projectName = dialog.projectNameLineEdit->text();
		QString projectPath = dialog.projectPathLineEdit->text();
		if(projectName.isEmpty() || projectPath.isEmpty())
			return;
		disableWidgets(false);
		projectsTreeWidget->clear();
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
		projectPair.first = projectName;
		projectPair.second = projectPath+"/"+projectName+"/"+projectName;
		projectWidget->refreshTemplates(clips->templatesSlot(false));
		projectWidget->refreshFacts(clips->factsSlot(false));
	}

}

void MainWindow::openProject()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Project"), QDir::homePath(), tr("GLIPS-GUI Projects (*.clp.prj);;All files (*.*)"));
	if(!fileName.isEmpty())
	{
		if(!projectPair.first.isEmpty())
		{
			QMessageBox msgBox;
			msgBox.setText(tr("You have opened project. This project will be closed."));
			msgBox.setInformativeText(tr("Do you want to save your changes?"));
			msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
			msgBox.setDefaultButton(QMessageBox::Save);
			if(msgBox.exec() == QMessageBox::Save)
				clips->saveFactsSlot(projectPair.second+"/facts.clp");
		}
		QSettings settings(fileName, QSettings::IniFormat);
		settings.beginGroup("project");
		QString projectName = settings.value("name").toString();
		settings.endGroup();
		if(projectName.isEmpty())
			return;
		disableWidgets(false);
		projectsTreeWidget->clear();
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
		if(!projectPair.first.isEmpty())
			saveProject();
		projectPair.first = projectName;
		projectPair.second = fileName.remove(fileName.lastIndexOf(QRegExp("(/|\\\\)")), fileName.length());
		clips->clearSlot();
		clips->loadSlot(projectPair.second+"/all.clp");
		projectWidget->refreshTemplates(clips->templatesSlot(false));
		clips->loadFactsSlot(projectPair.second+"/facts.clp");
		projectWidget->refreshFacts(clips->factsSlot(false));

	}
}

void MainWindow::addFactSlot()
{
	bool ok;
	QString text = QInputDialog::getText(this, tr("Add Fact"), tr("Fact name:"), QLineEdit::Normal, tr("Fact"), &ok);
	if (ok && !text.isEmpty())
		emit addFactSignal(text, false);
}

void MainWindow::addFactByTemplateSlot()
{
	QStringList templatesList;
	QList<slotsPair> slotsValuesList;
	templatesList = clips->templatesSlot(false);
	bool ok;
	QString templateName = QInputDialog::getItem(this, tr("Select Template"), tr("Template:"), templatesList, 0, false, &ok);
	if (ok && !templateName.isEmpty())
	{
		QList<slotsPair> list = clips->getTemplateInformation(templateName);
		if(list.isEmpty())
			return;
		addFactByTemplateDialog dialog(this, &list);
		if(dialog.exec() == QDialog::Accepted)
		{
			for(int i=0; i<list.count(); i++)
				slotsValuesList.append(slotsPair(list.at(i).first, dialog.lineEditList.at(i)->text()));
			clips->assertSlot(templateName, slotsValuesList, false);
		}
		if(slotsValuesList.isEmpty())
			return;
	}
}

void MainWindow::addTemplateSlot()
{
	bool ok;
	int i = QInputDialog::getInt(this, tr("Slots count"), tr("Enter slots count:"), 1, 1, 100, 1, &ok);
	if (ok)
	{
		addTemplateDialog dialog(this,i);
		if(dialog.exec() == QDialog::Accepted)
		{
			QString name = dialog.nameLineEdit->text();
			if(name.isEmpty())
				return;
			QList<QCheckBox *> checkBoxList = dialog.checkBoxList;
			QList<QLineEdit *> lineEditList = dialog.lineEditList;
			QList<slotsPair> slotsList;
			for(int i=0; i<lineEditList.count();i++)
			{
				slotsPair pair;
				pair.first = checkBoxList.at(i)->checkState();
				pair.second = lineEditList.at(i)->text();
				if(pair.second.isEmpty())
					return;
				slotsList.append(pair);
			}
			emit addTemplateSignal(name, slotsList);
		}
	}
}

void MainWindow::closeProject()
{
	saveProject();
	clips->clearSlot();
	projectsTreeWidget->clear();
	projectPair.first.clear();
	projectPair.second.clear();
	disableWidgets(true);
}

void MainWindow::removeProject()
{
	QMessageBox msgBox;
	msgBox.setText(tr("This action remove project from disc"));
	msgBox.setInformativeText(tr("Do you want to proceed?"));
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);
	if(msgBox.exec() == QMessageBox::Yes)
	{
		saveProject();
		clips->clearSlot();
		projectsTreeWidget->clear();
		removeFolder(QDir(projectPair.second));
		projectPair.first.clear();
		projectPair.second.clear();
		disableWidgets(true);
	}
}

void MainWindow::saveProject()
{
	clips->saveFactsSlot(projectPair.second+"/facts.clp");
	clips->saveSlot(projectPair.second+"/all.clp");
}

void MainWindow::saveProjectAs()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Project"), QDir::homePath(), tr("All files (*.*)"));
	if(!fileName.isEmpty())
	{
		QDir dir;
		dir.mkpath(fileName);
		QString projectPath = fileName;
		QString projectName = fileName.remove(0, fileName.lastIndexOf(QRegExp("(/|\\\\)"))+1);
		QFile file(projectPath+"/"+projectName+".clp.prj");
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
			qDebug()<<"can not open file";
		QTextStream out(&file);
		out << "[project]\n";
		out<<"name="+projectName+"\n";
		file.close();
		clips->saveFactsSlot(projectPath+"/facts.clp");
		clips->saveSlot(projectPath+"/all.clp");
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

void MainWindow::disableWidgets(bool state)
{
	projectsTreeWidget->setDisabled(state);
	projectWidget->setDisabled(state);
	ui->actionSave->setDisabled(state);
	ui->actionSave_As->setDisabled(state);
	ui->actionClose->setDisabled(state);
	ui->actionRemove->setDisabled(state);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	Q_UNUSED(event);
	if(!projectPair.first.isEmpty())
	{
		QMessageBox msgBox;
		msgBox.setText(tr("You have opened project."));
		msgBox.setInformativeText(tr("Do you want to save a project before quit?"));
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::Yes);
		if(msgBox.exec() == QMessageBox::Yes)
			saveProject();
	}
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
	//bool ok;

	Q_UNUSED(column);
	if(!item->parent())
		emit treeWidgetItemClickedSignal(0);
	else
		emit treeWidgetItemClickedSignal(item->parent()->indexOfChild(item));
}

MainWindow::~MainWindow()
{
	delete ui;
}

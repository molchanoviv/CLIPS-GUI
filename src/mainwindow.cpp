#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "consoleclass.h"
#include "dialogs/addtemplatedialog.h"
#include "dialogs/newprojectdialog.h"
#include "dialogs/addfactbytemplatedialog.h"
#include "dialogs/adddeffactsdialog.h"
#include "dialogs/addruledialog.h"
#include "dialogs/addglobalsdialog.h"
#include "dialogs/addfunctiondialog.h"
#include "dialogs/addmessagehandlerdialog.h"
#include "dialogs/addinstancedialog.h"
#include "dialogs/addmoduledialog.h"
#include "dialogs/aboutdialog.h"
#include <QToolBar>
#include <QInputDialog>
#include <QCheckBox>
#include <QComboBox>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	ui->actionShow_Hide_console->setIcon(QIcon::fromTheme("utilities-terminal"));
	ui->actionQuit->setIcon(QIcon::fromTheme("dialog-close"));
	ui->mainToolBar->setWindowTitle(tr("Main Toolbar"));
	ui->mainToolBar->addAction(ui->actionShow_Hide_console);
	ui->mainToolBar->addAction(ui->actionQuit);
	ui->actionNew->setIcon(QIcon::fromTheme("document-new"));
	ui->actionOpen->setIcon(QIcon::fromTheme("document-open"));
	ui->actionRemove->setIcon(QIcon::fromTheme("edit-delete"));
	ui->actionClose->setIcon(QIcon::fromTheme("document-close"));
	ui->actionSave->setIcon(QIcon::fromTheme("document-save"));
	ui->actionSave_As->setIcon(QIcon::fromTheme("document-save"));
	QToolBar *projectToolbar = new QToolBar(tr("Project Toolbar"));
	projectToolbar->addAction(ui->actionNew);
	projectToolbar->addAction(ui->actionOpen);
	projectToolbar->addAction(ui->actionSave);
	projectToolbar->addAction(ui->actionSave_As);
	projectToolbar->addAction(ui->actionClose);
	projectToolbar->addAction(ui->actionRemove);
	addToolBar(projectToolbar);
	console = new consoleClass;
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
	connect(ui->actionAbout_Programm, SIGNAL(triggered()), this, SLOT(aboutDialogSlot()));
	connect(projectsTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(treeWidgetItemClicked(QTreeWidgetItem*,int)));
	connect(projectWidget, SIGNAL(removeTemplateSignal(QString)), clips, SLOT(unDeftemplateSlot(QString)));
	connect(projectWidget, SIGNAL(viewTemplateSignal(QString)), this, SLOT(viewTemplateSlot(QString)));
	connect(projectWidget, SIGNAL(removeFactSignal(int)), clips, SLOT(retractSlot(int)));
	connect(projectWidget, SIGNAL(removeFactsListSignal(QString)), clips, SLOT(unDeffactsSlot(QString)));
	connect(projectWidget, SIGNAL(viewFactsListSignal(QString)), this, SLOT(viewDeffactsSlot(QString)));
	connect(projectWidget, SIGNAL(removeRuleSignal(QString)), clips, SLOT(unDefruleSlot(QString)));
	connect(projectWidget, SIGNAL(viewRuleSignal(QString)), this, SLOT(viewRuleSlot(QString)));
	connect(projectWidget, SIGNAL(setBreakpointSignal(QString)), clips, SLOT(SetBreakSlot(QString)));
	connect(projectWidget, SIGNAL(removeBreakpointSignal(QString)), clips, SLOT(RemoveBreakSlot(QString)));
	connect(projectWidget, SIGNAL(removeActivationSignal(QString)), clips, SLOT(removeActivationSlot(QString)));
	connect(projectWidget, SIGNAL(removeGlobalSignal(QString)), clips, SLOT(unDefglobalSlot(QString)));
	connect(projectWidget, SIGNAL(viewGlobalSignal(QString)), this, SLOT(viewGlobalSlot(QString)));
	connect(projectWidget, SIGNAL(removeFunctionSignal(QString)), clips, SLOT(unDeffunctionSlot(QString)));
	connect(projectWidget, SIGNAL(viewFunctionSignal(QString)), this, SLOT(viewFunctionSlot(QString)));
	connect(projectWidget, SIGNAL(removeGenericSignal(QString)), clips, SLOT(unDefgenericSlot(QString)));
	connect(projectWidget, SIGNAL(viewGenericSignal(QString)), this, SLOT(viewGenericSlot(QString)));
	connect(projectWidget, SIGNAL(removeMethodSignal(QString,int)), clips, SLOT(unDefmethodSlot(QString,int)));
	connect(projectWidget, SIGNAL(viewMethodSignal(QString, int)), this, SLOT(viewMethodSlot(QString, int)));
	connect(projectWidget, SIGNAL(removeClassSignal(QString)), clips, SLOT(unDefclassSlot(QString)));
	connect(projectWidget, SIGNAL(viewClassSignal(QString)), this, SLOT(viewClassSlot(QString)));
	connect(projectWidget, SIGNAL(metaInformationSignal(QString)), this, SLOT(metaInformationSlot(QString)));
	connect(projectWidget, SIGNAL(subClassesSignal(QString)), this, SLOT(subClassesSlot(QString)));
	connect(projectWidget, SIGNAL(superClassesSignal(QString)), this, SLOT(superClassesSlot(QString)));
	connect(projectWidget, SIGNAL(removeMessageHandlerSignal(QString,uint)), clips, SLOT(unDefmessageHandlerSlot(QString,uint)));
	connect(projectWidget, SIGNAL(viewMessageHandlerSignal(QString,uint)), this, SLOT(viewMessageHandlerSlot(QString,uint)));
	connect(projectWidget, SIGNAL(removeInstanceSignal(QString)), clips, SLOT(unDefinstancesSlot(QString)));
	connect(projectWidget, SIGNAL(viewInstanceSignal(QString)), this, SLOT(viewInstanceSlot(QString)));
	connect(projectWidget, SIGNAL(viewModuleSignal(QString)), this, SLOT(viewModuleSlot(QString)));
	connect(projectWidget->addTemplatePushButton, SIGNAL(clicked()), this, SLOT(addTemplateSlot()));
	connect(projectWidget->refreshTemplatesPushButton, SIGNAL(clicked()), this, SLOT(refreshTemplatesSlot()));
	connect(projectWidget->addFactPushButton, SIGNAL(clicked()), this, SLOT(addFactSlot()));
	connect(projectWidget->addFactByTemplatePushButton, SIGNAL(clicked()), this, SLOT(addFactByTemplateSlot()));
	connect(projectWidget->duplicationPushButton, SIGNAL(toggled(bool)), clips, SLOT(setFactDuplicationSlot(bool)));
	connect(projectWidget->refreshFactsPushButton, SIGNAL(clicked()), this, SLOT(refreshFactsSlot()));
	connect(projectWidget->addDeffactPushButton, SIGNAL(clicked()), this, SLOT(addFactsListSlot()));
	connect(projectWidget->refreshDeffactsPushButton, SIGNAL(clicked()), this, SLOT(refreshDeffactsSlot()));
	connect(projectWidget->addRulePushButton, SIGNAL(clicked()), this, SLOT(addRuleSlot()));
	connect(projectWidget->refreshRulesPushButton, SIGNAL(clicked()), this, SLOT(refreshRulesSlot()));
	connect(projectWidget->refreshActivationsPushButton, SIGNAL(clicked()), this, SLOT(refreshActivationsSlot()));
	connect(projectWidget->runPushButton, SIGNAL(clicked()), clips, SLOT(runSlot()));
	connect(projectWidget->setActivationSaliencePushButton, SIGNAL(clicked()), this, SLOT(setActivationSalienceSlot()));
	connect(projectWidget->setStrategyPushButton, SIGNAL(clicked()), this, SLOT(setConflictStrategySlot()));
	connect(projectWidget->addGlobalPushButton, SIGNAL(clicked()), this, SLOT(addGlobalSlot()));
	connect(projectWidget->refreshGlobalsPushButton, SIGNAL(clicked()), this, SLOT(refreshGlobalsSlot()));
	connect(projectWidget->addFunctionPushButton, SIGNAL(clicked()), this, SLOT(addFunctionSlot()));
	connect(projectWidget->refreshFunctionsPushButton, SIGNAL(clicked()), this, SLOT(refreshFunctionsSlot()));
	connect(projectWidget->addGenericPushButton, SIGNAL(clicked()), this, SLOT(addGenericSlot()));
	connect(projectWidget->refreshGenericPushButton, SIGNAL(clicked()), this, SLOT(refreshGenericSlot()));
	connect(projectWidget->addMethodPushButton, SIGNAL(clicked()), this, SLOT(addMethodSlot()));
	connect(projectWidget->refreshMethodsPushButton, SIGNAL(clicked()), this, SLOT(refreshMethodsSlot()));
	connect(projectWidget->refreshClassesPushButton, SIGNAL(clicked()), this, SLOT(refreshClassesSlot()));
	connect(projectWidget->defaultsModePushButton, SIGNAL(clicked()), this, SLOT(setDefaultsModeSlot()));
	connect(projectWidget->addMessageHandlerPushButton, SIGNAL(clicked()), this, SLOT(addMessageHandlerSlot()));
	connect(projectWidget->refreshMessageHandlersPushButton, SIGNAL(clicked()), this, SLOT(refreshMessageHandlersSlot()));
	connect(projectWidget->addInstancePushButton, SIGNAL(clicked()), this, SLOT(addInstanceSlot()));
	connect(projectWidget->refreshInstancesPushButton, SIGNAL(clicked()), this, SLOT(refreshInstancesSlot()));
	connect(projectWidget->addModulePushButton, SIGNAL(clicked()), this, SLOT(addModuleSlot()));
	connect(projectWidget->refreshModulesPushButton, SIGNAL(clicked()), this, SLOT(refreshModulesSlot()));
	connect(projectWidget->currentModulePushButton, SIGNAL(clicked()), this, SLOT(setCurrentModuleSlot()));
	connect(this, SIGNAL(treeWidgetItemClickedSignal(int)), projectWidget, SLOT(setCurrentIndex(int)));
	connect(this,SIGNAL(addTemplateSignal(QString,QList<slotsPair>)), clips, SLOT(deftemplateSlot(QString,QList<slotsPair>)));
	connect(this, SIGNAL(addFactSignal(QString)), clips, SLOT(assertStringSlot(QString)));
	connect(this, SIGNAL(addFactsListSignal(QString,QStringList)), clips, SLOT(deffactsSlot(QString,QStringList)));
	connect(this, SIGNAL(addRuleSignal(QString,QString,QString,QStringList,QStringList)), clips, SLOT(defRuleSlot(QString,QString,QString,QStringList,QStringList)));
	connect(this, SIGNAL(setActivationSalienceSignal(QString,int)), clips, SLOT(setActivationSalienceSlot(QString,int)));
	connect(this, SIGNAL(addGlobalSignal(QString,QHash<QString,QString>)), clips, SLOT(defglobalSlot(QString,QHash<QString,QString>)));
	connect(this, SIGNAL(addFunctionSignal(QString,QString,QString,QString,QString)), clips, SLOT(deffunctionSlot(QString,QString,QString,QString,QString)));
	connect(this, SIGNAL(addGenericSignal(QString)), clips, SLOT(defgenericSlot(QString)));
	connect(this, SIGNAL(addMethodSignal(QString,QString,QString,QString,QString,QString)), clips, SLOT(defmethodSlot(QString,QString,QString,QString,QString,QString)));
	connect(clips, SIGNAL(templatesChangedSignal(QStringList)), projectWidget, SLOT(refreshTemplates(QStringList)));
	connect(clips, SIGNAL(factsChangedSignal(QStringList)), projectWidget, SLOT(refreshFacts(QStringList)));
	connect(clips, SIGNAL(deffactsChangedSignal(QStringList)), projectWidget, SLOT(refreshDeffacts(QStringList)));
	connect(clips, SIGNAL(rulesChangedSignal(QStringList)), projectWidget, SLOT(refreshRules(QStringList)));
	connect(clips, SIGNAL(activationsChangedSignal(QStringList)), projectWidget, SLOT(refreshActivations(QStringList)));
	connect(clips, SIGNAL(globalsChangedSignal(QStringList)), projectWidget, SLOT(refreshGlobals(QStringList)));
	connect(clips, SIGNAL(functionsChangedSignal(QStringList)), projectWidget, SLOT(refreshFunctions(QStringList)));
	connect(clips, SIGNAL(genericChangedSignal(QStringList)), projectWidget, SLOT(refreshGeneric(QStringList)));
	connect(clips, SIGNAL(methodsChangedSignal(QHash<QString, int>)), projectWidget, SLOT(refreshMethods(QHash<QString, int>)));
	connect(clips, SIGNAL(classesChangedSignal(QStringList)), projectWidget, SLOT(refreshClasses(QStringList)));
	connect(clips, SIGNAL(messageHandlersChangedSignal(QHash<QString, unsigned int>)), projectWidget, SLOT(refreshMessageHandlers(QHash<QString, unsigned int>)));
	connect(clips, SIGNAL(instancesChangedSignal(QStringList)), projectWidget, SLOT(refreshInstancesSlot(QStringList)));
	connect(clips, SIGNAL(modulesChangedSignal(QStringList)), this, SLOT(refreshModulesSlot()));
	connect(clips, SIGNAL(clearSignal()), projectWidget, SLOT(clearSlot()));
	connect(clips, SIGNAL(dataChanged()), this, SLOT(dataChangedSlot()));
	connect(clips, SIGNAL(refreshAll()), this, SLOT(refreshAll()));
	connect(clips, SIGNAL(outputSignal(QString)), console, SLOT(output(QString)));
	connect(console, SIGNAL(execSignal(QString)), clips, SLOT(executeCommand(QString)));
	connect(console, SIGNAL(refreshAllSignal()), this, SLOT(refreshAll()));
	connect(console, SIGNAL(outputSignal(QString)), this, SLOT(outputSlot(QString)));
	disableWidgets(true);
	readSettings();
	unsaved = false;

}

MainWindow::~MainWindow()
{
	delete ui;
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
				saveProject();
		}
		QString projectName = dialog.projectNameLineEdit->text();
		QString projectPath = dialog.projectPathLineEdit->text();
		if(projectName.isEmpty() || projectPath.isEmpty())
			return;
		disableWidgets(false);
		createProjectTreeWidgetItems(projectName);
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
		refreshAll();
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
				saveProject();
		}
		QSettings settings(fileName, QSettings::IniFormat);
		settings.beginGroup("project");
		QString projectName = settings.value("name").toString();
		settings.endGroup();
		if(projectName.isEmpty())
			return;
		disableWidgets(false);
		createProjectTreeWidgetItems(projectName);
		if(!projectPair.first.isEmpty())
			saveProject();
		projectPair.first = projectName;
		projectPair.second = fileName.remove(fileName.lastIndexOf(QRegExp("(/|\\\\)")), fileName.length());
		clips->clearSlot();
		clips->loadSlot(projectPair.second);
		refreshAll();
	}
}

void MainWindow::createProjectTreeWidgetItems(QString projectName)
{
	projectsTreeWidget->clear();
	QTreeWidgetItem *item = new QTreeWidgetItem();
	item->setText(0, projectName);
	item->setText(1, QString::number(projectsTreeWidget->topLevelItemCount()));
	QTreeWidgetItem *templatesItem = new QTreeWidgetItem();
	templatesItem->setText(0, tr("Templates"));
	QTreeWidgetItem *factsItem = new QTreeWidgetItem();
	factsItem->setText(0, tr("Facts"));
	QTreeWidgetItem *deffactsItem = new QTreeWidgetItem();
	deffactsItem->setText(0, tr("FactsList"));
	QTreeWidgetItem *rulesItem = new QTreeWidgetItem();
	rulesItem->setText(0, tr("Rules"));
	QTreeWidgetItem *activationsItem = new QTreeWidgetItem();
	activationsItem->setText(0, tr("Activations"));
	QTreeWidgetItem *globalsItem = new QTreeWidgetItem();
	globalsItem->setText(0, tr("Globals"));
	QTreeWidgetItem *functionsItem = new QTreeWidgetItem();
	functionsItem->setText(0, tr("Functions"));
	QTreeWidgetItem *genericItem = new QTreeWidgetItem();
	genericItem->setText(0, tr("Generic Functions"));
	QTreeWidgetItem *methodsItem = new QTreeWidgetItem();
	methodsItem->setText(0, tr("Methods"));
	QTreeWidgetItem *classesItem = new QTreeWidgetItem();
	classesItem->setText(0, tr("Classes"));
	QTreeWidgetItem *messageHandlersItem = new QTreeWidgetItem();
	messageHandlersItem->setText(0, tr("Message Handlers"));
	QTreeWidgetItem *instancesItem = new QTreeWidgetItem();
	instancesItem->setText(0, tr("Instances"));
	QTreeWidgetItem *modulesItem = new QTreeWidgetItem();
	modulesItem->setText(0, tr("Modules"));
	item->addChild(templatesItem);
	item->addChild(factsItem);
	item->addChild(deffactsItem);
	item->addChild(rulesItem);
	item->addChild(activationsItem);
	item->addChild(globalsItem);
	item->addChild(functionsItem);
	item->addChild(genericItem);
	item->addChild(methodsItem);
	item->addChild(classesItem);
	item->addChild(messageHandlersItem);
	item->addChild(instancesItem);
	item->addChild(modulesItem);
	projectsTreeWidget->insertTopLevelItem(0, item);
	item->setExpanded(1);
	projectsTreeWidget->clearSelection();
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
	clips->saveSlot(projectPair.second);
	unsaved = false;
	redrawTitle();
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
		clips->saveSlot(projectPath);
		unsaved = false;
		redrawTitle();
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
	console->setDisabled(state);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	Q_UNUSED(event);
	if(unsaved)
	{
		QMessageBox msgBox;
		msgBox.setText(tr("You have unsaved data. This data will be lost."));
		msgBox.setInformativeText(tr("Do you really want to quit?"));
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Save);
		msgBox.setDefaultButton(QMessageBox::No);
		int state = msgBox.exec();
		if(state == QMessageBox::No)
			event->ignore();
		else if(state == QMessageBox::Save)
		{
			saveProject();
			event->accept();
		}
		else
			event->accept();

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

void MainWindow::refreshAll()
{
	refreshTemplatesSlot();
	refreshFactsSlot();
	refreshDeffactsSlot();
	refreshRulesSlot();
	refreshActivationsSlot();
	refreshGlobalsSlot();
	refreshFunctionsSlot();
	refreshGenericSlot();
	refreshMethodsSlot();
	refreshClassesSlot();
	refreshMessageHandlersSlot();
	refreshInstancesSlot();
	refreshModulesSlot();
}

void MainWindow::redrawTitle()
{
	QString str = "";
	if(unsaved)
		str = tr("CLIPS-GUI")+"*";
	else
		str = tr("CLIPS-GUI");
	setWindowTitle(str);
}

void MainWindow::dataChangedSlot()
{
	unsaved = true;
	redrawTitle();
}

void MainWindow::aboutDialogSlot()
{
	aboutDialog dialog(this);
	dialog.exec();
}

void MainWindow::outputSlot(QString str)
{
	QMessageBox::information(this, tr(""), str);
}

//Templates

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

void MainWindow::viewTemplateSlot(QString name)
{
	QString info = clips->getTemplatePPF(name);
	if(info.isEmpty())
		info = tr("This template haven't pretty print representation");
	QMessageBox::information(this, tr("Information About Template"), info);
}

void MainWindow::refreshTemplatesSlot()
{
	projectWidget->refreshTemplates(clips->templatesSlot());
}

//Facts

void MainWindow::addFactSlot()
{
	bool ok;
	QString text = QInputDialog::getText(this, tr("Add Fact"), tr("Fact name:"), QLineEdit::Normal, "", &ok);
	if (ok && !text.isEmpty())
		emit addFactSignal(text);
}

void MainWindow::addFactByTemplateSlot()
{
	QStringList templatesList;
	QList<slotsPair> slotsValuesList;
	templatesList = clips->templatesSlot();
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
			clips->assertSlot(templateName, slotsValuesList);
		}
		if(slotsValuesList.isEmpty())
			return;
	}
}

void MainWindow::refreshFactsSlot()
{
	projectWidget->refreshFacts(clips->factsSlot());
}

//Facts Lists

void MainWindow::addFactsListSlot()
{
	bool ok;
	int i = QInputDialog::getInt(this, tr("Facts count"), tr("Enter facts count:"), 1, 1, 100, 1, &ok);
	if (ok)
	{
		addDeffactsDialog dialog(this, i);
		if(dialog.exec() == QDialog::Accepted)
		{
			QString name = dialog.nameLineEdit->text();
			if(name.isEmpty())
				return;
			QList<QLineEdit *> lineEditList = dialog.lineEditList;
			QStringList factsList;
			for(int i=0; i<lineEditList.count();i++)
			{
				factsList.append(lineEditList.at(i)->text());
			}
			emit addFactsListSignal(name, factsList);
		}
	}
}

void MainWindow::viewDeffactsSlot(QString name)
{
	QString info = clips->getDeffactsPPF(name);
	if(info.isEmpty())
		info = tr("This fact list haven't pretty print representation");
	QMessageBox::information(this, tr("Information About Facts List"), info);
}

void MainWindow::refreshDeffactsSlot()
{
	projectWidget->refreshDeffacts(clips->factsListSlot());
}

//Rules

void MainWindow::addRuleSlot()
{
	bool ok;
	int antecedents = QInputDialog::getInt(this, tr("Antecedents count"), tr("Enter antecedents count:"), 1, 1, 100, 1, &ok);
	if(ok)
	{
		int consequents = QInputDialog::getInt(this, tr("Consequents count"), tr("Enter consequents count:"), 1, 1, 100, 1, &ok);
		if(ok)
		{
			addRuleDialog dialog(this, antecedents, consequents);
			if(dialog.exec() == QDialog::Accepted)
			{
				QString name = dialog.nameLineEdit->text();
				if(name.isEmpty())
					return;
				QString comment = dialog.commentLineEdit->text();
				QString declaration = dialog.declarationLineEdit->text();
				QStringList antecedentsList;
				QList<QLineEdit *> antecedentsLineEditList = dialog.antecedentsLineEditList;
				for(int i=0; i<antecedentsLineEditList.count(); i++)
				{
					antecedentsList.append(antecedentsLineEditList.at(i)->text());
				}
				if(antecedentsList.isEmpty())
					return;
				QStringList consequentsList;
				QList<QLineEdit *> consequentsLineEditList = dialog.consequentsLineEditList;
				for(int i=0; i<consequentsLineEditList.count(); i++)
				{
					consequentsList.append(consequentsLineEditList.at(i)->text());
				}
				if(consequentsList.isEmpty())
					return;
				emit addRuleSignal(name, comment, declaration, antecedentsList, consequentsList);
			}
		}
	}
}

void MainWindow::viewRuleSlot(QString name)
{
	QString info = clips->getRulePPF(name);
	if(info.isEmpty())
		info = tr("This rule haven't pretty print representation");
	QMessageBox::information(this, tr("Information About Rule"), info);
}

void MainWindow::refreshRulesSlot()
{
	projectWidget->refreshRules(clips->rulesSlot());
}

//Agenda

void MainWindow::setActivationSalienceSlot()
{
	QList<QListWidgetItem*> activations = projectWidget->activationsListWidget->selectedItems();
	if(!activations.isEmpty())
	{
		QString name = activations.at(0)->text();
		int cur_salience = clips->getActivationSalienceSlot(name);
		bool ok;
		int new_salience = QInputDialog::getInt(this, tr("Set Activation Salience"), tr("Salience:"), cur_salience, -10000, 10000, 1, &ok);
		if (ok)
			emit setActivationSalienceSignal(name, new_salience);
	}
}

void MainWindow::setConflictStrategySlot()
{
	QHash<QString, int> strategyesHash = clips->getStrategyes();
	QStringList strategyesList;
	int currentStrategy = clips->getStrategy();
	int val=0;
	int iter_num=0;
	QHashIterator<QString, int> i(strategyesHash);
	while (i.hasNext())
	{
		i.next();
		strategyesList.append(i.key());
		if(i.value() == currentStrategy)
			val = iter_num;
		iter_num++;
	}

	bool ok;
	QString strategyName = QInputDialog::getItem(this, tr("Select Strategy"), tr("Strategy:"), strategyesList, val, false, &ok);
	if (ok && !strategyName.isEmpty())
	{
		clips->setStrategySlot(strategyesHash[strategyName]);
	}
}

void MainWindow::refreshActivationsSlot()
{
	projectWidget->refreshActivations(clips->agendaSlot());
}

//Globals

void MainWindow::addGlobalSlot()
{
	bool ok;
	int variablesCount = QInputDialog::getInt(this, tr("Globals count"), tr("Enter globals count:"), 1, 1, 100, 1, &ok);
	if(ok)
	{
		QStringList modulesList = clips->modulesSlot();
		addGlobalsDialog dialog(this, variablesCount, modulesList);
		if(dialog.exec() == QDialog::Accepted)
		{
			QString module = dialog.modulesComboBox->currentText();
			if(module.isEmpty())
				return;
			QHash<QString, QString> hash;
			QList<QPair<QLineEdit*, QLineEdit*> > list = dialog.assignmentsLineEditsList;
			for(int i=0; i<list.count(); i++)
				hash.insert(list.at(i).first->text(), list.at(i).second->text());
			if(hash.isEmpty())
				return;
			emit addGlobalSignal(module, hash);
		}
	}
}

void MainWindow::viewGlobalSlot(QString name)
{
	QString info = clips->getGlobalPPF(name);
	if(info.isEmpty())
		info = tr("This global haven't pretty print representation");
	QMessageBox::information(this, tr("Information About Global"), info);
}

void MainWindow::refreshGlobalsSlot()
{
	projectWidget->refreshGlobals(clips->globalsSlot());
}

//Functions

void MainWindow::addFunctionSlot()
{

	addFunctionDialog dialog(this);
	if(dialog.exec() == QDialog::Accepted)
	{
		QString name = dialog.nameLineEdit->text();
		QString comment = dialog.commentLineEdit->text();
		QString regular = dialog.regularLineEdit->text();
		QString wildcard = dialog.wildcardLineEdit->text();
		QString expression = dialog.expressionTextEdit->document()->toPlainText();
		emit addFunctionSignal(name, comment, regular, wildcard, expression);
	}
}

void MainWindow::viewFunctionSlot(QString name)
{
	QString info = clips->getFunctionPPF(name);
	if(info.isEmpty())
		info = tr("This function haven't pretty print representation");
	QMessageBox::information(this, tr("Information About Function"), info);
}

void MainWindow::refreshFunctionsSlot()
{
	projectWidget->refreshFunctions(clips->functionsSlot());
}

//Generic Functions

void MainWindow::addGenericSlot()
{
	bool ok;
	QString text = QInputDialog::getText(this, tr("Add Generic Function"), tr("Generic function name:"), QLineEdit::Normal, "", &ok);
	if (ok && !text.isEmpty())
		emit addGenericSignal(text);
}

void MainWindow::viewGenericSlot(QString name)
{
	QString info = clips->getGenericPPF(name);
	if(info.isEmpty())
		info = tr("This generic function haven't pretty print representation");
	QMessageBox::information(this, tr("Information About Generic Function"), info);
}

void MainWindow::refreshGenericSlot()
{
	projectWidget->refreshGeneric(clips->genericSlot());
}

//Methods

void MainWindow::addMethodSlot()
{

	addFunctionDialog dialog(this);
	if(dialog.exec() == QDialog::Accepted)
	{
		QString name = dialog.nameLineEdit->text();
		QString index = "";
		QString comment = dialog.commentLineEdit->text();
		QString regular = dialog.regularLineEdit->text();
		QString wildcard = dialog.wildcardLineEdit->text();
		QString expression = dialog.expressionTextEdit->document()->toPlainText();
		emit addMethodSignal(name, index, comment, regular, wildcard, expression);
	}
}

void MainWindow::viewMethodSlot(QString name, int index)
{
	QString info = clips->getMethodPPF(name, index);
	if(info.isEmpty())
		info = tr("This method haven't pretty print representation");
	QMessageBox::information(this, tr("Information About Method"), info);
}

void MainWindow::refreshMethodsSlot()
{
	projectWidget->refreshMethods(clips->methodsSlot());
}

//Classes

void MainWindow::viewClassSlot(QString name)
{
	QString info = clips->getClassPPF(name);
	if(info.isEmpty())
		info = tr("This class haven't pretty print representation");
	QMessageBox::information(this, tr("Information About Class"), info);
}

void MainWindow::refreshClassesSlot()
{
	projectWidget->refreshClasses(clips->classesSlot());
}

void MainWindow::metaInformationSlot(QString name)
{
	QString info = clips->getMetaInformation(name);
	if(info.isEmpty())
		info = tr("This class haven't meta information.");
	QMessageBox::information(this, tr("Class Meta Information"), info);
}

void MainWindow::subClassesSlot(QString name)
{
	QString info = clips->getSubclasses(name);
	if(info.isEmpty())
		info = tr("This class haven't subclasses.");
	QMessageBox::information(this, tr("Subclasses"), info);
}

void MainWindow::superClassesSlot(QString name)
{
	QString info = clips->getSuperclasses(name);
	if(info.isEmpty())
		info = tr("This class haven't superclasses.");
	QMessageBox::information(this, tr("Supercalsses"), info);
}

void MainWindow::setDefaultsModeSlot()
{
	unsigned short currentMode = clips->getCurrentDefaultsMode();
	QHash<QString, unsigned short> modes = clips->getDefaultsModes();
	QHashIterator<QString, unsigned short> i(modes);
	QStringList modesList;
	int iterNum = 0;
	int val = 0;
	while (i.hasNext())
	{
		i.next();
		modesList.append(i.key());
		if(i.value() == currentMode)
			val = iterNum;
		iterNum++;
	}
	bool ok;
	QString modeName = QInputDialog::getItem(this, tr("Select Defaults Mode"), tr("Defaults Mode:"), modesList, val, false, &ok);
	if (ok && !modeName.isEmpty())
	{
		clips->setDefaultsMode(modes[modeName]);
	}
}

//Message Handlers

void MainWindow::addMessageHandlerSlot()
{
	QStringList classesList = clips->classesSlot();
	QStringList handlerTypeList = clips->getHandlerTypesSlot();
	addMessageHandlerDialog dialog(this, classesList, handlerTypeList);
	if(dialog.exec() == QDialog::Accepted)
	{
		QString className = dialog.classNameComboBox->currentText();
		QString messageName = dialog.messageNameLineEdit->text();
		if(messageName.isEmpty())
			return;
		QString handlerType = dialog.handlerTypeComboBox->currentText();
		QString comment = dialog.commentLineEdit->text();
		QString parameter = dialog.parameterLineEdit->text();
		QString wildcardParameter = dialog.wildcardParameterLineEdit->text();
		QString action = dialog.actionTextEdit->toPlainText();
		clips->defmessageHandlerSlot(className, messageName, handlerType, comment, parameter, wildcardParameter, action);
	}
}

void MainWindow::viewMessageHandlerSlot(QString name, unsigned int index)
{
	QString info = clips->getMessageHandlerPPF(name, index);
	if(info.isEmpty())
		info = tr("This message handler haven't pretty print representation");
	QMessageBox::information(this, tr("Information About Message Handler"), info);
}

void MainWindow::refreshMessageHandlersSlot()
{
	projectWidget->refreshMessageHandlers(clips->messageHandlersSlot());
}

//Instances

void MainWindow::addInstanceSlot()
{
	addInstanceDialog dialog(this);
	if(dialog.exec() == QDialog::Accepted)
	{
		QString name = dialog.nameLineEdit->text();
		QString comment = dialog.commentLineEdit->text();
		QString instanceTemplate = dialog.instanceTemplateLineEdit->text();
		QString active = "";
		if(dialog.activeCheckBox->isChecked())
			active = "active";
		clips->definstanceSlot(name, active, comment, instanceTemplate);
	}
}

void MainWindow::viewInstanceSlot(QString name)
{
	QString info = clips->getInstancePPF(name);
	if(info.isEmpty())
		info = tr("This instance haven't pretty print representation");
	QMessageBox::information(this, tr("Information About Instance"), info);
}

void MainWindow::refreshInstancesSlot()
{
	projectWidget->refreshInstancesSlot(clips->instancesSlot());
}

//Modules

void MainWindow::addModuleSlot()
{
	addModuleDialog dialog(this);
	if(dialog.exec() == QDialog::Accepted)
	{
		QString name = dialog.nameLineEdit->text();
		QString comment = dialog.commentLineEdit->text();
		QString specification = dialog.specificationLineEdit->text();
		clips->defmoduleSlot(name, comment, specification);
	}
}

void MainWindow::viewModuleSlot(QString name)
{
	QString info = clips->getModulePPF(name);
	if(info.isEmpty())
		info = tr("This module haven't pretty print representation");
	QMessageBox::information(this, tr("Information About Module"), info);
}

void MainWindow::refreshModulesSlot()
{
	projectWidget->refreshModulesSlot(clips->modulesSlot());
}

void MainWindow::setCurrentModuleSlot()
{
	QString currentModule = clips->getCurrentModule();
	QStringList modulesList = clips->modulesSlot();
	int index=0;
	for(int i=0; i<modulesList.count();i++)
	{
		if(modulesList.at(i) == currentModule)
			index = i;
	}
	QString module = QInputDialog::getItem(this, "Set Current Module", "Module", modulesList, index, false);
	clips->setCurrentModule(module);
}

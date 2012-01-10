#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "consoleclass.h"
#include "addtemplatedialog.h"
#include "newprojectdialog.h"
#include "addfactbytemplatedialog.h"
#include "adddeffactsdialog.h"
#include "addruledialog.h"
#include "addglobalsdialog.h"
#include "addfunctiondialog.h"
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
	connect(projectWidget, SIGNAL(removeTemplateSignal(QString,bool)), clips, SLOT(unDeftemplateSlot(QString,bool)));
	connect(projectWidget, SIGNAL(removeFactSignal(int,bool)), clips, SLOT(retractSlot(int,bool)));
	connect(projectWidget, SIGNAL(removeFactsListSignal(QString,bool)), clips, SLOT(unDeffactsSlot(QString,bool)));
	connect(projectWidget, SIGNAL(removeRuleSignal(QString,bool)), clips, SLOT(unDefruleSlot(QString,bool)));
	connect(projectWidget, SIGNAL(setBreakpointSignal(QString,bool)), clips, SLOT(SetBreakSlot(QString,bool)));
	connect(projectWidget, SIGNAL(removeBreakpointSignal(QString,bool)), clips, SLOT(RemoveBreakSlot(QString,bool)));
	connect(projectWidget, SIGNAL(removeActivationSignal(QString,bool)), clips, SLOT(removeActivationSlot(QString,bool)));
	connect(projectWidget, SIGNAL(removeGlobalSignal(QString,bool)), clips, SLOT(unDefglobalSlot(QString,bool)));
	connect(projectWidget, SIGNAL(watchGlobalSignal(QString)), this, SLOT(watchGlobalSlot(QString)));
	connect(projectWidget, SIGNAL(removeFunctionSignal(QString,bool)), clips, SLOT(unDeffunctionSlot(QString,bool)));
	connect(projectWidget, SIGNAL(watchFunctionSignal(QString)), this, SLOT(watchFunctionSlot(QString)));
	connect(projectWidget, SIGNAL(removeGenericSignal(QString,bool)), clips, SLOT(unDefgenericSlot(QString,bool)));
	connect(projectWidget, SIGNAL(watchGenericSignal(QString)), this, SLOT(watchGenericSlot(QString)));
	connect(projectWidget->addTemplateButton, SIGNAL(clicked()), this, SLOT(addTemplateSlot()));
	connect(projectWidget->refreshTemplatesButton, SIGNAL(clicked()), this, SLOT(refreshTemplatesSlot()));
	connect(projectWidget->addFactButton, SIGNAL(clicked()), this, SLOT(addFactSlot()));
	connect(projectWidget->addFactByTemplateButton, SIGNAL(clicked()), this, SLOT(addFactByTemplateSlot()));
	connect(projectWidget->refreshFactsButton, SIGNAL(clicked()), this, SLOT(refreshFactsSlot()));
	connect(projectWidget->addDeffactButton, SIGNAL(clicked()), this, SLOT(addFactsListSlot()));
	connect(projectWidget->refreshDeffactsButton, SIGNAL(clicked()), this, SLOT(refreshDeffactsSlot()));
	connect(projectWidget->addRuleButton, SIGNAL(clicked()), this, SLOT(addRuleSlot()));
	connect(projectWidget->refreshRulesButton, SIGNAL(clicked()), this, SLOT(refreshRulesSlot()));
	connect(projectWidget->refreshActivationsButton, SIGNAL(clicked()), this, SLOT(refreshActivationsSlot()));
	connect(projectWidget->runButton, SIGNAL(clicked()), clips, SLOT(runSlot()));
	connect(projectWidget->setActivationSaliencePushButton, SIGNAL(clicked()), this, SLOT(setActivationSalienceSlot()));
	connect(projectWidget->setStrategyPushButton, SIGNAL(clicked()), this, SLOT(setConflictStrategySlot()));
	connect(projectWidget->addGlobalButton, SIGNAL(clicked()), this, SLOT(addGlobalSlot()));
	connect(projectWidget->refreshGlobalsButton, SIGNAL(clicked()), this, SLOT(refreshGlobalsSlot()));
	connect(projectWidget->refreshFunctionsButton, SIGNAL(clicked()), this, SLOT(refreshFunctionsSlot()));
	connect(projectWidget->refreshGenericButton, SIGNAL(clicked()), this, SLOT(refreshGenericSlot()));
	connect(projectWidget->refreshClassesButton, SIGNAL(clicked()), this, SLOT(refreshClassesSlot()));
	connect(projectWidget->addFunctionButton, SIGNAL(clicked()), this, SLOT(addFunctionSlot()));
	connect(projectWidget->addGenericButton, SIGNAL(clicked()), this, SLOT(addGenericSlot()));
	connect(this, SIGNAL(addFactSignal(QString,bool)), clips, SLOT(assertStringSlot(QString,bool)));
	connect(this, SIGNAL(addFactsListSignal(QString,QStringList)), clips, SLOT(deffactsSlot(QString,QStringList)));
	connect(this,SIGNAL(addTemplateSignal(QString,QList<slotsPair>)), clips, SLOT(deftemplateSlot(QString,QList<slotsPair>)));
	connect(this, SIGNAL(treeWidgetItemClickedSignal(int)), projectWidget, SLOT(setCurrentIndex(int)));
	connect(this, SIGNAL(addRuleSignal(QString,QString,QString,QStringList,QStringList)), clips, SLOT(defRuleSlot(QString,QString,QString,QStringList,QStringList)));
	connect(this, SIGNAL(setActivationSalienceSignal(QString,int,bool)), clips, SLOT(setActivationSalienceSlot(QString,int,bool)));
	connect(this, SIGNAL(addGlobalSignal(QString,QHash<QString,QString>)), clips, SLOT(defglobalSlot(QString,QHash<QString,QString>)));
	connect(this, SIGNAL(addFunctionSignal(QString,QString,QString,QString,QString)), clips, SLOT(deffunctionSlot(QString,QString,QString,QString,QString)));
	connect(this, SIGNAL(addGenericSignal(QString)), clips, SLOT(defgenericSlot(QString)));
	connect(console, SIGNAL(assertStringSignal(QString,bool)), clips, SLOT(assertStringSlot(QString,bool)));
	connect(console, SIGNAL(factsSignal(bool)), clips, SLOT(factsSlot(bool)));
	connect(console, SIGNAL(retractSignal(int,bool)), clips, SLOT(retractSlot(int,bool)));
	connect(console, SIGNAL(saveFactsSignal(QString)), clips, SLOT(saveFactsSlot(QString)));
	connect(console, SIGNAL(setFactDuplicationSignal(bool,bool)), clips, SLOT(setFactDuplicationSlot(bool,bool)));
	connect(console, SIGNAL(createProjectSignal()), this, SLOT(newProject()));
	connect(console, SIGNAL(openProjectSignal()), this, SLOT(openProject()));
	connect(console, SIGNAL(quitSignal()), qApp, SLOT(quit()));
	connect(clips, SIGNAL(templatesChangedSignal(QStringList)), projectWidget, SLOT(refreshTemplates(QStringList)));
	connect(clips, SIGNAL(factsChangedSignal(QStringList)), projectWidget, SLOT(refreshFacts(QStringList)));
	connect(clips, SIGNAL(deffactsChangedSignal(QStringList)), projectWidget, SLOT(refreshDeffacts(QStringList)));
	connect(clips, SIGNAL(rulesChangedSignal(QStringList)), projectWidget, SLOT(refreshRules(QStringList)));
	connect(clips, SIGNAL(activationsChangedSignal(QStringList)), projectWidget, SLOT(refreshActivations(QStringList)));
	connect(clips, SIGNAL(globalsChangedSignal(QStringList)), projectWidget, SLOT(refreshGlobals(QStringList)));
	connect(clips, SIGNAL(functionsChangedSignal(QStringList)), projectWidget, SLOT(refreshFunctions(QStringList)));
	connect(clips, SIGNAL(genericChangedSignal(QStringList)), projectWidget, SLOT(refreshGeneric(QStringList)));
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
		refreshAll(false);
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
		clips->loadSlot(projectPair.second+"/all.clp");
		clips->loadFactsSlot(projectPair.second+"/facts.clp");
		clips->bLoadSlot(projectPair.second+"/data.bin");
		refreshAll(false);
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
	QTreeWidgetItem *classesItem = new QTreeWidgetItem();
	classesItem->setText(0, tr("Classes"));
	item->addChild(templatesItem);
	item->addChild(factsItem);
	item->addChild(deffactsItem);
	item->addChild(rulesItem);
	item->addChild(activationsItem);
	item->addChild(globalsItem);
	item->addChild(functionsItem);
	item->addChild(genericItem);
	item->addChild(classesItem);
	projectsTreeWidget->insertTopLevelItem(0, item);
	item->setExpanded(1);
	projectsTreeWidget->clearSelection();
}

void MainWindow::addFactSlot()
{
	bool ok;
	QString text = QInputDialog::getText(this, tr("Add Fact"), tr("Fact name:"), QLineEdit::Normal, "", &ok);
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

void MainWindow::addGlobalSlot()
{
	bool ok;
	int variablesCount = QInputDialog::getInt(this, tr("Globals count"), tr("Enter globals count:"), 1, 1, 100, 1, &ok);
	if(ok)
	{
		QStringList modulesList = clips->getModules();
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

void MainWindow::addGenericSlot()
{
	bool ok;
	QString text = QInputDialog::getText(this, tr("Add Generic Function"), tr("Generic function name:"), QLineEdit::Normal, "", &ok);
	if (ok && !text.isEmpty())
		emit addGenericSignal(text);
}

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
			emit setActivationSalienceSignal(name, new_salience, false);
	}
}

void MainWindow::setConflictStrategySlot()
{
	QHash<QString, int> strategyesHash = clips->getStrategyes();
	QStringList strategyesList;
	int cur_strategy = clips->getStrategy();
	int val=0;
	int iter_num=0;
	QHashIterator<QString, int> i(strategyesHash);
	while (i.hasNext())
	{
		i.next();
		strategyesList.append(i.key());
		if(i.value() == cur_strategy)
			val = iter_num;
		iter_num++;
	}

	bool ok;
	QString strategyName = QInputDialog::getItem(this, tr("Select Strategy"), tr("Strategy:"), strategyesList, val, false, &ok);
	if (ok && !strategyName.isEmpty())
	{
		clips->setStrategySlot(strategyesHash[strategyName], false);
	}
}

void MainWindow::watchGlobalSlot(QString name)
{
	QString info = clips->getGlobalInformation(name);
	QMessageBox::information(this, tr("Information About Global"), info);
}

void MainWindow::watchFunctionSlot(QString name)
{
	QString info = clips->getFunctionInformation(name);
	QMessageBox::information(this, tr("Information About Function"), info);
}

void MainWindow::watchGenericSlot(QString name)
{
	QString info = clips->getGenericInformation(name);
	QMessageBox::information(this, tr("Information About Generic Function"), info);
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
	clips->bSaveSlot(projectPair.second+"/data.bin");
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

void MainWindow::refreshAll(bool state)
{
	projectWidget->refreshTemplates(clips->templatesSlot(state));
	projectWidget->refreshFacts(clips->factsSlot(state));
	projectWidget->refreshDeffacts(clips->factsListSlot(state));
	projectWidget->refreshRules(clips->rulesSlot(state));
	projectWidget->refreshActivations(clips->agendaSlot(state));
	projectWidget->refreshGlobals(clips->globalsSlot(state));
	projectWidget->refreshFunctions(clips->functionsSlot(state));
	projectWidget->refreshGeneric(clips->genericSlot(state));
}

void MainWindow::refreshTemplatesSlot()
{
	projectWidget->refreshTemplates(clips->templatesSlot(false));
}

void MainWindow::refreshFactsSlot()
{
	projectWidget->refreshFacts(clips->factsSlot(false));
}

void MainWindow::refreshDeffactsSlot()
{
	projectWidget->refreshDeffacts(clips->factsListSlot(false));
}

void MainWindow::refreshRulesSlot()
{
	projectWidget->refreshRules(clips->rulesSlot(false));
}

void MainWindow::refreshActivationsSlot()
{
	projectWidget->refreshActivations(clips->agendaSlot(false));
}

void MainWindow::refreshGlobalsSlot()
{
	projectWidget->refreshGlobals(clips->globalsSlot(false));
}

void MainWindow::refreshFunctionsSlot()
{
	projectWidget->refreshFunctions(clips->functionsSlot(false));
}

void MainWindow::refreshGenericSlot()
{
	projectWidget->refreshGeneric(clips->genericSlot(false));
}

void MainWindow::refreshClassesSlot()
{
	//
}

MainWindow::~MainWindow()
{
	delete ui;
}

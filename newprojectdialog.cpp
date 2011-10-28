#include "newprojectdialog.h"
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <QDebug>

NewProjectDialog::NewProjectDialog(QWidget *parent) :
	QDialog(parent)
{
	setupUi(this);
	connect(pathToolButton, SIGNAL(clicked()), this, SLOT(getDir()));
	projectNameLineEdit->setText("Untitled");
	projectPathLineEdit->setText(QDir::homePath());
	updateProjectName(projectNameLineEdit->text());
}

void NewProjectDialog::updateProjectName(QString directory)
{
	QDir dir(projectPathLineEdit->text());
	bool ok = dir.cd(directory);
	if(ok)
	{
		projectNameLineEdit->setText(projectNameLineEdit->text()+"-1");
		updateProjectName(projectNameLineEdit->text());
	}
}

void NewProjectDialog::getDir()
{
	QString dirname = QFileDialog::getExistingDirectory( this, tr("Select a Directory"), QDir::currentPath());
	if(!dirname.isNull())
		projectPathLineEdit->setText(dirname);
}

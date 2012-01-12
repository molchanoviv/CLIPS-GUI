#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include "ui_newprojectdialog.h"


class NewProjectDialog : public QDialog, public Ui::newProjectDialog
{
	Q_OBJECT

public:
	explicit NewProjectDialog(QWidget *parent = 0);

public slots:
	void getDir();
	void updateProjectName(QString);
};

#endif // NEWPROJECTDIALOG_H

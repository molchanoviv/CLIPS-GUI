#ifndef ADDGLOBALSDIALOG_H
#define ADDGLOBALSDIALOG_H

#include "ui_addglobalsdialog.h"

class QComboBox;

typedef QPair<QLineEdit*, QLineEdit*> lineEditsPair;

class addGlobalsDialog : public QDialog, private Ui::addGlobalsDialog
{
	Q_OBJECT
	
public:
	explicit addGlobalsDialog(QWidget *parent = 0, int variablesCount=1, QStringList modules=QStringList());
	QList<lineEditsPair> assignmentsLineEditsList;
	QComboBox *modulesComboBox;
};

#endif // ADDGLOBALSDIALOG_H

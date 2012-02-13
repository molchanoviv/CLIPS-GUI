#ifndef ADDCLASSDIALOG_H
#define ADDCLASSDIALOG_H

#include "ui_addclassdialog.h"

#include <QLineEdit>
#include <QList>
#include <QComboBox>

class addClassDialog : public QDialog, public Ui::addClassDialog
{
	Q_OBJECT
	
public:
	explicit addClassDialog(QWidget *parent = 0, int parentsCount=0, int slotsCount=0, int handlersCount=0, QStringList classesList = QStringList());
	QList<QLineEdit*> slotsList;
	QList<QLineEdit*> handlerDocumentationList;
	QList<QComboBox*> isAList;

};

#endif // ADDCLASSDIALOG_H

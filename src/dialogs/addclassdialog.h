#ifndef ADDCLASSDIALOG_H
#define ADDCLASSDIALOG_H

#include "ui_addclassdialog.h"

#include <QLineEdit>
#include <QList>
#include <QComboBox>

typedef struct
{
	QLineEdit *nameLineEdit;
	QLineEdit *facetLineEdit;
	QLineEdit *messageHandlerLineEdit;
} slot;

class addClassDialog : public QDialog, public Ui::addClassDialog
{
	Q_OBJECT
	
public:
	explicit addClassDialog(QWidget *parent = 0, int parentsCount=0, int slotsCount=0, QStringList classesList = QStringList());
//	QList <slot*> slotsList;
	QList<QComboBox*> isAList;

};

#endif // ADDCLASSDIALOG_H

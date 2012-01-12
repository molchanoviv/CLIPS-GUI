#ifndef ADDTEMPLATEDIALOG_H
#define ADDTEMPLATEDIALOG_H

#include "ui_addtemplatedialog.h"

class QCheckBox;
class QLineEdit;

class addTemplateDialog : public QDialog, private Ui::addTemplateDialog
{
	Q_OBJECT
	
public:
	explicit addTemplateDialog(QWidget *parent = 0, int slotsCount=1);
	QList<QCheckBox *> checkBoxList;
	QList<QLineEdit *> lineEditList;
	QLineEdit *nameLineEdit;
};

#endif // ADDTEMPLATEDIALOG_H

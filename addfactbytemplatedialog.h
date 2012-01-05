#ifndef ADDFACTBYTEMPLATEDIALOG_H
#define ADDFACTBYTEMPLATEDIALOG_H

#include "ui_addfactbytemplatedialog.h"
class QLineEdit;

typedef QPair<bool, QString> slotsPair;

class addFactByTemplateDialog : public QDialog, private Ui::addFactByTemplateDialog
{
	Q_OBJECT
	
public:
	explicit addFactByTemplateDialog(QWidget *parent = 0, QList<slotsPair> *slotsList= 0);
	QList<QLineEdit *> lineEditList;
};

#endif // ADDFACTBYTEMPLATEDIALOG_H

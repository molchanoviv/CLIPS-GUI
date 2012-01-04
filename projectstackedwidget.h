#ifndef PROJECTSTACKEDWIDGET_H
#define PROJECTSTACKEDWIDGET_H

#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QGroupBox>
#include <QLabel>
#include <QWidget>
#include <QStringList>

typedef QPair<bool, QString> slotsPair;

class ProjectStackedWidget : public QStackedWidget
{
	Q_OBJECT
public:
	explicit ProjectStackedWidget(QWidget *parent = 0);
	QListWidget *templatesListWidget;
	QListWidget *factsListWidget;
	QListWidget *rulesListWidget;
	QListWidget *functionsListWidget;
	QListWidget *classesListWidget;

private:


signals:
	void addFactSignal(QString, bool);
	void setFactDuplicationSignal(bool, bool);
	void removeFactSignal(int, bool);
	void addTemplateSignal(QString, QList<slotsPair>);
	void removeTemplateSignal(QString, bool);

public slots:
	void refreshFacts(QStringList);
	void addFactSlot();
	void removeFactSlot();
	void duplicationProxySlot(bool);
	void clearSlot();
	void addTemplateSlot();
	void removeTemplateSlot();
	void refreshTemplates(QStringList);

};

#endif // PROJECTSTACKEDWIDGET_H

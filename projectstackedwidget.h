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

public slots:
	void refreshFacts(QString);
	void addFactSlot();
	void removeFactSlot();
	void duplicationProxySlot(bool);
	void clearSlot();

};

#endif // PROJECTSTACKEDWIDGET_H

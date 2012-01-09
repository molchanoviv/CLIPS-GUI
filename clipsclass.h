#ifndef CLIPSCLASS_H
#define CLIPSCLASS_H

#include <clips/clips.h>
#include <QtCore>

typedef QPair<bool, QString> slotsPair;

class CLIPSClass : public QObject
{
	Q_OBJECT
public:
	explicit CLIPSClass(QObject *parent = 0);

public slots:
	void assertStringSlot(QString, bool);
	void assertSlot(QString, QList<slotsPair>, bool);
	QStringList templatesSlot(bool);
	QStringList factsSlot(bool);
	QStringList factsListSlot(bool);
	QStringList rulesSlot(bool);
	QStringList agendaSlot(bool);
	QStringList globalsSlot(bool);
	void retractSlot(int, bool);
	void saveFactsSlot(QString);
	void loadFactsSlot(QString);
	void saveSlot(QString);
	void bSaveSlot(QString);
	void loadSlot(QString);
	void bLoadSlot(QString);
	void clearSlot();
	void setFactDuplicationSlot(bool, bool);
	void deftemplateSlot(QString, QList<slotsPair>);
	void deffactsSlot(QString, QStringList);
	void unDeftemplateSlot(QString, bool);
	void unDeffactsSlot(QString, bool);
	void unDefruleSlot(QString, bool);
	void SetBreakSlot(QString, bool);
	void RemoveBreakSlot(QString, bool);
	void defRuleSlot(QString, QString, QString, QStringList, QStringList);
	QList<slotsPair> getTemplateInformation(QString);
	void runSlot();
	void removeActivationSlot(QString, bool);
	int getActivationSalienceSlot(QString);
	void setActivationSalienceSlot(QString, int, bool);
	QHash<QString, int> getStrategyes();
	int getStrategy();
	void setStrategySlot(int, bool);
	void defglobalSlot(QString, QHash<QString, QString>);
	void unDefglobalSlot(QString, bool);
	QStringList getModules();
	QString getGlobalInformation(QString);

signals:
	void outputSignal(QString);
	void factsChangedSignal(QStringList);
	void deffactsChangedSignal(QStringList);
	void templatesChangedSignal(QStringList);
	void rulesChangedSignal(QStringList);
	void activationsChangedSignal(QStringList);
	void globalsChangedSignal(QStringList);
	void clearSignal();

protected:

};

#endif // CLIPSCLASS_H

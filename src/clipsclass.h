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
	void saveFactsSlot(QString);
	void loadFactsSlot(QString);
	void saveSlot(QString);
	void bSaveSlot(QString);
	void loadSlot(QString);
	void bLoadSlot(QString);
	void clearSlot();
	void exec(QString);
	//Templates
	QStringList templatesSlot();
	void deftemplateSlot(QString, QList<slotsPair>);
	void unDeftemplateSlot(QString);
	QString getTemplatePPF(QString);
	QList<slotsPair> getTemplateInformation(QString);
	//Facts
	QStringList factsSlot();
	void assertStringSlot(QString);
	void assertSlot(QString, QList<slotsPair>);
	void retractSlot(int);
	void setFactDuplicationSlot(bool);
	//Facts List
	QStringList factsListSlot();
	void deffactsSlot(QString, QStringList);
	void unDeffactsSlot(QString);
	QString getDeffactsPPF(QString);
	//Rules
	QStringList rulesSlot();
	void defRuleSlot(QString, QString, QString, QStringList, QStringList);
	void unDefruleSlot(QString);
	QString getRulePPF(QString);
	void SetBreakSlot(QString);
	void RemoveBreakSlot(QString);
	//Agenda
	QStringList agendaSlot();
	void removeActivationSlot(QString);
	void runSlot();
	int getActivationSalienceSlot(QString);
	void setActivationSalienceSlot(QString, int);
	QHash<QString, int> getStrategyes();
	int getStrategy();
	void setStrategySlot(int);
	//Globals
	QStringList globalsSlot();
	void defglobalSlot(QString, QHash<QString, QString>);
	void unDefglobalSlot(QString);
	QString getGlobalPPF(QString);
	//Functions
	QStringList functionsSlot();
	void deffunctionSlot(QString, QString, QString, QString, QString);
	void unDeffunctionSlot(QString);
	QString getFunctionPPF(QString);
	//Generic Functions
	QStringList genericSlot();
	void defgenericSlot(QString);
	void unDefgenericSlot(QString);
	QString getGenericPPF(QString);
	//Methods
	QHash<QString, int> methodsSlot();
	void defmethodSlot(QString, QString, QString, QString, QString, QString);
	void unDefmethodSlot(QString, int);
	QString getMethodPPF(QString, int);
	//Classes
	/*******/
	//Message Handlers
	/*******/
	//Modules
	QStringList getModules();

signals:
	void templatesChangedSignal(QStringList);
	void factsChangedSignal(QStringList);
	void deffactsChangedSignal(QStringList);
	void rulesChangedSignal(QStringList);
	void activationsChangedSignal(QStringList);
	void globalsChangedSignal(QStringList);
	void functionsChangedSignal(QStringList);
	void genericChangedSignal(QStringList);
	void methodsChangedSignal(QHash<QString, int>);
	void clearSignal();

protected:

};

#endif // CLIPSCLASS_H

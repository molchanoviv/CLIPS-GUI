#ifndef CLIPSCLASS_H
#define CLIPSCLASS_H

#include <clips/clips.h>
#include <QtCore>

#define CLIPS	static_cast<CLIPSClass*>(GetEnvironmentContext(Environment))

typedef QPair<bool, QString> slotsPair;

class CLIPSClass : public QObject
{
	Q_OBJECT
public:
	explicit CLIPSClass(QObject *parent = 0);
	~CLIPSClass();

public slots:
	void saveSlot(QString);
	void loadSlot(QString);
	void clearSlot();
	void executeCommand(QString);
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
	QStringList classesSlot();
	void unDefclassSlot(QString);
	QString getClassPPF(QString);
	QString getMetaInformation(QString);
	QString getSubclasses(QString);
	QString getSuperclasses(QString);
	unsigned short getCurrentDefaultsMode();
	QHash<QString, unsigned short> getDefaultsModes();
	unsigned short setDefaultsMode(unsigned short);
	//Message Handlers
	void defmessageHandlerSlot(QString, QString, QString, QString, QString, QString, QString);
	QHash<QString, unsigned int> messageHandlersSlot();
	void unDefmessageHandlerSlot(QString, unsigned int);
	QString getMessageHandlerPPF(QString, unsigned int);
	QStringList getHandlerTypesSlot();
	//Instances
	QStringList instancesSlot();
	void definstanceSlot(QString, QString, QString, QString);
	void unDefinstancesSlot(QString);
	QString getInstancePPF(QString);
	//Modules
	QStringList modulesSlot();
	void defmoduleSlot(QString, QString, QString);
	QString getModulePPF(QString);
	QString getCurrentModule();
	void setCurrentModule(QString);

private slots:


signals:
	void templatesChangedSignal(QStringList);
	void factsChangedSignal(QStringList);
	void restoreFactDuplicationSignal(bool);
	void deffactsChangedSignal(QStringList);
	void rulesChangedSignal(QStringList);
	void activationsChangedSignal(QStringList);
	void globalsChangedSignal(QStringList);
	void functionsChangedSignal(QStringList);
	void genericChangedSignal(QStringList);
	void methodsChangedSignal(QHash<QString, int>);
	void classesChangedSignal(QStringList);
	void messageHandlersChangedSignal(QHash<QString, unsigned int>);
	void instancesChangedSignal(QStringList);
	void modulesChangedSignal(QStringList);
	void dataChanged();
	void clearSignal();
	void refreshAll();
	void outputSignal(QString);

protected:
	void* Environment;
	static int queryFunction(void*, char*);
	static int printFunction(void*,char*, char*);
	QString answer;
};

#endif // CLIPSCLASS_H

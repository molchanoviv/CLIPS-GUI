#ifndef CLIPSCLASS_H
#define CLIPSCLASS_H

#include <clips/clips.h>
#include <QtCore>
#include <QLineEdit>
#include <QHash>

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
	void fillHashes();
	void removeSlot(QString, QString, int index=0);
	QString getPPF(QString, QString, int index=0);
	QStringList itemsSlot(QString);
	//Templates
	void deftemplateSlot(QString, QList<slotsPair>);
	QList<slotsPair> getTemplateInformation(QString);
	//Facts
	void assertStringSlot(QString);
	void assertSlot(QString, QList<slotsPair>);
	void retractSlot(int);
	void setFactDuplicationSlot(bool);
	//Facts List
	void deffactsSlot(QString, QStringList);
	//Rules
	void defRuleSlot(QString, QString, QString, QStringList, QStringList);
	void SetBreakSlot(QString);
	void RemoveBreakSlot(QString);
	//Agenda
	void removeActivationSlot(QString);
	void runSlot();
	int getActivationSalienceSlot(QString);
	void setActivationSalienceSlot(QString, int);
	QHash<QString, int> getStrategyes();
	int getStrategy();
	void setStrategySlot(int);
	//Globals
	void defglobalSlot(QString, QHash<QString, QString>);
	//Functions
	void deffunctionSlot(QString, QString, QString, QString, QString);
	//Generic Functions
	void defgenericSlot(QString);
	//Methods
	QHash<QString, int> methodsSlot();
	void defmethodSlot(QString, QString, QString, QString, QString, QString);
	//Classes
	void defclassSlot(QString, QString, QString, QString, QStringList, QStringList, QStringList);
	QString getMetaInformation(QString);
	QString getSubclasses(QString);
	QString getSuperclasses(QString);
	unsigned short getCurrentDefaultsMode();
	QHash<QString, unsigned short> getDefaultsModes();
	unsigned short setDefaultsMode(unsigned short);
	//Message Handlers
	void defmessageHandlerSlot(QString, QString, QString, QString, QString, QString, QString);
	QHash<QString, unsigned int> messageHandlersSlot();
	QStringList getHandlerTypesSlot();
	//Instances
	void definstanceSlot(QString, QString, QString, QString);
	//Modules
	void defmoduleSlot(QString, QString, QString);
	QString getCurrentModule();
	void setCurrentModule(QString);

private slots:


signals:
	void restoreFactDuplicationSignal(bool);
	void methodsChangedSignal(QHash<QString, int>);
	void messageHandlersChangedSignal(QHash<QString, unsigned int>);
	void dataChanged();
	void clearSignal();
	void refreshAll();
	void outputSignal(QString);

protected:
	void* Environment;
	static int queryFunction(void*, char*);
	static int printFunction(void*,char*, char*);
	QString answer;
	QHash<QString, int(*)(void*, void*)> removeFunctionsHash;
	QHash<QString, void*(*)(void*, char*)> findFunctionsHash;
	QHash<QString, int(*)(void*, void*)> isDeletableFunctionsHash;
	QHash<QString, void*(*)(void*, void*)> getNextFunctionsHash;
};

#endif // CLIPSCLASS_H

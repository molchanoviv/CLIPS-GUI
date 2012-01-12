#include <iostream>
#include "clipsclass.h"
#include <QRegExpValidator>

CLIPSClass::CLIPSClass(QObject *parent) :
	QObject(parent)
{
	InitializeEnvironment();
}

void CLIPSClass::exec(QString command)
{
	QFile file(QDir::tempPath()+"/tmpfile");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;
	QTextStream out(&file);
	out<<command;
	QString path = file.fileName();
	file.close();
	Load(path.toLocal8Bit().data());
	file.remove();
}

void CLIPSClass::saveFactsSlot(QString path)
{
	SaveFacts(path.toLocal8Bit().data(),LOCAL_SAVE,NULL);
}

void CLIPSClass::loadFactsSlot(QString path)
{
	LoadFacts(path.toLocal8Bit().data());
	QStringList facts = factsSlot();
	emit factsChangedSignal(facts);
}

void CLIPSClass::saveSlot(QString path)
{
	Save(path.toLocal8Bit().data());
}

void CLIPSClass::bSaveSlot(QString path)
{
	Bsave(path.toLocal8Bit().data());
}

void CLIPSClass::loadSlot(QString path)
{
	Load(path.toLocal8Bit().data());
	QStringList facts = factsSlot();
	emit factsChangedSignal(facts);
	QStringList templates = templatesSlot();
	emit templatesChangedSignal(templates);
}

void CLIPSClass::bLoadSlot(QString path)
{
	BloadData(path.toLocal8Bit().data());
}

void CLIPSClass::clearSlot()
{
	Clear();
	emit clearSignal();
}

//Templates

void CLIPSClass::deftemplateSlot(QString name, QList<slotsPair> slotsList)
{
	QString slotsstr;
	QString slot;
	for(int i=0; i<slotsList.count(); i++)
	{
		if(slotsList.at(i).first)
			slot = "multislot";
		else
			slot = "slot";
		slotsstr += "( "+slot+" "+slotsList.at(i).second+" ) ";
	}
	QString command = "(deftemplate "+name+" "+slotsstr+")";
	exec(command);
	QStringList templates = templatesSlot();
	emit templatesChangedSignal(templates);
}

void CLIPSClass::unDeftemplateSlot(QString name)
{
	void* tmplPtr = FindDeftemplate(name.simplified().toLocal8Bit().data());
	if(!IsDeftemplateDeletable(tmplPtr))
		return;
	Undeftemplate(tmplPtr);
	QStringList templates = templatesSlot();
	emit templatesChangedSignal(templates);
}

QList<slotsPair> CLIPSClass::getTemplateInformation(QString name)
{
	QList<slotsPair> info;
	DATA_OBJECT sltVal;
	void* tmplPtr = FindDeftemplate(name.toLocal8Bit().data());
	DeftemplateSlotNames(tmplPtr, &sltVal);
	void *multifieldPtr;
	char *sltName;
	multifieldPtr = GetValue(sltVal);
	for (int i = GetDOBegin(sltVal); i <= GetDOEnd(sltVal); i++)
	{
		if ((GetMFType(multifieldPtr,i) == STRING) ||(GetMFType(multifieldPtr,i) == SYMBOL))
		{
			sltName = ValueToString(GetMFValue(multifieldPtr,i));
			bool ok = DeftemplateSlotMultiP(tmplPtr, sltName);
			info.append(slotsPair(ok, QString(sltName)));
		}
	}
	return info;
}

QString CLIPSClass::getTemplatePPF(QString name)
{
	void* deftemplatePtr = FindDeftemplate(name.simplified().toLocal8Bit().data());
	char *deftemplateName = GetDeftemplatePPForm(deftemplatePtr);
	return QString(deftemplateName).simplified();
}

QStringList CLIPSClass::templatesSlot()
{
	QStringList templatesList;
	void* ptr=NULL;
	do
	{
		ptr = GetNextDeftemplate(ptr);
		if(ptr!=NULL)
		{
			char* buf = GetDeftemplateName(ptr);
			templatesList<<QString(buf);
		}
	}
	while(ptr!=NULL);
	return templatesList;
}

//Facts

void CLIPSClass::assertStringSlot(QString fact)
{
	fact.append(")").prepend("(");
	AssertString(fact.toLocal8Bit().data());
	QStringList facts = factsSlot();
	emit factsChangedSignal(facts);
	QStringList templates = templatesSlot();
	emit templatesChangedSignal(templates);
	QStringList activations = agendaSlot();
	emit activationsChangedSignal(activations);
}

void CLIPSClass::assertSlot(QString templateName, QList<slotsPair> slotsList)
{
	QRegExp floatRx("[0-9]+[\\.][0-9]*");
	QRegExp intRx("[0-9]*");
	void *newFact;
	void *templatePtr;
	void *theMultifield;
	DATA_OBJECT theValue;
	IncrementGCLocks();
	templatePtr = FindDeftemplate(templateName.toLocal8Bit().data());
	newFact = CreateFact(templatePtr);
	if (newFact == NULL)
		return;
	DATA_OBJECT sltVal;
	QStringList sltNames;
	DeftemplateSlotNames(templatePtr, &sltVal);
	void *multifieldPtr;
	char *sltName;
	multifieldPtr = GetValue(sltVal);
	for (int i = GetDOBegin(sltVal); i <= GetDOEnd(sltVal); i++)
	{
		if ((GetMFType(multifieldPtr,i) == STRING) ||(GetMFType(multifieldPtr,i) == SYMBOL))
		{
			sltName = ValueToString(GetMFValue(multifieldPtr,i));
			sltNames.append(QString(sltName));
		}
	}
	for(int i=0; i<slotsList.count(); i++)
	{
		if(!slotsList.at(i).first)
		{
			QRegExpValidator validator(floatRx, 0);
			int pos = 0;
			QString slotVal = slotsList.at(i).second;
			if(validator.validate(slotVal, pos) != QValidator::Acceptable)
			{
				QRegExpValidator validator(intRx, 0);
				if(validator.validate(slotVal, pos) != QValidator::Acceptable)
				{
					theValue.type = SYMBOL;
					theValue.value = AddSymbol(slotVal.toLocal8Bit().data());
				}
				else
				{
					theValue.type = FLOAT;
					theValue.value = AddDouble(slotVal.toFloat());
				}
			}
			else
			{
				theValue.type = INTEGER;
				theValue.value = AddLong(slotVal.toInt());
			}
			PutFactSlot(newFact, sltNames.at(i).toLocal8Bit().data(), &theValue);
		}
		else
		{
			QStringList mltSltVal = slotsList.at(i).second.split(" ");
			if(mltSltVal.isEmpty())
				return;
			theMultifield = CreateMultifield(mltSltVal.count());

			for(int t=0; t<mltSltVal.count(); t++)
			{
				QRegExpValidator validator(floatRx, 0);
				int pos = 0;
				QString slotVal = slotsList.at(t).second;
				if(validator.validate(slotVal, pos) != QValidator::Acceptable)
				{
					QRegExpValidator validator(intRx, 0);
					if(validator.validate(slotVal, pos) != QValidator::Acceptable)
					{
						SetMFType(theMultifield,t+1,SYMBOL);
						SetMFValue(theMultifield,t+1,AddSymbol(mltSltVal.at(t).toLocal8Bit().data()));
					}
					else
					{
						SetMFType(theMultifield,t+1,FLOAT);
						SetMFValue(theMultifield,t+1,AddDouble(mltSltVal.at(t).toFloat()));
					}
				}
				else
				{
					SetMFType(theMultifield,t+1,INTEGER);
					SetMFValue(theMultifield,t+1,AddLong(mltSltVal.at(t).toInt()));
				}
			}
			SetDOBegin(theValue,1);
			SetDOEnd(theValue,mltSltVal.count()+1);
			theValue.type = MULTIFIELD;
			theValue.value = theMultifield;
			PutFactSlot(newFact, sltNames.at(i).toLocal8Bit().data(), &theValue);
		}
	}
	AssignFactSlotDefaults(newFact);
	DecrementGCLocks();
	Assert(newFact);
	QStringList facts = factsSlot();
	emit factsChangedSignal(facts);
	QStringList templates = templatesSlot();
	emit templatesChangedSignal(templates);
	QStringList activations = agendaSlot();
	emit activationsChangedSignal(activations);
}

void CLIPSClass::retractSlot(int factNumber)
{
	void* ptr=NULL;
	do
	{
		ptr = GetNextFact(ptr);
		if(ptr!=NULL)
		{
			if(factNumber == FactIndex(ptr))
			{
				Retract(ptr);
				QStringList facts = factsSlot();
				emit factsChangedSignal(facts);
				QStringList activations = agendaSlot();
				emit activationsChangedSignal(activations);
			}
		}
	}
	while(ptr!=NULL);
}

QStringList CLIPSClass::factsSlot()
{
	QStringList factsList;
	void* ptr=NULL;
	do
	{
		ptr = GetNextFact(ptr);
		char buf[16384]={0};
		if(ptr!=NULL)
		{
			GetFactPPForm(buf,sizeof(buf), ptr);
			factsList<<QString(buf);
		}
	}
	while(ptr!=NULL);
	return factsList;
}

void CLIPSClass::setFactDuplicationSlot(bool state)
{
	SetFactDuplication(state);
}

//Facts Lists

void CLIPSClass::deffactsSlot(QString name, QStringList factsList)
{
	QString factsstr;

	for(int i=0; i<factsList.count(); i++)
	{
		factsstr += "( "+factsList.at(i)+" ) ";
	}
	QString command = "(deffacts "+name+" "+factsstr+")";
	exec(command);
	QStringList deffacts = factsListSlot();
	emit deffactsChangedSignal(deffacts);
	QStringList templates = templatesSlot();
	emit templatesChangedSignal(templates);
	QStringList activations = agendaSlot();
	emit activationsChangedSignal(activations);
}

void CLIPSClass::unDeffactsSlot(QString name)
{
	void* tmplPtr = FindDeffacts(name.simplified().toLocal8Bit().data());
	if(!IsDeffactsDeletable(tmplPtr))
		return;
	Undeffacts(tmplPtr);
	QStringList deffacts = factsListSlot();
	emit deffactsChangedSignal(deffacts);
	QStringList templates = templatesSlot();
	emit templatesChangedSignal(templates);
	QStringList activations = agendaSlot();
	emit activationsChangedSignal(activations);
}

QString CLIPSClass::getDeffactsPPF(QString name)
{
	void* deffactsPtr = FindDeffacts(name.simplified().toLocal8Bit().data());
	char *deffactsName = GetDeffactsPPForm(deffactsPtr);
	return QString(deffactsName).simplified();
}

QStringList CLIPSClass::factsListSlot()
{
	QStringList deffactsList;
	void* ptr=NULL;
	do
	{
		ptr = GetNextDeffacts(ptr);
		if(ptr!=NULL)
		{
			char* buf = GetDeffactsName(ptr);
			deffactsList<<QString(buf);
		}
	}
	while(ptr!=NULL);
	return deffactsList;
}

//Rules

void CLIPSClass::defRuleSlot(QString name, QString comment, QString declaration, QStringList antecedentList, QStringList concequentList)
{
	QString antecedentsStr;
	QString consequentsStr;
	for(int i=0; i<antecedentList.count(); i++)
		antecedentsStr += "( "+antecedentList.at(i)+" ) ";
	for(int i=0; i<concequentList.count(); i++)
		consequentsStr += "( "+concequentList.at(i)+" ) ";
	if(!comment.isEmpty())
		comment = "\""+comment+"\"";
	if(!declaration.isEmpty())
		declaration = "("+declaration+")";
	QString command = "(defrule "+name+" "+comment+" "+declaration+" "+antecedentsStr+"=>"+consequentsStr+")";
	exec(command);
	QStringList rules = rulesSlot();
	emit rulesChangedSignal(rules);
	QStringList templates = templatesSlot();
	emit templatesChangedSignal(templates);
	QStringList activations = agendaSlot();
	emit activationsChangedSignal(activations);
}

void CLIPSClass::unDefruleSlot(QString name)
{
	void* tmplPtr = FindDefrule(name.simplified().toLocal8Bit().data());
	if(!IsDefruleDeletable(tmplPtr))
		return;
	Undefrule(tmplPtr);
	QStringList rules = rulesSlot();
	emit rulesChangedSignal(rules);
	QStringList activations = agendaSlot();
	emit activationsChangedSignal(activations);
}

void CLIPSClass::SetBreakSlot(QString name)
{
	SetBreak(FindDefrule(name.toLocal8Bit().data()));
	QStringList rules = rulesSlot();
	emit rulesChangedSignal(rules);
}

void CLIPSClass::RemoveBreakSlot(QString name)
{
	RemoveBreak(FindDefrule(name.toLocal8Bit().data()));
	QStringList rules = rulesSlot();
	emit rulesChangedSignal(rules);
}

QString CLIPSClass::getRulePPF(QString name)
{
	void* rulePtr = FindDefrule(name.simplified().toLocal8Bit().data());
	char *ruleName = GetDefrulePPForm(rulePtr);
	return QString(ruleName).simplified();
}

QStringList CLIPSClass::rulesSlot()
{
	QStringList rulesList;
	void* ptr=NULL;
	do
	{
		ptr = GetNextDefrule(ptr);
		if(ptr!=NULL)
		{
			char* buf = GetDefruleName(ptr);
			rulesList<<QString(buf);
		}
	}
	while(ptr!=NULL);
	return rulesList;
}

//Agenda

void CLIPSClass::runSlot()
{
	Run(-1);
	QStringList templates = templatesSlot();
	emit templatesChangedSignal(templates);
	QStringList facts = factsSlot();
	emit factsChangedSignal(facts);
	QStringList deffacts = factsListSlot();
	emit deffactsChangedSignal(deffacts);
	QStringList rules = rulesSlot();
	emit rulesChangedSignal(rules);
	QStringList activations = agendaSlot();
	emit activationsChangedSignal(activations);
}

void CLIPSClass::removeActivationSlot(QString name)
{
	void* ptr=NULL;
	do
	{
		ptr = GetNextActivation(ptr);
		char buf[16384]={0};
		if(ptr!=NULL)
		{
			GetActivationPPForm(buf,sizeof(buf), ptr);
			QString bufVal(buf);
			if(bufVal == name)
			{
				DeleteActivation(ptr);
				QStringList activations = agendaSlot();
				emit activationsChangedSignal(activations);
			}
		}
	}
	while(ptr!=NULL);
}

int CLIPSClass::getActivationSalienceSlot(QString name)
{
	void* ptr=NULL;
	do
	{
		ptr = GetNextActivation(ptr);
		char buf[16384]={0};
		if(ptr!=NULL)
		{
			GetActivationPPForm(buf,sizeof(buf), ptr);
			QString bufVal(buf);
			if(bufVal == name)
			{
				int salience = GetActivationSalience(ptr);
				return salience;
			}
		}
	}
	while(ptr!=NULL);
	return 0;
}

void CLIPSClass::setActivationSalienceSlot(QString name, int salience)
{
	void* ptr=NULL;
	do
	{
		ptr = GetNextActivation(ptr);
		char buf[16384]={0};
		if(ptr!=NULL)
		{
			GetActivationPPForm(buf,sizeof(buf), ptr);
			QString bufVal(buf);
			if(bufVal == name)
			{
				SetActivationSalience(ptr, salience);
				ReorderAgenda(NULL);
				QStringList activations = agendaSlot();
				emit activationsChangedSignal(activations);
			}
		}
	}
	while(ptr!=NULL);
}

QHash<QString, int> CLIPSClass::getStrategyes()
{
	QHash<QString, int> strategyes;
	strategyes.insert(tr("DEPTH_STRATEGY"), DEPTH_STRATEGY);
	strategyes.insert(tr("BREADTH_STRATEGY"), BREADTH_STRATEGY);
	strategyes.insert(tr("LEX_STRATEGY"), LEX_STRATEGY);
	strategyes.insert(tr("MEA_STRATEGY"), MEA_STRATEGY);
	strategyes.insert(tr("COMPLEXITY_STRATEGY"), COMPLEXITY_STRATEGY);
	strategyes.insert(tr("SIMPLICITY_STRATEGY"), SIMPLICITY_STRATEGY);
	strategyes.insert(tr("RANDOM_STRATEGY"), RANDOM_STRATEGY);
	return strategyes;
}

int CLIPSClass::getStrategy()
{
	return GetStrategy();
}

void CLIPSClass::setStrategySlot(int strategy)
{
	SetStrategy(strategy);
}

QStringList CLIPSClass::agendaSlot()
{
	RefreshAgenda(NULL);
	QStringList activationsList;
	void* ptr=NULL;
	do
	{
		ptr = GetNextActivation(ptr);
		char buf[16384]={0};
		if(ptr!=NULL)
		{
			GetActivationPPForm(buf,sizeof(buf), ptr);
			activationsList<<QString(buf);
		}
	}
	while(ptr!=NULL);
	return activationsList;
}

//Globals

void CLIPSClass::defglobalSlot(QString moduleName, QHash<QString, QString> defglobalsHash)
{
	QString globalsStr;
	QHashIterator<QString, QString> i(defglobalsHash);
	QRegExp rx("^\\?\\*.*\\*$");
	while (i.hasNext())
	{
		i.next();
		QString str = i.key();
		if(!str.contains(rx))
			str = "?*"+str+"*";
		globalsStr += str+" = "+i.value()+" ";
	}
	QString command = "(defglobal "+moduleName+" "+globalsStr+")";
	exec(command);
	QStringList globals = globalsSlot();
	emit globalsChangedSignal(globals);
}

void CLIPSClass::unDefglobalSlot(QString name)
{
	void* globalPtr = FindDefglobal(name.simplified().toLocal8Bit().data());
	if(!IsDefglobalDeletable(globalPtr))
		return;
	Undefglobal(globalPtr);
	QStringList globals = globalsSlot();
	emit globalsChangedSignal(globals);
}

QString CLIPSClass::getGlobalPPF(QString name)
{
	void* globalPtr = FindDefglobal(name.simplified().toLocal8Bit().data());
	char *globalsName = GetDefglobalPPForm(globalPtr);
	return QString(globalsName).simplified();
}

QStringList CLIPSClass::globalsSlot()
{
	QStringList globalsList;
	void* ptr=NULL;
	do
	{
		ptr = GetNextDefglobal(ptr);
		if(ptr!=NULL)
		{
			char *globalsStr = GetDefglobalName(ptr);
			globalsList<<QString(globalsStr).simplified();
		}
	}
	while(ptr!=NULL);
	return globalsList;
}

//Functions

void CLIPSClass::deffunctionSlot(QString name, QString comment, QString regular, QString wildcard, QString expression)
{
	if(!comment.isEmpty())
		comment = "\""+comment+"\"";
	QString command = "(deffunction "+name+" "+comment+" ("+regular+" "+wildcard+") "+expression+")";
	exec(command);
	QStringList functions = functionsSlot();
	emit functionsChangedSignal(functions);
}

void CLIPSClass::unDeffunctionSlot(QString name)
{
	void* functionPtr = FindDeffunction(name.simplified().toLocal8Bit().data());
	if(!IsDeffunctionDeletable(functionPtr))
		return;
	Undeffunction(functionPtr);
	QStringList functions = functionsSlot();
	emit functionsChangedSignal(functions);
}

QString CLIPSClass::getFunctionPPF(QString name)
{
	void* functionPtr = FindDeffunction(name.simplified().toLocal8Bit().data());
	char *functionName = GetDeffunctionPPForm(functionPtr);
	return QString(functionName).simplified();
}

QStringList CLIPSClass::functionsSlot()
{
	QStringList functionsList;
	void* ptr=NULL;
	do
	{
		ptr = GetNextDeffunction(ptr);
		if(ptr!=NULL)
		{
			char *functionStr = GetDeffunctionName(ptr);
			functionsList<<QString(functionStr).simplified();
		}
	}
	while(ptr!=NULL);
	return functionsList;
}

//Generic Functions

void CLIPSClass::defgenericSlot(QString name)
{
	QString command = "(defgeneric "+name+")";
	exec(command);
	QStringList generic = genericSlot();
	emit genericChangedSignal(generic);
	QHash<QString, int> methods = methodsSlot();
	emit methodsChangedSignal(methods);
}

void CLIPSClass::unDefgenericSlot(QString name)
{
	void* genericPtr = FindDefgeneric(name.simplified().toLocal8Bit().data());
	if(!IsDefgenericDeletable(genericPtr))
		return;
	Undefgeneric(genericPtr);
	QStringList generic = genericSlot();
	emit genericChangedSignal(generic);
	QHash<QString, int> methods = methodsSlot();
	emit methodsChangedSignal(methods);
}

QString CLIPSClass::getGenericPPF(QString name)
{
	void* genericPtr = FindDefgeneric(name.simplified().toLocal8Bit().data());
	char *genericName = GetDefgenericPPForm(genericPtr);
	return QString(genericName).simplified();
}

QStringList CLIPSClass::genericSlot()
{
	QStringList genericList;
	void* ptr=NULL;
	do
	{
		ptr = GetNextDefgeneric(ptr);
		if(ptr!=NULL)
		{
			char *genericStr = GetDefgenericName(ptr);
			genericList<<QString(genericStr).simplified();
		}
	}
	while(ptr!=NULL);
	return genericList;
}

//Methods

void CLIPSClass::defmethodSlot(QString name, QString index, QString comment, QString regular, QString wildcard, QString expression)
{
	if(!comment.isEmpty())
		comment = "\""+comment+"\"";
	QString command = "(defmethod "+name+" "+index+" "+comment+" ("+regular+" "+wildcard+") "+expression+")";
	exec(command);
	QStringList generic = genericSlot();
	emit genericChangedSignal(generic);
	QHash<QString, int> methods = methodsSlot();
	emit methodsChangedSignal(methods);
}

void CLIPSClass::unDefmethodSlot(QString name, int index)
{

	void* genericPtr = FindDefgeneric(name.simplified().toLocal8Bit().data());
	if(IsDefmethodDeletable(genericPtr,index))
		return;
	Undefmethod(genericPtr, index);
	QHash<QString, int> methods = methodsSlot();
	emit methodsChangedSignal(methods);
}

QString CLIPSClass::getMethodPPF(QString name, int index)
{
	void* genericPtr = FindDefgeneric(name.simplified().toLocal8Bit().data());
	char *methodName = GetDefmethodPPForm(genericPtr,index);
	return QString(methodName).simplified();
}

QHash<QString, int> CLIPSClass::methodsSlot()
{
	QHash<QString, int> methodsHash;
	QStringList generics = genericSlot();
	QString str;
	foreach(str, generics)
	{
		void* genericPtr = FindDefgeneric(str.simplified().toLocal8Bit().data());
		int index=0;
		do
		{
			index = GetNextDefmethod(genericPtr, index);
			if(index!=0)
				methodsHash.insert(str, index);
		}
		while(index!=0);
	}
	return methodsHash;
}

//Classes

/*****/

//Message Handlers

/*****/

//Modules

QStringList CLIPSClass::getModules()//Временная заглушка
{
	QStringList modulesList;
	modulesList<<"MAIN";
	return modulesList;
}

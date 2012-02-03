#include <iostream>
#include "clipsclass.h"
#include <QRegExpValidator>

CLIPSClass::CLIPSClass(QObject *parent) :
	QObject(parent)
{
//	InitializeEnvironment();
	Environment = CreateEnvironment();
	SetEnvironmentContext(Environment, this);
	EnvAddRouter(Environment,"IORouter",40,queryFunction,printFunction,NULL,NULL,NULL);
	EnvActivateRouter(Environment,"IORouter");
	SetPrintWhileLoading(Environment,false);
}

CLIPSClass::~CLIPSClass()
{
	DestroyEnvironment(Environment);
}

void CLIPSClass::executeCommand(QString command)
{
	answer.clear();
	SetCommandString(Environment, command.toUtf8().data());
	RouteCommand(Environment,CommandLineData(Environment)->CommandString,true);
	emit outputSignal(answer);
	emit dataChanged();
}

int CLIPSClass::queryFunction(void* Environment, char* logicalName)
{
	Q_UNUSED(Environment);
	if (	(qstrcmp(logicalName,"stdout") == 0)	||
		(qstrcmp(logicalName,"stdin") == 0)	||
		(qstrcmp(logicalName,"wclips") == 0)	||
		(qstrcmp(logicalName,"wdisplay") == 0)	||
		(qstrcmp(logicalName,"wdialog") == 0)	||
		(qstrcmp(logicalName,"werror") == 0)	||
		(qstrcmp(logicalName,"wwarning") == 0)	||
		(qstrcmp(logicalName,"wtrace") == 0))
		return true;
	return false;
}

int CLIPSClass::printFunction(void* Environment, char* name, char* str)
{
	Q_UNUSED(Environment);
	if (qstrcmp(name, "stdin"))
	{
		CLIPS->answer.append(str);
		return true;
	}
	return false;

}

void CLIPSClass::saveSlot(QString path)
{
	QString factsPath = path+QString("/data.fct");
	QString dataPath = path+QString("/data.clp");
	QString binaryPath = path+QString("/data.bin");
	SaveFacts(factsPath.toUtf8().data(),LOCAL_SAVE,NULL);
	Save(dataPath.toUtf8().data());
	Bsave(binaryPath.toUtf8().data());
}

void CLIPSClass::loadSlot(QString path)
{
	QString factsPath = path+QString("/data.fct");
	QString dataPath = path+QString("/data.clp");
	QString binaryPath = path+QString("/data.bin");
	LoadFacts(factsPath.toUtf8().data());
	Load(dataPath.toUtf8().data());
	BloadData(binaryPath.toUtf8().data());
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
	executeCommand(command);
	QStringList templates = templatesSlot();
	emit templatesChangedSignal(templates);
	emit dataChanged();
}

void CLIPSClass::unDeftemplateSlot(QString name)
{
	void* tmplPtr = FindDeftemplate(name.simplified().toUtf8().data());
	if(!IsDeftemplateDeletable(tmplPtr))
		return;
	Undeftemplate(tmplPtr);
	QStringList templates = templatesSlot();
	emit templatesChangedSignal(templates);
	emit dataChanged();
}

QList<slotsPair> CLIPSClass::getTemplateInformation(QString name)
{
	QList<slotsPair> info;
	DATA_OBJECT sltVal;
	void* tmplPtr = FindDeftemplate(name.toUtf8().data());
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
	void* deftemplatePtr = FindDeftemplate(name.simplified().toUtf8().data());
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
	AssertString(fact.toUtf8().data());
	QStringList facts = factsSlot();
	emit factsChangedSignal(facts);
	QStringList templates = templatesSlot();
	emit templatesChangedSignal(templates);
	QStringList activations = agendaSlot();
	emit activationsChangedSignal(activations);
	emit dataChanged();
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
	templatePtr = FindDeftemplate(templateName.toUtf8().data());
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
					theValue.value = AddSymbol(slotVal.toUtf8().data());
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
			PutFactSlot(newFact, sltNames.at(i).toUtf8().data(), &theValue);
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
						SetMFValue(theMultifield,t+1,AddSymbol(mltSltVal.at(t).toUtf8().data()));
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
			PutFactSlot(newFact, sltNames.at(i).toUtf8().data(), &theValue);
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
	emit dataChanged();
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
				emit dataChanged();
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
	executeCommand(command);
	QStringList deffacts = factsListSlot();
	emit deffactsChangedSignal(deffacts);
	QStringList templates = templatesSlot();
	emit templatesChangedSignal(templates);
	QStringList activations = agendaSlot();
	emit activationsChangedSignal(activations);
	emit dataChanged();
}

void CLIPSClass::unDeffactsSlot(QString name)
{
	void* tmplPtr = FindDeffacts(name.simplified().toUtf8().data());
	if(!IsDeffactsDeletable(tmplPtr))
		return;
	Undeffacts(tmplPtr);
	QStringList deffacts = factsListSlot();
	emit deffactsChangedSignal(deffacts);
	QStringList templates = templatesSlot();
	emit templatesChangedSignal(templates);
	QStringList activations = agendaSlot();
	emit activationsChangedSignal(activations);
	emit dataChanged();
}

QString CLIPSClass::getDeffactsPPF(QString name)
{
	void* deffactsPtr = FindDeffacts(name.simplified().toUtf8().data());
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
	executeCommand(command);
	QStringList rules = rulesSlot();
	emit rulesChangedSignal(rules);
	QStringList templates = templatesSlot();
	emit templatesChangedSignal(templates);
	QStringList activations = agendaSlot();
	emit activationsChangedSignal(activations);
	emit dataChanged();
}

void CLIPSClass::unDefruleSlot(QString name)
{
	void* tmplPtr = FindDefrule(name.simplified().toUtf8().data());
	if(!IsDefruleDeletable(tmplPtr))
		return;
	Undefrule(tmplPtr);
	QStringList rules = rulesSlot();
	emit rulesChangedSignal(rules);
	QStringList activations = agendaSlot();
	emit activationsChangedSignal(activations);
	emit dataChanged();
}

void CLIPSClass::SetBreakSlot(QString name)
{
	SetBreak(FindDefrule(name.toUtf8().data()));
	QStringList rules = rulesSlot();
	emit rulesChangedSignal(rules);
	emit dataChanged();
}

void CLIPSClass::RemoveBreakSlot(QString name)
{
	RemoveBreak(FindDefrule(name.toUtf8().data()));
	QStringList rules = rulesSlot();
	emit rulesChangedSignal(rules);
	emit dataChanged();
}

QString CLIPSClass::getRulePPF(QString name)
{
	void* rulePtr = FindDefrule(name.simplified().toUtf8().data());
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
	emit dataChanged();
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
	emit dataChanged();
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
				emit dataChanged();
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
	executeCommand(command);
	QStringList globals = globalsSlot();
	emit globalsChangedSignal(globals);
	emit dataChanged();
}

void CLIPSClass::unDefglobalSlot(QString name)
{
	void* globalPtr = FindDefglobal(name.simplified().toUtf8().data());
	if(!IsDefglobalDeletable(globalPtr))
		return;
	Undefglobal(globalPtr);
	QStringList globals = globalsSlot();
	emit globalsChangedSignal(globals);
	emit dataChanged();
}

QString CLIPSClass::getGlobalPPF(QString name)
{
	void* globalPtr = FindDefglobal(name.simplified().toUtf8().data());
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
	executeCommand(command);
	QStringList functions = functionsSlot();
	emit functionsChangedSignal(functions);
	emit dataChanged();
}

void CLIPSClass::unDeffunctionSlot(QString name)
{
	void* functionPtr = FindDeffunction(name.simplified().toUtf8().data());
	if(!IsDeffunctionDeletable(functionPtr))
		return;
	Undeffunction(functionPtr);
	QStringList functions = functionsSlot();
	emit functionsChangedSignal(functions);
	emit dataChanged();
}

QString CLIPSClass::getFunctionPPF(QString name)
{
	void* functionPtr = FindDeffunction(name.simplified().toUtf8().data());
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
	executeCommand(command);
	QStringList generic = genericSlot();
	emit genericChangedSignal(generic);
	QHash<QString, int> methods = methodsSlot();
	emit methodsChangedSignal(methods);
	emit dataChanged();
}

void CLIPSClass::unDefgenericSlot(QString name)
{
	void* genericPtr = FindDefgeneric(name.simplified().toUtf8().data());
	if(!IsDefgenericDeletable(genericPtr))
		return;
	Undefgeneric(genericPtr);
	QStringList generic = genericSlot();
	emit genericChangedSignal(generic);
	QHash<QString, int> methods = methodsSlot();
	emit methodsChangedSignal(methods);
	emit dataChanged();
}

QString CLIPSClass::getGenericPPF(QString name)
{
	void* genericPtr = FindDefgeneric(name.simplified().toUtf8().data());
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
	executeCommand(command);
	QStringList generic = genericSlot();
	emit genericChangedSignal(generic);
	QHash<QString, int> methods = methodsSlot();
	emit methodsChangedSignal(methods);
	emit dataChanged();
}

void CLIPSClass::unDefmethodSlot(QString name, int index)
{

	void* genericPtr = FindDefgeneric(name.simplified().toUtf8().data());
	if(IsDefmethodDeletable(genericPtr,index))
		return;
	Undefmethod(genericPtr, index);
	QHash<QString, int> methods = methodsSlot();
	emit methodsChangedSignal(methods);
	emit dataChanged();
}

QString CLIPSClass::getMethodPPF(QString name, int index)
{
	void* genericPtr = FindDefgeneric(name.simplified().toUtf8().data());
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
		void* genericPtr = FindDefgeneric(str.simplified().toUtf8().data());
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

QStringList CLIPSClass::classesSlot()
{
	QStringList classesList;
	void* ptr=NULL;
	do
	{
		ptr = GetNextDefclass(ptr);
		if(ptr!=NULL)
		{
			char *classStr = GetDefclassName(ptr);
			classesList<<QString(classStr).simplified();
		}
	}
	while(ptr!=NULL);
	return classesList;
}

void CLIPSClass::unDefclassSlot(QString name)
{
	void* classPtr = FindDefclass(name.simplified().toUtf8().data());
	if(!IsDefclassDeletable(classPtr))
		return;
	Undefclass(classPtr);
	QStringList classes = classesSlot();
	emit classesChangedSignal(classes);
	QStringList templates = templatesSlot();
	emit templatesChangedSignal(templates);
	QStringList activations = agendaSlot();
	emit activationsChangedSignal(activations);
	QHash<QString, uint> messageHandlers = messageHandlersSlot();
	emit messageHandlersChangedSignal(messageHandlers);
	emit dataChanged();
}

QString CLIPSClass::getClassPPF(QString name)
{
	void* classPtr = FindDefclass(name.simplified().toUtf8().data());
	char *className = GetDefclassPPForm(classPtr);
	return QString(className).simplified();
}

QString CLIPSClass::getMetaInformation(QString name)
{
	QString ret = "";
	QString val = "";
	answer.clear();
	if(name.isEmpty())
		name = "OBJECT";
	void* classPtr = FindDefclass(name.simplified().toUtf8().data());
	if(ClassAbstractP(classPtr))
		val = tr("yes");
	else
		val = tr("no");
	ret += tr("Abstract: ")+val+tr("\n");
	if(ClassReactiveP(classPtr))
		val = tr("yes");
	else
		val = tr("no");
	ret += tr("Reactive: ")+val+tr("\n");

	if(IsDefclassDeletable(classPtr))
		val = tr("yes");
	else
		val = tr("no");
	ret += tr("Deletable: ")+val+tr("\n");
	char* moduleName = DefclassModule(classPtr);
	ret += tr("Module: ")+QString(moduleName)+tr("\n");
	DescribeClass("stdout", classPtr);
	ret += answer;
	return ret;
}

QString CLIPSClass::getSubclasses(QString name)
{
	if(name.isEmpty())
		name = "OBJECT";
	void* classPtr = FindDefclass(name.simplified().toUtf8().data());
	BrowseClasses("stdout", classPtr);
	return answer;
}

QString CLIPSClass::getSuperclasses(QString name)
{
	QString ret = "";
	if(name.isEmpty())
		name = "OBJECT";
	void* classPtr = FindDefclass(name.simplified().toUtf8().data());
	DATA_OBJECT result;
	ClassSuperclasses(classPtr,&result,1);
	void *multifieldPtr;
	char *sltName;
	multifieldPtr = GetValue(result);
	for (int i = GetDOBegin(result); i <= GetDOEnd(result); i++)
	{
		if ((GetMFType(multifieldPtr,i) == STRING) ||(GetMFType(multifieldPtr,i) == SYMBOL))
		{
			sltName = ValueToString(GetMFValue(multifieldPtr,i));
			ret += QString(sltName)+tr("\n");
		}
	}
	ret = ret.trimmed();
	return ret;
}

unsigned short CLIPSClass::getCurrentDefaultsMode()
{
	return GetClassDefaultsMode();
}

QHash<QString, unsigned short> CLIPSClass::getDefaultsModes()
{
	QHash<QString, unsigned short> modes;
	modes.insert(tr("CONVENIENCE_MODE"), CONVENIENCE_MODE);
	modes.insert(tr("CONSERVATION_MODE"), CONSERVATION_MODE);
	return modes;
}

unsigned short CLIPSClass::setDefaultsMode(unsigned short mode)
{
	return SetClassDefaultsMode(mode);
}

//Message Handlers

void CLIPSClass::defmessageHandlerSlot(QString className, QString messageName, QString handlerType, QString comment, QString parameter, QString wildcardParameter, QString action)
{
	QString command = "";
	command += "(defmessage-handler "+className+" "+messageName+" "+handlerType+" ";
	if(!comment.isEmpty())
		command += comment+" ";
	if(!parameter.isEmpty())
	{
		command += "("+parameter;
		if(!wildcardParameter.isEmpty())
			command += " "+wildcardParameter;
		command += ") ";
	}
	command += "("+action+"))";
	executeCommand(command);
	QHash<QString, uint> messageHandlers = messageHandlersSlot();
	emit messageHandlersChangedSignal(messageHandlers);
	emit dataChanged();

}

QHash<QString, unsigned int> CLIPSClass::messageHandlersSlot()
{
	QHash<QString, unsigned int> messageHandlersHash;
	QStringList classes = classesSlot();
	QString str;
	foreach(str, classes)
	{
		void* classPtr = FindDefclass(str.simplified().toUtf8().data());
		unsigned int index=0;
		do
		{
			index = GetNextDefmessageHandler(classPtr, index);
			if(index!=0)
			{
				char* messageHandlerName = GetDefmessageHandlerName(classPtr, index);
				char* messageHandlerType = GetDefmessageHandlerType(classPtr, index);
				messageHandlersHash.insertMulti(str+QString("  ")+QString(messageHandlerName)+QString(" ")+QString(messageHandlerType), index);
			}
		}
		while(index!=0);
	}
	return messageHandlersHash;
}

void CLIPSClass::unDefmessageHandlerSlot(QString name, unsigned int index)
{
	name = name.remove(name.lastIndexOf("  "), name.length());
	void* classPtr = FindDefclass(name.simplified().toUtf8().data());
	if(IsDefmessageHandlerDeletable(classPtr, index))
		UndefmessageHandler(classPtr, index);
	QHash<QString, uint> messageHandlers = messageHandlersSlot();
	emit messageHandlersChangedSignal(messageHandlers);
	emit dataChanged();
}

QString CLIPSClass::getMessageHandlerPPF(QString name, unsigned int index)
{
	name = name.remove(name.lastIndexOf("  "), name.length());
	void* classPtr = FindDefclass(name.simplified().toUtf8().data());
	char *messageHandlerPPForm = GetDefmessageHandlerPPForm(classPtr, index);
	return QString(messageHandlerPPForm).simplified();
}

QStringList CLIPSClass::getHandlerTypesSlot()
{
	QStringList list;
	list<<"around"<<"before"<<"primary"<<"after";
	return list;
}

//Modules

QStringList CLIPSClass::getModules()//Временная заглушка
{
	QStringList modulesList;
	modulesList<<"MAIN";
	return modulesList;
}

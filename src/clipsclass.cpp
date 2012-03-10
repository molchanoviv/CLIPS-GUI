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
	fillHashes();
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
	QString configPath = path+QString("/data.cnf");
	EnvSaveFacts(Environment, factsPath.toUtf8().data(),LOCAL_SAVE,NULL);
	EnvSave(Environment, dataPath.toUtf8().data());
	EnvBsave(Environment, binaryPath.toUtf8().data());
	QFile file(configPath);
	file.remove();
	QSettings settings(configPath, QSettings::IniFormat);
	settings.beginGroup("Breakpoints");
	int i=0;
	void* ptr=NULL;
	do
	{
		ptr = EnvGetNextDefrule(Environment, ptr);
		if(ptr!=NULL)
		{
			char* buf = EnvGetDefruleName(Environment, ptr);
			QString name = QString(buf);
			if(EnvDefruleHasBreakpoint(Environment, ptr))
			{
				settings.setValue("bp_"+QString::number(i), name);
				i++;
			}
		}
	}
	while(ptr!=NULL);
	settings.setValue("bp_count", i);
	settings.endGroup();
	settings.beginGroup("Rules");
	settings.setValue("strategy", getStrategy());
	settings.endGroup();
	settings.beginGroup("Facts");
	settings.setValue("duplication", EnvGetFactDuplication(Environment));
	settings.endGroup();
	settings.beginGroup("Classes");
	settings.setValue("defaultMode", getCurrentDefaultsMode());
	settings.endGroup();
	settings.beginGroup("Modules");
	settings.setValue("module", getCurrentModule());
	settings.endGroup();
}

void CLIPSClass::loadSlot(QString path)
{
	QString factsPath = path+QString("/data.fct");
	QString dataPath = path+QString("/data.clp");
	QString binaryPath = path+QString("/data.bin");
	QString configPath = path+QString("/data.cnf");
	EnvLoadFacts(Environment, factsPath.toUtf8().data());
	EnvLoad(Environment, dataPath.toUtf8().data());
	EnvBload(Environment,binaryPath.toUtf8().data());
	QSettings settings(configPath, QSettings::IniFormat);
	settings.beginGroup("Breakpoints");
	int bp_count = settings.value("bp_count").toInt();
	for(int i=0; i<bp_count; i++)
	{
		QString name = settings.value("bp_"+QString::number(i)).toString();
		EnvSetBreak(Environment, findFunctionsHash["rule"](Environment, name.simplified().toUtf8().data()));
	}
	settings.endGroup();
	settings.beginGroup("Rules");
	if(!settings.value("strategy").isNull())
		setStrategySlot(settings.value("strategy").toInt());
	settings.endGroup();
	settings.beginGroup("Facts");
	if(!settings.value("duplication").isNull())
		emit restoreFactDuplicationSignal(settings.value("duplication").toBool());
	settings.endGroup();
	settings.beginGroup("Classes");
	if(!settings.value("defaultMode").isNull())
		setDefaultsMode(settings.value("defaultMode").toUInt());
	settings.endGroup();
	settings.beginGroup("Modules");
	if(!settings.value("module").isNull())
		setCurrentModule(settings.value("module").toString());
	settings.endGroup();
}

void CLIPSClass::clearSlot()
{
	EnvClear(Environment);
	emit clearSignal();
}

void CLIPSClass::fillHashes()
{
	removeFunctionsHash.insert("template", EnvUndeftemplate);
	removeFunctionsHash.insert("factsList", EnvUndeffacts);
	removeFunctionsHash.insert("rule", EnvUndefrule);
	removeFunctionsHash.insert("global", EnvUndefglobal);
	removeFunctionsHash.insert("function", EnvUndeffunction);
	removeFunctionsHash.insert("generic", EnvUndefgeneric);
	removeFunctionsHash.insert("class", EnvUndefclass);
	removeFunctionsHash.insert("instance", EnvUndefinstances);

	findFunctionsHash.insert("template", EnvFindDeftemplate);
	findFunctionsHash.insert("factsList", EnvFindDeffacts);
	findFunctionsHash.insert("rule", EnvFindDefrule);
	findFunctionsHash.insert("global", EnvFindDefglobal);
	findFunctionsHash.insert("function", EnvFindDeffunction);
	findFunctionsHash.insert("generic", EnvFindDefgeneric);
	findFunctionsHash.insert("class", EnvFindDefclass);
	findFunctionsHash.insert("instance", EnvFindDefinstances);
	findFunctionsHash.insert("module", EnvFindDefmodule);

	isDeletableFunctionsHash.insert("template", EnvIsDeftemplateDeletable);
	isDeletableFunctionsHash.insert("factsList", EnvIsDeffactsDeletable);
	isDeletableFunctionsHash.insert("rule", EnvIsDefruleDeletable);
	isDeletableFunctionsHash.insert("global", EnvIsDefglobalDeletable);
	isDeletableFunctionsHash.insert("function", EnvIsDeffunctionDeletable);
	isDeletableFunctionsHash.insert("generic", EnvIsDefgenericDeletable);
	isDeletableFunctionsHash.insert("class", EnvIsDefclassDeletable);
	isDeletableFunctionsHash.insert("instance", EnvIsDefinstancesDeletable);

	getNextFunctionsHash.insert("template", EnvGetNextDeftemplate);
	getNextFunctionsHash.insert("fact", EnvGetNextFact);
	getNextFunctionsHash.insert("factsList", EnvGetNextDeffacts);
	getNextFunctionsHash.insert("rule", EnvGetNextDefrule);
	getNextFunctionsHash.insert("agenda", EnvGetNextActivation);
	getNextFunctionsHash.insert("global", EnvGetNextDefglobal);
	getNextFunctionsHash.insert("function", EnvGetNextDeffunction);
	getNextFunctionsHash.insert("generic", EnvGetNextDefgeneric);
	getNextFunctionsHash.insert("class", EnvGetNextDefclass);
	getNextFunctionsHash.insert("instance", EnvGetNextDefinstances);
	getNextFunctionsHash.insert("module", EnvGetNextDefmodule);
}

void CLIPSClass::removeSlot(QString name, QString function, int index)
{
	if(function == "method")
	{
		void* ptr = findFunctionsHash["generic"](Environment, name.simplified().toUtf8().data());
		if(!EnvIsDefmethodDeletable(Environment, ptr,index))
			return;
		EnvUndefmethod(Environment, ptr, index);
	}
	else if(function == "messageHandler")
	{
		name = name.remove(name.lastIndexOf("  "), name.length());
		void* ptr = findFunctionsHash["class"](Environment, name.simplified().toUtf8().data());
		if(!EnvIsDefmessageHandlerDeletable(Environment, ptr, index))
			return;
		EnvUndefmessageHandler(Environment, ptr, (unsigned int)index);
	}
	else
	{
		void* ptr = findFunctionsHash[function](Environment, name.simplified().toUtf8().data());
		if(!isDeletableFunctionsHash[function](Environment, ptr))
			return;
		removeFunctionsHash[function](Environment, ptr);
	}
	emit refreshAll();
	emit dataChanged();
}

QString CLIPSClass::getPPF(QString name, QString function, int index)
{
	char *ppf;
	if(function=="method")
	{
		void* ptr = findFunctionsHash["generic"](Environment, name.simplified().toUtf8().data());
		ppf = EnvGetDefmethodPPForm(Environment, ptr, index);
	}
	else if(function == "messageHandler")
	{
		name = name.remove(name.lastIndexOf("  "), name.length());
		void* ptr = findFunctionsHash["class"](Environment, name.simplified().toUtf8().data());
		ppf = EnvGetDefmessageHandlerPPForm(Environment, ptr, (unsigned int)index);
	}
	else
	{
		void* ptr = findFunctionsHash[function](Environment, name.simplified().toUtf8().data());
		ppf = GetConstructPPForm(Environment, (struct constructHeader *) ptr);
	}
	return QString(ppf).simplified();
}

QStringList CLIPSClass::itemsSlot(QString function)
{
	EnvRefreshAgenda(Environment, NULL);
	QStringList list;
	void* ptr=NULL;
	do
	{
		ptr = getNextFunctionsHash[function](Environment, ptr);
		if(ptr!=NULL)
		{
			QString name;
			if(function == "fact")
			{
				char buf[16384]={0};
				EnvGetFactPPForm(Environment, buf,sizeof(buf), ptr);
				name = QString(buf);
			}
			else if(function == "agenda")
			{
				char buf[16384]={0};
				EnvGetActivationPPForm(Environment, buf,sizeof(buf), ptr);
				name = QString(buf);
			}
			else
			{
				char* buf = EnvGetConstructNameString(Environment, (struct constructHeader *) ptr);
				name = QString(buf);
			}
			if(function == "rule")
			{
				if(EnvDefruleHasBreakpoint(Environment, ptr))
					name = "[bp]/"+name;
			}
			list<<name;
		}
	}
	while(ptr!=NULL);
	return list;
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
	emit refreshAll();
	emit dataChanged();
}

QList<slotsPair> CLIPSClass::getTemplateInformation(QString name)
{
	QList<slotsPair> info;
	DATA_OBJECT sltVal;
	void* tmplPtr = findFunctionsHash["template"](Environment, name.simplified().toUtf8().data());
	EnvDeftemplateSlotNames(Environment, tmplPtr, &sltVal);
	void *multifieldPtr;
	char *sltName;
	multifieldPtr = EnvGetValue(Environment, sltVal);
	for (int i = EnvGetDOBegin(Environment, sltVal); i <= EnvGetDOEnd(Environment, sltVal); i++)
	{
		if ((EnvGetMFType(Environment, multifieldPtr,i) == STRING) ||(EnvGetMFType(Environment, multifieldPtr,i) == SYMBOL))
		{
			sltName = EnvValueToString(Environment, EnvGetMFValue(Environment, multifieldPtr,i));
			bool ok = EnvDeftemplateSlotMultiP(Environment, tmplPtr, sltName);
			info.append(slotsPair(ok, QString(sltName)));
		}
	}
	return info;
}

//Facts

void CLIPSClass::assertStringSlot(QString fact)
{
	fact.append(")").prepend("(");
	void* factPtr = EnvAssertString(Environment, fact.toUtf8().data());
	emit refreshAll();
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
	EnvIncrementGCLocks(Environment);
	templatePtr = findFunctionsHash["template"](Environment, templateName.simplified().toUtf8().data());
	newFact = EnvCreateFact(Environment, templatePtr);
	if (newFact == NULL)
		return;
	DATA_OBJECT sltVal;
	QStringList sltNames;
	EnvDeftemplateSlotNames(Environment, templatePtr, &sltVal);
	void *multifieldPtr;
	char *sltName;
	multifieldPtr = EnvGetValue(Environment, sltVal);
	for (int i = EnvGetDOBegin(Environment, sltVal); i <= EnvGetDOEnd(Environment, sltVal); i++)
	{
		if ((EnvGetMFType(Environment, multifieldPtr,i) == STRING) ||(EnvGetMFType(Environment, multifieldPtr,i) == SYMBOL))
		{
			sltName = EnvValueToString(Environment, EnvGetMFValue(Environment, multifieldPtr,i));
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
					theValue.value = EnvAddSymbol(Environment, slotVal.toUtf8().data());
				}
				else
				{
					theValue.type = FLOAT;
					theValue.value = EnvAddDouble(Environment, slotVal.toFloat());
				}
			}
			else
			{
				theValue.type = INTEGER;
				theValue.value = EnvAddLong(Environment, slotVal.toInt());
			}
			EnvPutFactSlot(Environment, newFact, sltNames.at(i).toUtf8().data(), &theValue);
		}
		else
		{
			QRegExp rx("(([\\(][\\w\\s]+[\\)]))+");
			QStringList mltSltVal;
			int pos = 0;
			while ((pos = rx.indexIn(slotsList.at(i).second, pos)) != -1)
			{
				QString fact = rx.cap(1);
				fact.remove(0, 1);
				fact.remove(fact.length()-1, 1);
				mltSltVal << fact;
				pos += rx.matchedLength();
			}
			if(mltSltVal.isEmpty())
				return;
			theMultifield = EnvCreateMultifield(Environment, mltSltVal.count());
			for(int t=0; t<mltSltVal.count(); t++)
			{
				QRegExpValidator validator(floatRx, 0);
				int pos = 0;
				QString slotVal = mltSltVal.at(t);
				if(validator.validate(slotVal, pos) != QValidator::Acceptable)
				{
					QRegExpValidator validator(intRx, 0);
					if(validator.validate(slotVal, pos) != QValidator::Acceptable)
					{
						EnvSetMFType(Environment, theMultifield,t+1,SYMBOL);
						EnvSetMFValue(Environment, theMultifield, t+1, EnvAddSymbol(Environment, mltSltVal.at(t).toUtf8().data()));
					}
					else
					{
						EnvSetMFType(Environment, theMultifield, t+1, FLOAT);
						EnvSetMFValue(Environment, theMultifield, t+1, EnvAddDouble(Environment, mltSltVal.at(t).toFloat()));
					}
				}
				else
				{
					EnvSetMFType(Environment, theMultifield, t+1, INTEGER);
					EnvSetMFValue(Environment, theMultifield, t+1, EnvAddLong(Environment, mltSltVal.at(t).toInt()));
				}
			}
			EnvSetDOBegin(Environment, theValue,1);
			EnvSetDOEnd(Environment, theValue, mltSltVal.count()+1);
			theValue.type = MULTIFIELD;
			theValue.value = theMultifield;
			EnvPutFactSlot(Environment, newFact, sltNames.at(i).toUtf8().data(), &theValue);
		}
	}
	EnvAssignFactSlotDefaults(Environment, newFact);
	EnvDecrementGCLocks(Environment);
	EnvAssert(Environment, newFact);
	emit refreshAll();
	emit dataChanged();
}

void CLIPSClass::retractSlot(int factNumber)
{
	void* ptr=NULL;
	do
	{
		ptr = EnvGetNextFact(Environment, ptr);
		if(ptr!=NULL)
		{
			if(factNumber == EnvFactIndex(Environment, ptr))
			{
				EnvRetract(Environment, ptr);
				emit refreshAll();
				emit dataChanged();
			}
		}
	}
	while(ptr!=NULL);
}

void CLIPSClass::setFactDuplicationSlot(bool state)
{
	EnvSetFactDuplication(Environment, state);
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
	emit refreshAll();
	emit dataChanged();
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
	emit refreshAll();
	emit dataChanged();
}

void CLIPSClass::SetBreakSlot(QString name)
{
	EnvSetBreak(Environment, findFunctionsHash["rule"](Environment, name.simplified().toUtf8().data()));
	emit refreshAll();
	emit dataChanged();
}

void CLIPSClass::RemoveBreakSlot(QString name)
{
	EnvRemoveBreak(Environment, findFunctionsHash["rule"](Environment, name.simplified().toUtf8().data()));
	emit refreshAll();
	emit dataChanged();
}

//Agenda

void CLIPSClass::runSlot()
{
	EnvRun(Environment, -1);
	emit refreshAll();
	emit dataChanged();
}

void CLIPSClass::removeActivationSlot(QString name)
{
	void* ptr=NULL;
	do
	{
		ptr = EnvGetNextActivation(Environment, ptr);
		char buf[16384]={0};
		if(ptr!=NULL)
		{
			EnvGetActivationPPForm(Environment, buf,sizeof(buf), ptr);
			QString bufVal(buf);
			if(bufVal == name)
			{
				EnvDeleteActivation(Environment, ptr);
				emit refreshAll();
				emit dataChanged();
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
		ptr = EnvGetNextActivation(Environment, ptr);
		char buf[16384]={0};
		if(ptr!=NULL)
		{
			EnvGetActivationPPForm(Environment, buf,sizeof(buf), ptr);
			QString bufVal(buf);
			if(bufVal == name)
			{
				int salience = EnvGetActivationSalience(Environment, ptr);
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
		ptr = EnvGetNextActivation(Environment, ptr);
		char buf[16384]={0};
		if(ptr!=NULL)
		{
			EnvGetActivationPPForm(Environment, buf,sizeof(buf), ptr);
			QString bufVal(buf);
			if(bufVal == name)
			{
				EnvSetActivationSalience(Environment, ptr, salience);
				EnvReorderAgenda(Environment, NULL);
				emit refreshAll();
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
	return EnvGetStrategy(Environment);
}

void CLIPSClass::setStrategySlot(int strategy)
{
	EnvSetStrategy(Environment, strategy);
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
	emit refreshAll();
	emit dataChanged();
}

//Functions

void CLIPSClass::deffunctionSlot(QString name, QString comment, QString regular, QString wildcard, QString expression)
{
	if(!comment.isEmpty())
		comment = "\""+comment+"\"";
	QString command = "(deffunction "+name+" "+comment+" ("+regular+" "+wildcard+") "+expression+")";
	executeCommand(command);
	emit refreshAll();
	emit dataChanged();
}

//Generic Functions

void CLIPSClass::defgenericSlot(QString name)
{
	QString command = "(defgeneric "+name+")";
	executeCommand(command);
	emit refreshAll();
	emit dataChanged();
}

//Methods

void CLIPSClass::defmethodSlot(QString name, QString index, QString comment, QString regular, QString wildcard, QString expression)
{
	if(!comment.isEmpty())
		comment = "\""+comment+"\"";
	QString command = "(defmethod "+name+" "+index+" "+comment+" ("+regular+" "+wildcard+") "+expression+")";
	executeCommand(command);
	emit refreshAll();
	emit dataChanged();
}

QHash<QString, int> CLIPSClass::methodsSlot()
{
	QHash<QString, int> methodsHash;
	QStringList generics = itemsSlot("generic");
	QString str;
	foreach(str, generics)
	{
		void* genericPtr = findFunctionsHash["generic"](Environment, str.simplified().toUtf8().data());
		int index=0;
		do
		{
			index = EnvGetNextDefmethod(Environment, genericPtr, index);
			if(index!=0)
				methodsHash.insert(str, index);
		}
		while(index!=0);
	}
	return methodsHash;
}

//Classes

void CLIPSClass::defclassSlot(QString name, QString comment, QString role, QString patternMatchRole, QStringList slotsList, QStringList parentsList, QStringList handlersList)
{
	if(!comment.isEmpty())
		comment = "\""+comment+"\"";
	QString command = "(defclass "+name+" "+comment+"( is-a ";
	for(int i=0; i<parentsList.count(); i++)
	{
		command += parentsList.at(i)+" ";
	}
	command +=") (role "+role+") (pattern-match "+patternMatchRole+") ";
	for(int i=0; i<slotsList.count(); i++)
	{
		command += "("+slotsList.at(i)+")";
	}
	for(int i=0; i<handlersList.count(); i++)
	{
		command += "("+handlersList.at(i)+")";
	}
	command += ")";
	executeCommand(command);
	emit refreshAll();
	emit dataChanged();
}

QString CLIPSClass::getMetaInformation(QString name)
{
	QString ret = "";
	QString val = "";
	answer.clear();
	if(name.isEmpty())
		name = "OBJECT";
	void* classPtr = findFunctionsHash["class"](Environment, name.simplified().toUtf8().data());
	if(EnvClassAbstractP(Environment, classPtr))
		val = tr("yes");
	else
		val = tr("no");
	ret += tr("Abstract: ")+val+tr("\n");
	if(EnvClassReactiveP(Environment, classPtr))
		val = tr("yes");
	else
		val = tr("no");
	ret += tr("Reactive: ")+val+tr("\n");

	if(EnvIsDefclassDeletable(Environment, classPtr))
		val = tr("yes");
	else
		val = tr("no");
	ret += tr("Deletable: ")+val+tr("\n");
	char* moduleName = EnvDefclassModule(Environment, classPtr);
	ret += tr("Module: ")+QString(moduleName)+tr("\n");
	EnvDescribeClass(Environment, "stdout", classPtr);
	ret += answer;
	return ret;
}

QString CLIPSClass::getSubclasses(QString name)
{
	answer.clear();
	if(name.isEmpty())
		name = "OBJECT";
	void* classPtr = findFunctionsHash["class"](Environment, name.simplified().toUtf8().data());
	EnvBrowseClasses(Environment, "stdout", classPtr);
	return answer;
}

QString CLIPSClass::getSuperclasses(QString name)
{
	QString ret = "";
	if(name.isEmpty())
		name = "OBJECT";
	void* classPtr = findFunctionsHash["class"](Environment, name.simplified().toUtf8().data());
	DATA_OBJECT result;
	EnvClassSuperclasses(Environment, classPtr,&result,1);
	void *multifieldPtr;
	char *sltName;
	multifieldPtr = EnvGetValue(Environment, result);
	for (int i = EnvGetDOBegin(Environment, result); i <= EnvGetDOEnd(Environment, result); i++)
	{
		if ((EnvGetMFType(Environment, multifieldPtr,i) == STRING) ||(EnvGetMFType(Environment, multifieldPtr,i) == SYMBOL))
		{
			sltName = EnvValueToString(Environment, GetMFValue(multifieldPtr,i));
			ret += QString(sltName)+tr("\n");
		}
	}
	ret = ret.trimmed();
	return ret;
}

unsigned short CLIPSClass::getCurrentDefaultsMode()
{
	return EnvGetClassDefaultsMode(Environment);
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
	return EnvSetClassDefaultsMode(Environment, mode);
}

//Message Handlers

void CLIPSClass::defmessageHandlerSlot(QString className, QString messageName, QString handlerType, QString comment, QString parameter, QString wildcardParameter, QString action)
{
	QString command = "";
	command += "(defmessage-handler "+className+" "+messageName+" "+handlerType+" ";
	if(!comment.isEmpty())
		command += "\""+comment+"\" ";
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
}

QStringList CLIPSClass::getHandlerTypesSlot()
{
	QStringList list;
	list<<"around"<<"before"<<"primary"<<"after";
	return list;
}

QHash<QString, unsigned int> CLIPSClass::messageHandlersSlot()
{
	QHash<QString, unsigned int> messageHandlersHash;
	QStringList classes = itemsSlot("class");
	QString str;
	foreach(str, classes)
	{
		void* classPtr = findFunctionsHash["class"](Environment, str.simplified().toUtf8().data());
		unsigned int index=0;
		do
		{
			index = EnvGetNextDefmessageHandler(Environment, classPtr, index);
			if(index!=0)
			{
				char* messageHandlerName = EnvGetDefmessageHandlerName(Environment, classPtr, index);
				char* messageHandlerType = EnvGetDefmessageHandlerType(Environment, classPtr, index);
				messageHandlersHash.insertMulti(str+QString("  ")+QString(messageHandlerName)+QString(" ")+QString(messageHandlerType), index);
			}
		}
		while(index!=0);
	}
	return messageHandlersHash;
}

//Instances

void CLIPSClass::definstanceSlot(QString name, QString active, QString comment, QString instanceTemplate)
{
	if(!comment.isEmpty())
		comment = "\""+comment+"\"";
	QString command = "(definstances "+name+" "+active+" "+comment+" "+instanceTemplate+")";
	executeCommand(command);
	emit refreshAll();
	emit dataChanged();
}

//Modules

void CLIPSClass::defmoduleSlot(QString name, QString comment, QString specification)
{
	if(!comment.isEmpty())
		comment = "\""+comment+"\"";
	QString command = "(defmodule "+name+" "+comment+" "+specification+")";
	executeCommand(command);
	emit refreshAll();
	emit dataChanged();
}

QString CLIPSClass::getCurrentModule()
{
	void* modulePtr = EnvGetCurrentModule(Environment);
	char* moduleName = EnvGetDefmoduleName(Environment, modulePtr);
	return QString(moduleName).simplified();
}

void CLIPSClass::setCurrentModule(QString name)
{
	void* modulePtr = findFunctionsHash["module"](Environment, name.simplified().toUtf8().data());
	EnvSetCurrentModule(Environment, modulePtr);
	emit refreshAll();
	emit dataChanged();
}

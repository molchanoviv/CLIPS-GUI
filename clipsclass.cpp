#include <iostream>
#include "clipsclass.h"
#include <QRegExpValidator>

CLIPSClass::CLIPSClass(QObject *parent) :
	QObject(parent)
{
	InitializeEnvironment();
}

void CLIPSClass::assertStringSlot(QString fact, bool ret)
{
	fact.append(")").prepend("(");
	AssertString(fact.toLocal8Bit().data());
	if(ret)
		emit outputSignal("");
	QStringList facts = factsSlot(false);
	emit factsChangedSignal(facts);
	QStringList templates = templatesSlot(false);
	emit templatesChangedSignal(templates);

}

void CLIPSClass::assertSlot(QString templateName, QList<slotsPair> slotsList, bool ret)
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
	if(ret)
		emit outputSignal("");
	QStringList facts = factsSlot(false);
	emit factsChangedSignal(facts);
	QStringList templates = templatesSlot(false);
	emit templatesChangedSignal(templates);
	QStringList activations = agendaSlot(false);
	emit activationsChangedSignal(activations);
}

void CLIPSClass::retractSlot(int factNumber, bool ret)
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
				if(ret)
					emit outputSignal("");
				QStringList facts = factsSlot(false);
				emit factsChangedSignal(facts);
				QStringList activations = agendaSlot(false);
				emit activationsChangedSignal(activations);
			}
		}
	}
	while(ptr!=NULL);
}

void CLIPSClass::deffactsSlot(QString name, QStringList factsList)
{
	QString factsstr;

	for(int i=0; i<factsList.count(); i++)
	{
		factsstr += "( "+factsList.at(i)+" ) ";
	}
	QString command = "(deffacts "+name+" "+factsstr+")";
	QFile file(QDir::tempPath()+"/tmpfile");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;
	QTextStream out(&file);
	out<<command;
	QString path = file.fileName();
	file.close();
	Load(path.toLocal8Bit().data());
	file.remove();
	QStringList deffacts = factsListSlot(false);
	emit deffactsChangedSignal(deffacts);
	QStringList templates = templatesSlot(false);
	emit templatesChangedSignal(templates);
	QStringList activations = agendaSlot(false);
	emit activationsChangedSignal(activations);
}

void CLIPSClass::unDeffactsSlot(QString name, bool ret)
{
	void* tmplPtr = FindDeffacts(name.simplified().toLocal8Bit().data());
	if(!IsDeffactsDeletable(tmplPtr))
		return;
	Undeffacts(tmplPtr);
	if(ret)
		emit outputSignal("");
	QStringList deffacts = factsListSlot(false);
	emit deffactsChangedSignal(deffacts);
	QStringList templates = templatesSlot(false);
	emit templatesChangedSignal(templates);
	QStringList activations = agendaSlot(false);
	emit activationsChangedSignal(activations);
}

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
	QFile file(QDir::tempPath()+"/tmpfile");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;
	QTextStream out(&file);
	out<<command;
	QString path = file.fileName();
	file.close();
	Load(path.toLocal8Bit().data());
	file.remove();
	QStringList templates = templatesSlot(false);
	emit templatesChangedSignal(templates);
}

void CLIPSClass::unDeftemplateSlot(QString name, bool ret)
{
	void* tmplPtr = FindDeftemplate(name.simplified().toLocal8Bit().data());
	if(!IsDeftemplateDeletable(tmplPtr))
		return;
	Undeftemplate(tmplPtr);
	if(ret)
		emit outputSignal("");
	QStringList templates = templatesSlot(false);
	emit templatesChangedSignal(templates);
}

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
	QFile file(QDir::tempPath()+"/tmpfile");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;
	QTextStream out(&file);
	out<<command;
	QString path = file.fileName();
	file.close();
	Load(path.toLocal8Bit().data());
	file.remove();
	QStringList rules = rulesSlot(false);
	emit rulesChangedSignal(rules);
	QStringList templates = templatesSlot(false);
	emit templatesChangedSignal(templates);
	QStringList activations = agendaSlot(false);
	emit activationsChangedSignal(activations);
}

void CLIPSClass::unDefruleSlot(QString name, bool ret)
{
	void* tmplPtr = FindDefrule(name.simplified().toLocal8Bit().data());
	if(!IsDefruleDeletable(tmplPtr))
		return;
	Undefrule(tmplPtr);
	if(ret)
		emit outputSignal("");
	QStringList rules = rulesSlot(false);
	emit rulesChangedSignal(rules);
	QStringList activations = agendaSlot(false);
	emit activationsChangedSignal(activations);
}

void CLIPSClass::SetBreakSlot(QString name, bool ret)
{
	SetBreak(FindDefrule(name.toLocal8Bit().data()));
	if(ret)
		emit outputSignal("");
	QStringList rules = rulesSlot(false);
	emit rulesChangedSignal(rules);
}

void CLIPSClass::RemoveBreakSlot(QString name, bool ret)
{
	RemoveBreak(FindDefrule(name.toLocal8Bit().data()));
	if(ret)
		emit outputSignal("");
	QStringList rules = rulesSlot(false);
	emit rulesChangedSignal(rules);
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

void CLIPSClass::runSlot()
{
	Run(-1);
	QStringList templates = templatesSlot(false);
	emit templatesChangedSignal(templates);
	QStringList facts = factsSlot(false);
	emit factsChangedSignal(facts);
	QStringList deffacts = factsListSlot(false);
	emit deffactsChangedSignal(deffacts);
	QStringList rules = rulesSlot(false);
	emit rulesChangedSignal(rules);
	QStringList activations = agendaSlot(false);
	emit activationsChangedSignal(activations);
}

void CLIPSClass::removeActivationSlot(QString name, bool ret)
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
				QStringList activations = agendaSlot(false);
				emit activationsChangedSignal(activations);
			}
		}
	}
	while(ptr!=NULL);
	if(ret)
		emit outputSignal("");
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

void CLIPSClass::setActivationSalienceSlot(QString name, int salience, bool ret)
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
				QStringList activations = agendaSlot(false);
				emit activationsChangedSignal(activations);
			}
		}
	}
	while(ptr!=NULL);
	if(ret)
		emit outputSignal("");
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

void CLIPSClass::setStrategySlot(int strategy, bool ret)
{
	SetStrategy(strategy);
	if(ret)
		emit outputSignal("");
}

void CLIPSClass::saveFactsSlot(QString path)
{
	SaveFacts(path.toLocal8Bit().data(),LOCAL_SAVE,NULL);
}

void CLIPSClass::loadFactsSlot(QString path)
{
	LoadFacts(path.toLocal8Bit().data());
	QStringList facts = factsSlot(false);
	emit factsChangedSignal(facts);
}

void CLIPSClass::saveSlot(QString path)
{
	Save(path.toLocal8Bit().data());
}

void CLIPSClass::loadSlot(QString path)
{
	Load(path.toLocal8Bit().data());
	QStringList facts = factsSlot(false);
	emit factsChangedSignal(facts);
	QStringList templates = templatesSlot(false);
	emit templatesChangedSignal(templates);
}

void CLIPSClass::clearSlot()
{
	Clear();
	emit clearSignal();
}

void CLIPSClass::setFactDuplicationSlot(bool state, bool ret)
{
	SetFactDuplication(state);
	if(ret)
		emit outputSignal("");
}

QStringList CLIPSClass::templatesSlot(bool ret)
{
	DATA_OBJECT retVal;
	char *templateStr;
	void *multifieldPtr;
	QStringList templatesList;
	GetDeftemplateList(&retVal, NULL);
	multifieldPtr = GetValue(retVal);
	for (int i = GetDOBegin(retVal); i <= GetDOEnd(retVal); i++)
	{
		if ((GetMFType(multifieldPtr,i) == STRING) ||(GetMFType(multifieldPtr,i) == SYMBOL))
		{
			templateStr = ValueToString(GetMFValue(multifieldPtr,i));
			templatesList<<QString(templateStr);
		}
	}
	if(ret)
	{
		QString string, str;
		foreach(str, templatesList)
			string += " "+str;
		emit outputSignal(string);
	}
	return templatesList;
}

QStringList CLIPSClass::factsSlot(bool ret)
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
	if(ret)
	{
		QString string, str;
		foreach(str, factsList)
			string += " "+str;
		emit outputSignal(string);
	}
	return factsList;
}

QStringList CLIPSClass::factsListSlot(bool ret)
{
	QStringList deffactsList;
	DATA_OBJECT retVal;
	char *deffactsStr;
	void *multifieldPtr;
	GetDeffactsList(&retVal, NULL);
	multifieldPtr = GetValue(retVal);
	for (int i = GetDOBegin(retVal); i <= GetDOEnd(retVal); i++)
	{
		if ((GetMFType(multifieldPtr,i) == STRING) ||(GetMFType(multifieldPtr,i) == SYMBOL))
		{
			deffactsStr = ValueToString(GetMFValue(multifieldPtr,i));
			deffactsList<<QString(deffactsStr);
		}
	}
	if(ret)
	{
		QString string, str;
		foreach(str, deffactsList)
			string += " "+str;
		emit outputSignal(string);
	}
	return deffactsList;
}

QStringList CLIPSClass::rulesSlot(bool ret)
{
	QStringList rulesList;
	DATA_OBJECT retVal;
	char *ruleStr;
	void *multifieldPtr;
	GetDefruleList(&retVal, NULL);
	multifieldPtr = GetValue(retVal);
	for (int i = GetDOBegin(retVal); i <= GetDOEnd(retVal); i++)
	{
		if ((GetMFType(multifieldPtr,i) == STRING) ||(GetMFType(multifieldPtr,i) == SYMBOL))
		{
			ruleStr = ValueToString(GetMFValue(multifieldPtr,i));
			void* rulePtr = FindDefrule(ruleStr);
			Refresh(rulePtr);
			QString name=QString(ruleStr);
			if(DefruleHasBreakpoint(rulePtr))
				name = "[bp]/"+name;
			rulesList<<name;
		}
	}
	if(ret)
	{
		QString string, str;
		foreach(str, rulesList)
			string += " "+str;
		emit outputSignal(string);
	}
	return rulesList;
}

QStringList CLIPSClass::agendaSlot(bool ret)
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
	if(ret)
	{
		QString string, str;
		foreach(str, activationsList)
			string += " "+str;
		emit outputSignal(string);
	}
	return activationsList;
}

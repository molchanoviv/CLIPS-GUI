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
			}
		}
	}
	while(ptr!=NULL);
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

void CLIPSClass::saveFactsSlot(QString path)
{
	SaveFacts(path.toLocal8Bit().data(),LOCAL_SAVE,NULL);
//	emit outputSignal("");
}

void CLIPSClass::loadFactsSlot(QString path)
{
	LoadFacts(path.toLocal8Bit().data());
//	emit outputSignal("");
	QStringList facts = factsSlot(false);
	emit factsChangedSignal(facts);
}

void CLIPSClass::saveSlot(QString path)
{
	Save(path.toLocal8Bit().data());
//	emit outputSignal("");
}

void CLIPSClass::loadSlot(QString path)
{
	Load(path.toLocal8Bit().data());
//	emit outputSignal("");
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

QStringList CLIPSClass::templatesSlot(bool ret)
{
	DATA_OBJECT retVal;
	char *tempPtr;
	void *multifieldPtr;
	QStringList templatesList;
	GetDeftemplateList(&retVal, NULL);
	multifieldPtr = GetValue(retVal);
	for (int i = GetDOBegin(retVal); i <= GetDOEnd(retVal); i++)
	{
		if ((GetMFType(multifieldPtr,i) == STRING) ||(GetMFType(multifieldPtr,i) == SYMBOL))
		{
			tempPtr = ValueToString(GetMFValue(multifieldPtr,i));
			templatesList<<QString(tempPtr);
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


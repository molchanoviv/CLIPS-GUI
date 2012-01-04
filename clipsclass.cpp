#include <iostream>
//#include <fcntl.h>
//#include <unistd.h>
#include "clipsclass.h"

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
	QStringList templates = templatesSlot(false);
	emit templatesChangedSignal(templates);
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
	int factNumber = 0;
	do
	{
		ptr = GetNextFact(ptr);
		char buf[16384]={0};
		if(ptr!=NULL)
		{
			factNumber = FactIndex(ptr);
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


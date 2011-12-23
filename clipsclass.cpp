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
	QString facts = factsSlot(false);
	emit factsChangedSignal(facts);

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
				QString facts = factsSlot(false);
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
	QString templates = templatesSlot(false);
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
	QString facts = factsSlot(false);
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
	QString facts = factsSlot(false);
	emit factsChangedSignal(facts);
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

QString CLIPSClass::factsSlot(bool ret)
{

	char buf[16384]={0};
	int fdpipe[2];
	pipe( fdpipe);
	int old=dup(fileno(stdout));
	dup2(fdpipe[1], fileno(stdout));
	Facts("stdout", NULL, -1, -1, -1);
	int r = read(fdpipe[0],buf,sizeof(buf));
	buf[r]=0;
	dup2(old, fileno(stdout));
	std::string str(buf);
	QString string;
	string = string.fromStdString(str).trimmed();
	if(ret)
		emit outputSignal(string);
	return string;
}

QString CLIPSClass::templatesSlot(bool ret)
{

	char buf[16384]={0};
	int fdpipe[2];
	pipe( fdpipe);
	int old=dup(fileno(stdout));
	dup2(fdpipe[1], fileno(stdout));
	ListDeftemplates("stdout", NULL);
	int r = read(fdpipe[0],buf,sizeof(buf));
	buf[r]=0;
	dup2(old, fileno(stdout));
	std::string str(buf);
	QString string;
	string = string.fromStdString(str).trimmed();
	if(ret)
		emit outputSignal(string);
	return string;
}


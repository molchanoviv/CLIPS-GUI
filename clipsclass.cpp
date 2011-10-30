#include <iostream>
//#include <fcntl.h>
//#include <unistd.h>
#include "clipsclass.h"

CLIPSClass::CLIPSClass(QObject *parent) :
	QObject(parent)
{
	InitializeEnvironment();
}

char* CLIPSClass::toChar(QString string)
{
	std::string str = string.toStdString();
	char* str_ptr = new char[ str.length() + 1 ]();
	strcpy( str_ptr, str.c_str() );
	return str_ptr;
	//delete[] str_ptr;

}

void CLIPSClass::assertStringSlot(QString fact, bool ret)
{
	fact.append(")").prepend("(");
	AssertString(toChar(fact));
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

void CLIPSClass::saveFactsSlot(QString path)
{
	SaveFacts(toChar(path),LOCAL_SAVE,NULL);
	emit outputSignal("");
}

void CLIPSClass::loadFactsSlot(QString path)
{
	LoadFacts(toChar(path));
	emit outputSignal("");
	QString facts = factsSlot(false);
	emit factsChangedSignal(facts);
}

void CLIPSClass::saveSlot(QString path)
{
	Save(toChar(path));
	emit outputSignal("");
}

void CLIPSClass::loadSlot(QString path)
{
	Load(toChar(path));
	emit outputSignal("");
	QString facts = factsSlot(false);
	emit factsChangedSignal(facts);
}

void CLIPSClass::clearSlot()
{
	Clear();
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


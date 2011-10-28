#include "clipsmmclass.h"

using namespace CLIPS;

CLIPSMMClass::CLIPSMMClass(QObject *parent) :
	QObject(parent)
{
	CLIPS::init();

	env.load( "strips.clp" );
}

void CLIPSMMClass::addFact(QString fact_str)
{
	const std::string str = fact_str.toStdString();
	//Fact::pointer fct = fact->create(env);
	fact = env.assert_fact(str);
}

QString CLIPSMMClass::getAllFacts()
{
	std::vector<std::string> slot_names;
	slot_names = fact->slot_names();
	for (int i=0; i<slot_names.size(); i++)
	{
		std::cout << "Slot name: " << slot_names.at(i) << std::endl;
		Values slot_values;
		slot_values = fact->slot_value(slot_names.at(i));
		std::cout<<"Values vector size: "<<slot_values.size()<<std::endl;
		for (int t=0; t<slot_values.size(); t++)
		{
			Value val = slot_values.at(i);
			std::cout << "Slot value: " << val.as_string() << std::endl;
		}

	}
	return "";
}

/*
#include <clipsmm.h>

#include <iostream>

int main( int argc, char** argv )
{
  CLIPS::init();

  CLIPS::Environment environment;
  CLIPS::Fact::pointer fact;
  std::vector<std::string> slot_names;
  std::vector<std::string>::iterator iter;

  environment.load( "strips.clp" );

  fact = environment.assert_fact("(in (object R2D2) (location RoomC) )");
  slot_names = fact->slot_names();
  for (iter = slot_names.begin(); iter != slot_names.end(); iter++)
    std::cout << "Slot name: " << *iter << std::endl;
  std::cout << std::endl;

  fact = environment.assert_fact("(numbers 1 2 3 4 5 )");
  slot_names = fact->slot_names();
  for (iter = slot_names.begin(); iter != slot_names.end(); iter++)
    std::cout << "Slot name: " << *iter << std::endl;

  return 0;
}
*/

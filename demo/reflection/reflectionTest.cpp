//
// Created by Jip Boesenkool on 10/06/2018.
//
#include "reflectionTest.h"

void ReflectionTest()
{
	TypeDatabase::Get().PrintAll();

	std::cout << "\nGetTypeByType(int) " << "\n";
	std::cout << GetTypeByType(int).mName << "\n";

	//std::cout << "\nGetTypeByString('int') " << "\n";
	//TODO: why doesn't this work!!!
	//std::cout << TypeDatabase::Get().GetType("int").mName << "\n";

	//Variable
	Var v;
	v = std::string( "test" );
	//Simple cast
	//TODO: Create automatic with template metaprogramming
	std::string str;
	if( v.GetType()->mName.compare("std::string") == 0 )
	{
		str = v.GetValue<std::string>();
		std::cout << "Type: " << v.GetType()->mName << "\n"
				  << "Value: " << str << "\n";
	}

	v = 1;
	//Typededuction test
	int i;
	int j;
	if( v.GetType()->mName.compare(GetTypeByType(int).mName) )
	{
		i = v.GetValue<int>(  );
		std::cout << "Type: " << v.GetType()->mName << "\n"
				  << "Value: " << i << "\n";

		j = v.GetValue(i);
		std::cout << "Type deduction" << "\n";
		std::cout << "Type: " << v.GetType()->mName << "\n"
				  << "Value: " << j << "\n";
	}

	//Varbag aka blackboard
	VarBag bb;
	Var dmg = 1;
	Var def = 2;
	bb.Set("damage", dmg);
	bb.Set("defence", def );

	for (const auto& pair : *( bb.GetMap() ) ) {
		std::cout << "Property: "<< pair.first << "\n";
		const TypeDesc* td = pair.second.GetType();
		std::cout << "Type: " << td->mName << "\n";
	}
}


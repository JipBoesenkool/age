#include "../include/age.h"
#include <iostream>

//---------------------------------------------------------------------------------------------------------------------
// Getters & Setters
//---------------------------------------------------------------------------------------------------------------------
MessageBus* Age::GetMessageBus(void)
{
	if(mpMessageBus == nullptr)
	{
		mpMessageBus = new MessageBus();
	}
	return mpMessageBus;
}

void Age::hello() {
	std::cout << "Hello, Engine!" << std::endl;
}

/*
void Age::VarTest()
{
	//Variable
	Var v;
	v = 1;
	//v = 5.0;
	//v = std::string("string");

	//Simple cast
	//Create automatic with template metaprogramming
	std::string str;
	if( v.GetType()->mName == "std::string" )
	{
		str = v.GetValue<std::string>();
		std::cout << "Type: " << v.GetType()->mName << "\n"
				  << "Value: " << str << "\n";
	}

	//Typededuction test
	int i;
	int j;
	if( v.GetType()->mName == GetTypeByType(int).mName )
	{
		i = v.GetValue<int>(  );
		std::cout << "Type: " << v.GetType()->mName << "\n"
				  << "Value: " << i << "\n";

		j = v.GetValue(i);
		std::cout << "Type deduction" << "\n";
		std::cout << "Type: " << v.GetType()->mName << "\n"
				  << "Value: " << j << "\n";
	}
}
 */

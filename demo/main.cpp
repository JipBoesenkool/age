#include <age.h>
#include <reflection/Reflection.h>
#include <ecs/Component.h>
#include <iostream>

//BEGIN EXAMPLE CODE
struct TestComponent : public ecs::Component<TestComponent>
{
	float x;
	float y;
};

void ComponentTest()
{
	TestComponent tComp;
	tComp.x = 1.0f;
	tComp.y = 2.0f;
}

void ReflectionTest()
{
	//Variable
	Var v;
	v = std::string( "test" );
	//Simple cast
	//TODO: Create automatic with template metaprogramming
	std::string str;
	if( strcmp(v.GetType()->mName, "std::string") == 0 )
	{
		str = v.GetValue<std::string>();
		std::cout << "Type: " << v.GetType()->mName << "\n"
				  << "Value: " << str << "\n";
	}

	v = 1;
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

int main() {
	std::cout << "Age demo started." << "\n";
	ComponentTest();
	ReflectionTest();
	return 0;
}
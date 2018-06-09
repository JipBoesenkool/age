#include "age.h"

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

void Age::EngineApiTest() {
	std::cout << "Hello, Engine!" << std::endl;
}

#ifndef AGE_H
#define AGE_H

#include "pattern/message/SimpleExample/Message.h"
#include "pattern/message/SimpleExample/MessageBus.h"

class Age
{
public:
	static Age& Get()
	{
		static Age instance;
		return instance;
	}

	static void hello();
	//static void VarTest();

	MessageBus* GetMessageBus();

private:
	MessageBus* mpMessageBus = nullptr;
};

#endif // AGE_H

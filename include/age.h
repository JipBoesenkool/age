#ifndef AGE_H
#define AGE_H

#include "pattern/message/Message.h"
#include "pattern/message/MessageBus.h"

class Age
{
public:
	static Age& Get()
	{
		static Age instance;
		return instance;
	}

	static void EngineApiTest();

	MessageBus* GetMessageBus();

private:
	MessageBus* mpMessageBus = nullptr;
};

#endif // AGE_H

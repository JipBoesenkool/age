#ifndef AGE_H
#define AGE_H

#include "pattern/message/Message.h"
#include "pattern/message/MessageBus.h"

#define NDEBUG true
#if NDEBUG
	#define Log(x) std::cout << x << "\n";
#else
	#define Log(x)
#endif

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

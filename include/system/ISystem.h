//
// Created by Jip Boesenkool on 21/05/2018.
//

#ifndef AGE_ISYSTEM_H
#define AGE_ISYSTEM_H

#include "pattern/message/SimpleExample/Message.h"
#include "pattern/pubsub/ISubscriber.h"

class ISystem : public ISubscriber<IMessagePtr>
{
public:
	//Observer
	virtual void On(IMessagePtr msg) override
	{
		//do nothing
	};
};

#endif //AGE_ISYSTEM_H

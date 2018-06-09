//
// Created by Jip Boesenkool on 21/05/2018.
//

#ifndef AGE_MESSAGEBUS_H
#define AGE_MESSAGEBUS_H

#include "Message.h"
#include "system/ISystem.h"
#include "pattern/pubsub/Channel.h"

#include <queue>
#include <map>
#include <vector>

//---------------------------------------------------------------------------------------------------------------------
// Forward declaration & typedefs
//---------------------------------------------------------------------------------------------------------------------
#define INFINITE 0xffffffff

class MessageBus
{
//-------------------------------------------------------------------------------------------------------------------
// Members
//-------------------------------------------------------------------------------------------------------------------
private:
	typedef Channel<IMessagePtr>* MsgChannelPtr;
	typedef std::queue<IMessagePtr> MessageQueue;
	typedef std::map<std::string, MsgChannelPtr > MessageChannelMap;

	MessageQueue mMessageQueue;
	MessageChannelMap mMessageChannels;
//---------------------------------------------------------------------------------------------------------------------
// Public Functions
//---------------------------------------------------------------------------------------------------------------------
public:
	explicit MessageBus();
	virtual ~MessageBus(void);

	//pubsub
	void AddListener(const std::string& msgTypeName, ISystem* pListener);
	void RemoveListener(const std::string& msgTypeName, ISystem* pListener);

	//MessageBus
	bool Trigger(const IMessagePtr& pMsg) const;
	bool Queue(const IMessagePtr& pMsg);

	void Update(unsigned long maxMillis = INFINITE);
};

#endif //AGE_MESSAGEBUS_H

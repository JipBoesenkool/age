//
// Created by Jip Boesenkool on 21/05/2018.
//
//Debugging
#include <iostream>

#include "pattern/message/MessageBus.h"
MessageBus::MessageBus()
{
	//Empty constructor
}

MessageBus::~MessageBus( void )
{
	//Empty destructor
}

void MessageBus::AddListener(const std::string& msgTypeName, ISystem* pListener)
{
	//Find message
	MessageChannelMap::iterator itr = mMessageChannels.find( msgTypeName );
	if( itr == mMessageChannels.end() )
	{
		//Add message to the list
		mMessageChannels[ msgTypeName ] = new Channel<IMessagePtr>;

		std::cout << "ERROR::MessageBus::AddListener: msgTypeName is not registered" << "\n";
	}

	//Check if listener is already there
	MsgChannelPtr channel = mMessageChannels[msgTypeName];
	channel->AddListener( pListener );
}

void MessageBus::RemoveListener(const std::string& msgTypeName, ISystem* pListener)
{
	//Find message
	MessageChannelMap::iterator itr = mMessageChannels.find( msgTypeName );
	if( itr == mMessageChannels.end() )
	{
		std::cout << "ERROR::MessageBus::RemoveListener: msgTypeName is not registered" << "\n";
	}

	//Remove the listener from the channel
	MsgChannelPtr channel = mMessageChannels[msgTypeName];
	channel->RemoveListener( pListener );
}

bool MessageBus::Trigger( const IMessagePtr &pMsg ) const
{
	bool processed = false;

	auto findIt = mMessageChannels.find( pMsg->GetTypeName() );
	if (findIt != mMessageChannels.end())
	{
		MsgChannelPtr channel = findIt->second;
		channel->Handle( pMsg );
		processed = true;
	}
	return processed;
}

bool MessageBus::Queue( const IMessagePtr &pMsg )
{
	// make sure the event is valid
	if (!pMsg)
	{
		std::cerr << "ERROR::MessageBus::Queue: Invalid message parameter." << std::endl;
		return false;
	}


	auto findIt = mMessageChannels.find( pMsg->GetTypeName() );
	if (findIt != mMessageChannels.end())
	{
		mMessageQueue.push( pMsg );
		std::cout << "MessageBus::Queue: Successfully queued message: " << pMsg->GetTypeName() << std::endl;
		return true;
	}
	else
	{
		std::cout << "ERROR::MessageBus::Queue: Skipping message since there are no listeners registered to receive it: " << pMsg->GetTypeName() << std::endl;
		return false;
	}
}

void MessageBus::Update( unsigned long maxMillis )
{
	while( !mMessageQueue.empty() )
	{
		IMessagePtr pMsg = mMessageQueue.front();
		if(pMsg == nullptr)
		{
			return;
		}
		mMessageQueue.pop();

		const std::string& msgName = pMsg->GetTypeName();

		//Find message type
		MsgChannelPtr channel = mMessageChannels[ pMsg->GetTypeName() ];
		channel->Handle( pMsg );
	}
}


//
// Created by Jip Boesenkool on 21/05/2018.
//
#ifndef AGE_MESSAGE_H
#define AGE_MESSAGE_H

#include <string>
#include "../../../reflection/Var.h"

//---------------------------------------------------------------------------------------------------------------------
// Forward declaration & typedefs
//---------------------------------------------------------------------------------------------------------------------
class IMessage;
typedef std::shared_ptr<IMessage> IMessagePtr;
//---------------------------------------------------------------------------------------------------------------------
// IMessage
//---------------------------------------------------------------------------------------------------------------------
class IMessage
{
//---------------------------------------------------------------------------------------------------------------------
// Getters & Setters
//---------------------------------------------------------------------------------------------------------------------
public:
	virtual float GetTimeStamp(void) const	= 0;
	virtual std::string& GetTypeName(void)	= 0;
//---------------------------------------------------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------------------------------------------------
public:
	virtual ~IMessage(void) {}
	virtual IMessagePtr Copy(void) const	= 0;
};
//-------------------------------------------------------------------------------------------------------------------
// class Message
// Base type for message object hierarchy, may be used itself for simplest event notifications such as those that do
// not carry additional payload data. If any message needs to propagate with payload data it must be defined separately.
//-------------------------------------------------------------------------------------------------------------------
class Message : public IMessage
{
//-------------------------------------------------------------------------------------------------------------------
// Members
//-------------------------------------------------------------------------------------------------------------------
protected:
	const float mTimeStamp;
	std::string mTypeName;
//-------------------------------------------------------------------------------------------------------------------
// Getters & Setters
//-------------------------------------------------------------------------------------------------------------------
public:
	float GetTimeStamp(void) const { return mTimeStamp; }
	virtual std::string& GetTypeName(void) { return mTypeName; }
//-------------------------------------------------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------------------------------------------------
public:
	explicit Message(std::string typeName, const float timeStamp = 0.0f) : mTypeName(typeName), mTimeStamp(timeStamp) { }
	virtual IMessagePtr Copy(void) const
	{
		return IMessagePtr( new Message(mTypeName, mTimeStamp) );
	}
};
//-------------------------------------------------------------------------------------------------------------------
// class VarMessage
// Message which uses reflection variable to carry the payload.
//-------------------------------------------------------------------------------------------------------------------
class VarMessage : public Message
{
//-------------------------------------------------------------------------------------------------------------------
// Members
//-------------------------------------------------------------------------------------------------------------------
private:
	Var mData;
//-------------------------------------------------------------------------------------------------------------------
// Getters & Setters
//-------------------------------------------------------------------------------------------------------------------
public:
	Var& GetData(){ return mData; }
public:
//-------------------------------------------------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------------------------------------------------
public:
	explicit VarMessage(std::string typeName, Var data ,const float timeStamp = 0.0f)
		: Message(typeName, timeStamp), mData(data) { }
	virtual IMessagePtr Copy(void) const
	{
		return IMessagePtr( new VarMessage(mTypeName, mData, mTimeStamp) );
	}
};

#endif //AGE_MESSAGE_H
#ifndef WINDOWRESIZEEVENT_H
#define WINDOWRESIZEEVENT_H
//---------------------------------------------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------------------------------------------
#include "BaseEvent.h"
//-------------------------------------------------------------------------------------------------------------------
// class WindowResizeEvent
//-------------------------------------------------------------------------------------------------------------------
class WindowResizeEvent : public BaseEvent
{
//-------------------------------------------------------------------------------------------------------------------
// Members
//-------------------------------------------------------------------------------------------------------------------
public:
	int mWidth;
	int mHeight;
//-------------------------------------------------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------------------------------------------------
public:
	WindowResizeEvent(void)
	{
		m_eventName = "WindowResizeEvent";
		mWidth = 0;
		mHeight= 0;
	}

	explicit WindowResizeEvent(int width, int height)
	{
		m_eventName = "WindowResizeEvent";
		mWidth = width;
		mHeight= height;
	}

	virtual IEventPtr Copy(void) const
	{
		return IEventPtr( new WindowResizeEvent(mWidth, mHeight) );
	}
};
#endif //WINDOWRESIZEEVENT_H

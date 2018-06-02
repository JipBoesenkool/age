//
// Created by Jip Boesenkool on 26/05/2018.
//

#ifndef AGE_CHANNEL_H
#define AGE_CHANNEL_H

#include <vector>
#include "ISubscriber.h"

template<typename MsgType>
class Channel
{
public:
	void AddListener( ISubscriber<MsgType>* pListener )
	{
		//Check if listener is already there
		for (auto itr = mListeners.begin(); itr != mListeners.end(); ++itr)
		{
			if ( (*itr) == pListener )
			{
				//Listener already added
				return;
			}
		}

		mListeners.push_back( pListener );
	};

	void RemoveListener( ISubscriber<MsgType>* pListener )
	{
		//Find and remove listener
		for( auto itr = mListeners.begin(); itr != mListeners.end(); ++itr )
		{
			if( (*itr) == pListener )
			{
				mListeners.erase( itr );
				return;
			}
		}
	};

	void Handle( MsgType msg )
	{
		//Simple redirect the messages
		for( int i = 0; i < mListeners.size(); i++ ) {
			ISubscriber<MsgType>* listener = mListeners[i];
			listener->On( msg );
		}
	};

private:
	std::vector< ISubscriber<MsgType>* > mListeners;
};

#endif //AGE_CHANNEL_H

//
// Created by Jip Boesenkool on 26/05/2018.
//

#ifndef AGE_ISUBSCRIBER_H
#define AGE_ISUBSCRIBER_H

template<typename MsgType>
class ISubscriber
{
public:
	virtual void On(MsgType msg) = 0;
};

#endif //AGE_ISUBSCRIBER_H

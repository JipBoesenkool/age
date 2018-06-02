//
// Created by Jip Boesenkool on 26/05/2018.
//

#ifndef AGE_IPUBLISHER_H
#define AGE_IPUBLISHER_H

template<typename MsgType>
class IPublisher
{
public:
	virtual void Publish(MsgType* msg) = 0;
};

#endif //AGE_PUBLISHER_H

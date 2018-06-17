//
// Created by Jip Boesenkool on 10/06/2018.
//
#ifndef AGE_INDEXBUFFER_H
#define AGE_INDEXBUFFER_H

#include "renderer/renderer/RenderResource.h"

struct IndexBufferObject
{
	unsigned int* 	mpData;
	unsigned int 	mCount;
};

class IndexBuffer : public RenderResource
{
protected:
	unsigned int mCount;
public:
	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	inline unsigned int GetCount() { return mCount; };
};

#endif //AGE_INDEXBUFFER_H

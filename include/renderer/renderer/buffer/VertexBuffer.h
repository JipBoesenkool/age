//
// Created by Jip Boesenkool on 10/06/2018.
//

#ifndef AGE_VERTEXBUFFER_H
#define AGE_VERTEXBUFFER_H

#include "renderer/renderer/RenderResource.h"

struct VertexBufferObject
{
	void* 			mpData;
	unsigned int 	mSize;
};

class VertexBuffer : public RenderResource
{
public:
	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;
};

#endif //AGE_VERTEXBUFFER_H

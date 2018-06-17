//
// Created by Jip Boesenkool on 10/06/2018.
//

#ifndef AGE_VERTEXARRAY_H
#define AGE_VERTEXARRAY_H

#include "renderer/renderer/RenderResource.h"
#include "renderer/renderer/buffer/VertexBuffer.h"
#include "renderer/renderer/buffer/VertexBufferLayout.h"

class VertexArray : public RenderResource
{
public:
	virtual void AddBuffer( const VertexBuffer& vb, VertexBufferLayout& layout ) = 0;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;
};

#endif //AGE_VERTEXARRAY_H

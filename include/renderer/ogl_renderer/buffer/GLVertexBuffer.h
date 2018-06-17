//
// Created by Jip Boesenkool on 10/06/2018.
//

#ifndef AGE_GLVERTEXBUFFER_H
#define AGE_GLVERTEXBUFFER_H

#include "renderer/renderer/buffer/VertexBuffer.h"

class GLVertexBuffer : public VertexBuffer
{
public:
	GLVertexBuffer(const VertexBufferObject& vbo);
	GLVertexBuffer(const void* pData, unsigned int size);
	~GLVertexBuffer();

	void Bind() const override;
	void Unbind() const override;
};

#endif //AGE_GLVERTEXBUFFER_H

//
// Created by Jip Boesenkool on 10/06/2018.
//

#ifndef AGE_GLINDEXBUFFER_H
#define AGE_GLINDEXBUFFER_H

#include "renderer/renderer/buffer/IndexBuffer.h"

class GLIndexBuffer : public IndexBuffer
{
public:
	GLIndexBuffer(const IndexBufferObject& ibo);
	GLIndexBuffer(const unsigned int* data, unsigned int count);
	~GLIndexBuffer();

	void Bind() const override;
	void Unbind() const override;
};

#endif //AGE_GLINDEXBUFFER_H

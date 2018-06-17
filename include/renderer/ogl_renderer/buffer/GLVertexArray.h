//
// Created by Jip Boesenkool on 10/06/2018.
//
#ifndef AGE_GLVERTEXARRAY_H
#define AGE_GLVERTEXARRAY_H

#include <renderer/renderer/buffer/VertexArray.h>
#include "GLVertexBufferLayoutImpl.h"

class GLVertexArray : public VertexArray
{
private:
	static GLVertexBufferLayoutImpl sImplCalcStride;
public:
	GLVertexArray();
	~GLVertexArray();

	void AddBuffer( const VertexBuffer& vb, VertexBufferLayout& layout ) override;

	void Bind() const override;
	void Unbind() const override;
};

#endif //AGE_GLVERTEXARRAY_H

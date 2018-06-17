//
// Created by Jip Boesenkool on 10/06/2018.
//
#include <glad/glad.h>

#include "renderer/ogl_renderer/buffer/GLVertexArray.h"

#include <renderer/renderer/buffer/VertexBuffer.h>
#include "renderer/ogl_renderer/GLUtilities.h"

GLVertexBufferLayoutImpl GLVertexArray::sImplCalcStride;

GLVertexArray::GLVertexArray()
{
	GLCall( glGenVertexArrays(1, &mRendererId) );
	Bind();
}

GLVertexArray::~GLVertexArray()
{
	GLCall( glDeleteVertexArrays(1, &mRendererId) );
}

void GLVertexArray::AddBuffer( const VertexBuffer& vb, VertexBufferLayout& layout )
{
	Bind();
	vb.Bind();
	auto& elements = layout.GetElements();
	unsigned int stride = sImplCalcStride.CalculateStride( &layout.GetElements() );
	size_t offset = 0;
	for(unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& el = elements[i];
		GLCall( glEnableVertexAttribArray(i) );
		GLCall( glVertexAttribPointer(i, el.mCount, el.mType,
									  el.mNormalized ? GL_TRUE : GL_FALSE,
									  stride, (GLvoid *)offset) );
		offset += el.mSize * el.mCount;
	}
	vb.Unbind();
	GLCall( glEnableVertexAttribArray(0) );
}

void GLVertexArray::Bind() const
{
	GLCall( glBindVertexArray(mRendererId) );
}

void GLVertexArray::Unbind() const
{
	GLCall( glBindVertexArray(0) );
}
//
// Created by Jip Boesenkool on 10/06/2018.
//
#include <glad/glad.h>

#include "renderer/ogl_renderer/buffer/GLIndexBuffer.h"
#include "ogl_renderer/GLUtilities.h"

//Public
GLIndexBuffer::GLIndexBuffer(const IndexBufferObject& ibo)
{
	//parent member
	mCount = ibo.mCount;

	//Check if platform behaves
	assert( sizeof(unsigned int) == sizeof(GLuint) );

	GLCall( glGenBuffers(1, &mRendererId) );
	GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererId) );
	GLCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, mCount * sizeof(unsigned int), ibo.mpData, GL_STATIC_DRAW) );

}
GLIndexBuffer::GLIndexBuffer(const unsigned int* pData, unsigned int count)
{
	//parent member
	mCount = count;

	//Check if platform behaves
	assert( sizeof(unsigned int) == sizeof(GLuint) );

	GLCall( glGenBuffers(1, &mRendererId) );
	GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererId) );
	GLCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), pData, GL_STATIC_DRAW) );

}
GLIndexBuffer::~GLIndexBuffer()
{
	GLCall( glDeleteBuffers(1, &mRendererId) );
}

void GLIndexBuffer::Bind() const
{
	GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererId) );
}
void GLIndexBuffer::Unbind() const
{
	GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
}


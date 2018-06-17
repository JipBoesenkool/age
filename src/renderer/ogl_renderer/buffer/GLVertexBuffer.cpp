//
// Created by Jip Boesenkool on 10/06/2018.
//
#include <glad/glad.h>

#include "renderer/ogl_renderer/buffer/GLVertexBuffer.h"
#include "ogl_renderer/GLUtilities.h"

//Public
GLVertexBuffer::GLVertexBuffer(const VertexBufferObject& vbo)
{
	GLCall( glGenBuffers(1, &mRendererId) );
	GLCall( glBindBuffer(GL_ARRAY_BUFFER, mRendererId) );
	GLCall( glBufferData(GL_ARRAY_BUFFER, vbo.mSize, vbo.mpData, GL_STATIC_DRAW) );

}
GLVertexBuffer::GLVertexBuffer(const void* pData, unsigned int size)
{
	GLCall( glGenBuffers(1, &mRendererId) );
	GLCall( glBindBuffer(GL_ARRAY_BUFFER, mRendererId) );
	GLCall( glBufferData(GL_ARRAY_BUFFER, size, pData, GL_STATIC_DRAW) );

}
GLVertexBuffer::~GLVertexBuffer()
{
	GLCall( glDeleteBuffers(1, &mRendererId) );
}

void GLVertexBuffer::Bind() const
{
	GLCall( glBindBuffer(GL_ARRAY_BUFFER, mRendererId) );
}
void GLVertexBuffer::Unbind() const
{
	GLCall( glBindBuffer(GL_ARRAY_BUFFER, 0) );
}


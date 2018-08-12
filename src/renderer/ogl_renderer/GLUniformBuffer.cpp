//
// Created by Jip Boesenkool on 12/08/2018.
//
#include <renderer/ogl_renderer/GLUniformBuffer.h>

#include <reflection/Reflection.h>
#include <reflection/TypeDesc.h>
#include <glad/glad.h>

GLUniformBuffer::GLUniformBuffer( )
{
	//Empty constructor
}

GLUniformBuffer::~GLUniformBuffer()
{
	GLCall( glDeleteBuffers(1, &mUBOHandle) );
}

void GLUniformBuffer::Init( const std::string &name, UniformList *pUniforms, Shader* shaderBegin, unsigned int shaderCount )
{
	mBufferName = name;
	mpUniforms  = pUniforms;

	// link each shader's uniform block to this uniform binding point
	for( int i = 0; i < shaderCount; i++ )
	{
		Shader& s = shaderBegin[i];
		GLCall( unsigned int blockIndex = glGetUniformBlockIndex( s.mRendererId, mBufferName.c_str() ) );
		GLCall( glUniformBlockBinding( s.mRendererId, blockIndex, 0 ) );
	}

	//Calculate the block size
	unsigned int blockSize = 0;
	std::vector<Uniform>& uniforms = mpUniforms->GetUniforms();
	for( int i = 0; i < uniforms.size(); i++ )
	{
		Uniform& u = uniforms[i];
		TypeDesc& typeDesc = TypeDatabase::Get().GetType( u.mTypeName.c_str() );
		blockSize += typeDesc.mSize;
	}

	// Create the buffer
	GLCall( glGenBuffers(1, &mUBOHandle) );
	GLCall( glBindBuffer(GL_UNIFORM_BUFFER, mUBOHandle) );
	GLCall( glBufferData(GL_UNIFORM_BUFFER, blockSize, NULL, GL_STATIC_DRAW) );
	GLCall( glBindBuffer(GL_UNIFORM_BUFFER, 0) );

	// define the range of the buffer that links to a uniform binding point
	GLCall( glBindBufferRange(GL_UNIFORM_BUFFER, 0, mUBOHandle, 0, blockSize) );
}

void GLUniformBuffer::Bind()
{
	unsigned int uniformSize = 0;
	unsigned int blockIndex  = 0;
	std::vector<Uniform>& uniforms = mpUniforms->GetUniforms();

	GLCall( glBindBuffer(GL_UNIFORM_BUFFER, mUBOHandle) );
	for( int i = 0; i < uniforms.size(); i++ )
	{
		Uniform& u = uniforms[i];
		TypeDesc& typeDesc = TypeDatabase::Get().GetType( u.mTypeName.c_str() );
		GLCall( glBufferSubData(GL_UNIFORM_BUFFER, blockIndex, typeDesc.mSize, u.mpData ) );
		blockIndex += uniformSize;
	}
	GLCall( glBindBuffer(GL_UNIFORM_BUFFER, 0) );
}

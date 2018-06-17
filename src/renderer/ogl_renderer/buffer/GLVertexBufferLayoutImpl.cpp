//
// Created by Jip Boesenkool on 10/06/2018.
//
#include <glad/glad.h>

#include <unordered_map>
#include "renderer/ogl_renderer/buffer/GLVertexBufferLayoutImpl.h"
#include "renderer/ogl_renderer/GLUtilities.h"

std::unordered_map<std::string, std::pair<unsigned int, unsigned int> > GLVertexBufferLayoutImpl::sGLTypeMap
{
	{"int", {GL_INT, sizeof(GLint)} },
	{"uint", {GL_UNSIGNED_INT, sizeof(GLuint)} },
	{"float", {GL_FLOAT, sizeof(GLfloat)} }
};

//Functions
//public:
unsigned int GLVertexBufferLayoutImpl::CalculateStride( std::vector< VertexBufferElement >* elements )
{
	unsigned int stride = 0;
	for(auto itr = elements->begin(); itr < elements->end(); ++itr)
	{
		itr->mType = GLTypeOf( itr->mTypeName );
		itr->mSize = GLSizeOf( itr->mTypeName );
		stride += GLSizeOf( itr->mTypeName ) * itr->mCount;
	}
	return stride;
}

//private:
unsigned int GLVertexBufferLayoutImpl::GLTypeOf(const std::string& typeName)
{
	if( sGLTypeMap.find( typeName ) != sGLTypeMap.end() )
	{
		return sGLTypeMap[typeName].first;
	}

	//Error
	assert(false);
	return 0;
}

unsigned int GLVertexBufferLayoutImpl::GLSizeOf(const std::string& typeName)
{
	if( sGLTypeMap.find( typeName ) != sGLTypeMap.end() )
	{
		return sGLTypeMap[typeName].second;
	}

	//Error
	assert(false);
	return 0;
}



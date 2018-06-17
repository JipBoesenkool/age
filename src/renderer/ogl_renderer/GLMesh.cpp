//
// Created by Jip Boesenkool on 16/06/2018.
//
#include <glad/glad.h>
#include <renderer/ogl_renderer/GLUtilities.h>

#include <renderer/ogl_renderer/GLMesh.h>

//public:
GLMesh::GLMesh( std::string name, VertexBufferLayout& layout, const VertexBufferObject& vbo, const IndexBufferObject& ibo )
	: mName(name), mVbo( vbo ), mIbo( ibo )
{
	mVao.AddBuffer(mVbo, layout);
}

GLMesh::~GLMesh()
{

}

GLMesh::GLMesh(GLMesh&& other)
	: mVao(other.mVao), mVbo(other.mVbo), mIbo(other.mIbo)
{

}

GLMesh& GLMesh::operator=(GLMesh&& other)
{
	// Self-assignment detection
	if (&other == this)
		return *this;

	// Transfer ownership of a.m_ptr to m_ptr
	mVao = other.mVao;
	mVbo = other.mVbo;
	mIbo = other.mIbo;

	return *this;
}

void GLMesh::Render(Shader& shader)
{
	shader.Bind();
	shader.SetUniformVec4( "uColor", 0.2f, 0.3f, 0.8f, 1.0f );

	//TODO: set uniforms
	mVao.Bind();
	GLCall( glDrawElements(GL_TRIANGLES, mIbo.GetCount(), GL_UNSIGNED_INT, 0) );
	mVao.Unbind();
}

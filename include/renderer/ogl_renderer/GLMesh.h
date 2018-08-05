//
// Created by Jip Boesenkool on 16/06/2018.
//

#ifndef AGE_GLMESH_H
#define AGE_GLMESH_H

#include <renderer/renderer/Mesh.h>

#include <renderer/renderer/buffer/VertexBufferLayout.h>
#include <renderer/ogl_renderer/GLShader.h>

#include <renderer/ogl_renderer/buffer/GLVertexArray.h>
#include <renderer/ogl_renderer/buffer/GLVertexBuffer.h>
#include <renderer/ogl_renderer/buffer/GLIndexBuffer.h>

class GLMesh
{
//Members
private:
	std::string 	mName;
	GLVertexArray 	mVao;
	GLVertexBuffer  mVbo;
	GLIndexBuffer 	mIbo;
public:
	GLMesh( std::string name, VertexBufferLayout& layout, const VertexBufferObject& vbo, const IndexBufferObject& ibo );
	~GLMesh();

	GLMesh(GLMesh&& other); //Move constructor
	GLMesh& operator=(GLMesh&& other); //Move assignment

	void Render();
};

#endif //AGE_GLMESH_H

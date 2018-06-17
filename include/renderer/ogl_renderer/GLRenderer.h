//
// Created by Jip Boesenkool on 10/06/2018.
//

#ifndef AGE_GLRENDERER_H
#define AGE_GLRENDERER_H

#include "GLUtilities.h"

//buffer
#include "buffer/GLVertexBufferLayoutImpl.h"
#include "buffer/GLVertexBuffer.h"
#include "buffer/GLVertexArray.h"
#include "buffer/GLIndexBuffer.h"

//Misc
#include "GLShader.h"
#include "GLMesh.h"

#include <unordered_map>

class GLRenderer
{
//Members
private:
	GLVertexBufferLayoutImpl* gBufferLayoutImpl;
	//TODO: Create store object
	std::unordered_map<std::string, unsigned int> mMeshMap;
	std::vector<GLMesh> mMeshes;
	std::unordered_map<std::string, unsigned int> mShaderMap;
	std::vector<GLShader> mShaders;
//Functions
public:
	GLRenderer();
	~GLRenderer();

	ShaderHandle CreateShader(const std::string& name, const std::string& filePath);
	MeshHandle CreateMesh(const std::string& name, VertexBufferLayout& layout, const VertexBufferObject& vbo, const IndexBufferObject& ibo);

	void Clear();
	void Render( ShaderHandle shader, MeshHandle mesh );
private:
	void PrintVersions();
	GLShader* shader;
	GLMesh* mesh;

//Test
	/*
public:
	void InitTest();
	void Test();
private:
	GLShader* shader;
	GLVertexBuffer* vb;
	GLVertexArray* va;
	GLIndexBuffer* ib;
	GLMesh* mesh;
	 */
};


#endif //AGE_GLRENDERER_H

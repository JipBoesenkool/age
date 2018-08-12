//
// Created by Jip Boesenkool on 10/06/2018.
//

#ifndef AGE_GLRENDERER_H
#define AGE_GLRENDERER_H

#include <renderer/renderer/Renderer.h>

#include "GLUtilities.h"

//buffer
#include "buffer/GLVertexBufferLayoutImpl.h"
#include "buffer/GLVertexBuffer.h"
#include "buffer/GLVertexArray.h"
#include "buffer/GLIndexBuffer.h"

//Misc
#include "GLShader.h"
#include "GLMesh.h"
#include "GLUniform.h"
#include "GLUniformBuffer.h"

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
//Getters
public:
	MeshHandle GetMeshHandle( std::string name ){ return mMeshMap[name]; }
	std::vector<GLMesh>& GetMeshes( ){ return mMeshes; }
	ShaderHandle GetShaderHandle( std::string name ){ return mShaderMap[name]; }
	Shader& GetShader( ShaderHandle shaderId ){ return mShaders[ shaderId ]; }
	Shader& GetShader( std::string name ){ return mShaders[ mShaderMap[name] ]; }
	std::vector<GLShader>& GetShaders( ){ return mShaders; }
//Functions
public:
	GLRenderer();
	~GLRenderer();

	ShaderHandle CreateShader(const std::string& name, const std::string& filePath);
	MeshHandle CreateMesh(const std::string& name, VertexBufferLayout& layout, const VertexBufferObject& vbo, const IndexBufferObject& ibo);

	void Clear();
	void Render( ShaderHandle shaderHandle, MeshHandle meshHandle, UniformList* uniformList );
	void Render( ShaderHandle shaderHandle, MeshHandle meshHandle, glm::vec3& position );
	void Render( ShaderHandle shaderHandle, MeshHandle meshHandle, glm::mat4& modelMatrix );
	void SetUniforms( UniformList* uniformList, Shader& shader);
private:
	void PrintVersions();
};

#endif //AGE_GLRENDERER_H

//
// Created by Jip Boesenkool on 10/06/2018.
//

#include <glad/glad.h>

#include <core/IWindow.h>

#include <renderer/ogl_renderer/GLRenderer.h>
#include <renderer/ogl_renderer/GLUtilities.h>

#include <renderer/ogl_renderer/GLShader.h>
#include <renderer/ogl_renderer/GLMesh.h>
#include <glm/detail/type_mat.hpp>
#include <glm/matrix.hpp>

GLRenderer::GLRenderer()
{
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)IWindow::Get()->GetProcAddress()))
	{
		std::cout << "RendererOGL::Failed to initialize GLAD" << std::endl;
		return;
	}

	PrintVersions();

	GLCall( glClearColor(0.2f, 0.3f, 0.3f, 1.0f) );

	glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
	//Wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	gBufferLayoutImpl = new GLVertexBufferLayoutImpl();
	//UniformList::sUniformImpl = new GLUniform();

	//PrintVersions();
	//SetupOpenglSettings();
	//SetupShaders();
	//SetupEventListeners();
}

GLRenderer::~GLRenderer()
{

}

ShaderHandle GLRenderer::CreateShader(const std::string& name, const std::string& filePath )
{
	//Find and return
	auto itr = mShaderMap.find( name );
	if(itr != mShaderMap.end() )
	{
		return itr->second;
	}

	//Create
	unsigned int index = mShaders.size();
	mShaderMap.insert(
			std::pair<std::string, unsigned int>( name, index )
	);
	ShaderResource sRes{name, filePath};
	mShaders.emplace_back( filePath );

	//Return handle
	return index;
}

MeshHandle GLRenderer::CreateMesh(const std::string& name, VertexBufferLayout& layout, const VertexBufferObject& vbo, const IndexBufferObject& ibo)
{
	//Find and return
	auto itr = mMeshMap.find( name );
	if(itr != mMeshMap.end() )
	{
		return itr->second;
	}

	//Create
	unsigned int index = mMeshes.size();
	mMeshMap.insert(
			std::pair<std::string, unsigned int>( name, index )
	);
	Mesh mRes{name, layout, vbo, ibo};
	mMeshes.emplace_back( name, layout, vbo, ibo );

	//Return handle
	return index;
}

void GLRenderer::Clear() {
	// Clear the colorbuffer
	GLCall( glClear(GL_COLOR_BUFFER_BIT) );
}

void GLRenderer::Render( ShaderHandle shaderHandle, MeshHandle meshHandle, UniformList* uniformList = nullptr )
{
	GLMesh& mesh = mMeshes[ meshHandle ];

	GLShader& shader = mShaders[ shaderHandle ];
	shader.Bind();

	if( uniformList != nullptr )
	{
		SetUniforms( uniformList, shader );
	}

	mesh.Render();
}

void GLRenderer::Render( ShaderHandle shaderHandle, MeshHandle meshHandle, glm::vec3& position )
{
	GLMesh& mesh = mMeshes[ meshHandle ];

	GLShader& shader = mShaders[ shaderHandle ];
	shader.Bind();

	//TODO: find better way for this
	//Set transform
	shader.SetUniformVec3("uPosition", position);

	mesh.Render();
}

void GLRenderer::Render( ShaderHandle shaderHandle, MeshHandle meshHandle, glm::mat4& modelMatrix )
{
	GLMesh& mesh = mMeshes[ meshHandle ];

	GLShader& shader = mShaders[ shaderHandle ];
	shader.Bind();

	//TODO: find better way for this
	//Set transform
	shader.SetUniformMat4("uModelMatrix", modelMatrix);

	mesh.Render();
}

void GLRenderer::SetUniforms( UniformList* uniformList, Shader& shader )
{
	std::vector<Uniform>& uniforms = uniformList->GetUniforms();
	for(int i = 0; i < uniforms.size(); i++)
	{
		Uniform& uniform = uniforms[i];
		uniform.mpSetFn( shader, uniform.mName, uniform.mpData );
	}
}

//private
void GLRenderer::PrintVersions()
{
	// Get info of GPU and supported OpenGL version
	GLCall( printf("renderer: %s\n", glGetString(GL_RENDERER) ) );
	GLCall( printf("OpenGL version supported %s\n", glGetString(GL_VERSION) ) );

	//If the shading language symbol is defined
#ifdef GL_SHADING_LANGUAGE_VERSION
	GLCall( std::printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION) ) );
#endif
}
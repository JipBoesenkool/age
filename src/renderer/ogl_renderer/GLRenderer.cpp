//
// Created by Jip Boesenkool on 10/06/2018.
//

#include <glad/glad.h>

#include <core/IWindow.h>

#include <renderer/ogl_renderer/GLRenderer.h>
#include <renderer/ogl_renderer/GLUtilities.h>

#include <renderer/ogl_renderer/GLShader.h>
#include <renderer/ogl_renderer/GLMesh.h>

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
	MeshResource mRes{name, layout, vbo, ibo};
	mMeshes.emplace_back( name, layout, vbo, ibo );

	//Return handle
	return index;
}

/*
void GLRenderer::InitTest()
{
	// Build and compile our shader program
	shader = new GLShader("resources/shaders/glsl/basic.glsl");

	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
			//positions
			-0.5f, -0.5f,
			0.5f, -0.5f,
			0.5f, 0.5f,
			-0.5f, 0.5f
	};

	unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
	};

	va = new GLVertexArray();
	VertexBufferLayout vbl;
	vbl.Push("float", 2);
	vb = new GLVertexBuffer( vertices, 4 * 2 * sizeof( float ) );
	va->AddBuffer(*vb, vbl);
	ib = new GLIndexBuffer(indices, 6);
}

void GLRenderer::Test()
{
	// Draw our first triangle
	//shader->Bind();
	//shader->SetUniformVec4( "uColor", 0.2f, 0.3f, 0.8f, 1.0f );
	//va->Bind();
	//GLCall( glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, 0) );
	//va->Unbind();
	mesh->Render( *shader );
}
 */

void GLRenderer::Clear() {
	// Clear the colorbuffer
	GLCall( glClearColor(0.2f, 0.3f, 0.3f, 1.0f) );
	GLCall( glClear(GL_COLOR_BUFFER_BIT) );
}

void GLRenderer::Render( ShaderHandle shader, MeshHandle mesh )
{
	GLMesh& m = mMeshes[ mesh ];
	GLShader& s = mShaders[shader];
	m.Render(s);
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

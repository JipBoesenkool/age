//
// Created by Jip Boesenkool on 10/06/2018.
//
#include <glad/glad.h>
#include <renderer/ogl_renderer/GLUtilities.h>

#include <renderer/ogl_renderer/GLRenderer.h>
#include <glfw/GLFWindow.h>
#include <pattern/event/EventManager.h>

EventManager* pEvtMgr;
GLFWindow* pWindow;
GLRenderer* pGLRenderer;

ShaderHandle shaderId;
MeshHandle meshId;

void InitScene()
{
	// Build and compile our shader program
	shaderId = pGLRenderer->CreateShader("basic", "../../resources/shaders/glsl/basic.glsl");

	//Create mesh object
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

	VertexBufferLayout vbl;
	vbl.Push("float", 2);
	VertexBufferObject vbo{vertices, 4 * 2 * sizeof( float )};
	IndexBufferObject ibo{indices, 6};

	meshId = pGLRenderer->CreateMesh("quad", vbl, vbo, ibo);
}

void OGLTest()
{
	pEvtMgr 	= new EventManager(true);
	pWindow 	= new GLFWindow(800, 600, "OpenGL Test");
	pGLRenderer	= new GLRenderer();

	InitScene();

	{
		while( !pWindow->IsClosed()) {
			//Input
			pEvtMgr->Update();

			//Render
			pGLRenderer->Clear();
			pGLRenderer->Render(shaderId, meshId);

			pWindow->SwapBuffers();
		}
	}

	pWindow->DestroyWindow();
};

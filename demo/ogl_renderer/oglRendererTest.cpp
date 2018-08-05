//
// Created by Jip Boesenkool on 10/06/2018.
//
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include "oglRendererTest.h"

void oglRendererTest::InitQuad()
{
	// Build and compile our shader program
	quad.mShaderHandle = pGLRenderer->CreateShader("basic", "../../resources/shaders/glsl/basic.glsl");

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

	quad.mQuadHandle = pGLRenderer->CreateMesh("quad", vbl, vbo, ibo);

	quad.mUniformList.Push( "uColor", new glm::vec4(1.0f,0.0f,0.0f,1.0f) );
	quad.mUniformList.Push( "uPosition", new glm::vec3(1.0f,1.0f,1.0f) );
}

void oglRendererTest::RenderQuad()
{
	pGLRenderer->Render(quad.mShaderHandle, quad.mQuadHandle, &quad.mUniformList);
}

void oglRendererTest::OGLTest()
{
	pEvtMgr 	= new EventManager(true);
	pWindow 	= new GLFWindow(800, 600, (char *)"OpenGL Test");
	pGLRenderer	= new GLRenderer();

	InitQuad();

	{
		while( !pWindow->IsClosed()) {
			//Input
			pEvtMgr->Update();

			//Render
			pGLRenderer->Clear();
			RenderQuad();

			pWindow->SwapBuffers();
		}
	}

	pWindow->DestroyWindow();
};

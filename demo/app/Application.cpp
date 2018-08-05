//
// Created by Jip Boesenkool on 04/08/2018.
//

#include "Application.h"
#include <glm/vec4.hpp>

//Public:
void Application::Init()
{
	//Init engine systems
	pEvtMgr 	= new EventManager(true);
	pWindow 	= new GLFWindow(800, 600, (char *)"Test App");
	pGLRenderer	= new GLRenderer();
	pEcsManager = new ecs::EcsManager();

	//Create shaders
	pGLRenderer->CreateShader("basic", "../../resources/shaders/glsl/basic.glsl");

	//Create meshes
	CreateQuadMesh();
}

void Application::Run()
{
	//Create components
	MeshComponent meshComp;
	meshComp.mMeshHandle = pGLRenderer->GetMeshHandle( "quad" );
	meshComp.mShaderHandle = pGLRenderer->GetShaderHandle( "basic" );

	TransformComponent transformComp;
	transformComp.mPos.x = 1.0f;
	transformComp.mPos.y = 1.0f;
	transformComp.mPos.z = 1.0f;

	//Create entity
	ecs::EntityHandle entity = pEcsManager->CreateEntityByComponents( meshComp, transformComp );

	//Add systems
	UniformList uniforms;
	glm::vec4 color(1.0f,0.0f,0.0f,1.0f);
	uniforms.Push( "uColor", &color );
	uniforms.Push( "uPosition", &transformComp.mPos );

	while( !pWindow->IsClosed()) {
		//Input
		pEvtMgr->Update();

		//Render
		pGLRenderer->Clear();

		//RenderQuad
		{
			pGLRenderer->Render( meshComp.mShaderHandle, meshComp.mMeshHandle, &uniforms );
		}

		pWindow->SwapBuffers();
	}

	pWindow->DestroyWindow();
}

//Private:
void Application::CreateQuadMesh()
{
	//Create mesh object
	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
			//positions
			-0.5f, -0.5f, 1.0f,
			0.5f, -0.5f, 1.0f,
			0.5f, 0.5f, 1.0f,
			-0.5f, 0.5f, 1.0f
	};

	unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
	};

	VertexBufferLayout vbl;
	vbl.Push("float", 3);
	VertexBufferObject vbo{vertices, 4 * 3 * sizeof( float )};
	IndexBufferObject ibo{indices, 6};

	pGLRenderer->CreateMesh("quad", vbl, vbo, ibo);
}
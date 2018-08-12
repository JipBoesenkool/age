//
// Created by Jip Boesenkool on 04/08/2018.
//

#include "Application.h"
#include <glm/vec4.hpp>
#include <thread>
#include <iostream>

//Public:
void Application::Init()
{
	//Init engine systems
	pPlatform   = new Platform();
	pEvtMgr 	= new EventManager(true);
	pWindow 	= new GLFWindow(800, 600, (char *)"Test App");
	pGLRenderer	= new GLRenderer();
	pEcsManager = new ecs::EcsManager();

	//Create shaders
	pGLRenderer->CreateShader("basic", "../../resources/shaders/glsl/basic.glsl");

	TypeDatabase::Get().PrintAll();

	//Create meshes
	CreateQuadMesh();
}

void Application::Run()
{
	//Create components
	MeshComponent meshComp;
	meshComp.mMeshHandle = pGLRenderer->GetMeshHandle( "quad" );
	meshComp.mShaderHandle = pGLRenderer->GetShaderHandle( "basic" );

	TransformComponent transComp;
	transComp.mPos = glm::vec3(0.0f);

	//Create the player
	ecs::EntityHandle ePlayer;
	ControlBehaviour controlBehaviour;
	CameraBehaviour cameraBehaviour;

	//Create the player
	{
		TransformComponent transformComp;
		transformComp.mPos.x = 0.0f;
		transformComp.mPos.y = 0.0f;
		transformComp.mPos.z = 0.0f;

		ControlComponent controlComponent;
		controlComponent.mSpeed = 10.0f;
		controlComponent.mMovement = glm::vec3(1.0f,0.0f,0.0f);

		CameraComponent cameraComponent;
		cameraComponent.mCamera = &mCamera;

		ePlayer = pEcsManager->CreateEntity( meshComp, transformComp, controlComponent, cameraComponent );
	}

	ControlComponent* ePlayerControl = pEcsManager->GetComponent<ControlComponent>( ePlayer );
	controlBehaviour.controlComponent = ePlayerControl;
	controlBehaviour.OnEnable();

	CameraComponent* ePlayerCamera = pEcsManager->GetComponent<CameraComponent>( ePlayer );
	cameraBehaviour.cameraComponent = ePlayerCamera;
	cameraBehaviour.OnEnable();

	//Entities
	for(int x = -5; x <= 5; x++)
	{
		for(int y = -5; y <= 5; y++)
		{
			transComp.mPos = glm::vec3(x, y, 0.0f);
			pEcsManager->CreateEntity( transComp, meshComp );
		}
	}

	//Renderer
	ecs::SystemList renderSystems;
	RenderMeshSystem renderMeshSystem( pGLRenderer );
	renderSystems.AddSystem( renderMeshSystem );

	//game systems
	ecs::SystemList mainSystems;
	MovementSystem movementSystem;
	mainSystems.AddSystem( movementSystem );
	CameraSystem cameraSystem( pGLRenderer, &pWindow->mWidth, &pWindow->mHeight );
	mainSystems.AddSystem( cameraSystem );

	//Init shader
	UniformList uniforms;
	glm::vec4 color(1.0f,0.0f,0.0f,1.0f);
	uniforms.Push( "uColor", &color, "glm::vec3" );
	uniforms.Push( "uPosition", &transComp.mPos, "glm::vec3" );
	Shader& s = pGLRenderer->GetShader( meshComp.mShaderHandle );

	s.Bind();
	s.SetUniformVec4("uColor", color);
	s.SetUniformVec3("uPosition", transComp.mPos);
	//pGLRenderer->SetUniforms( &uniforms, s );

	//Timer
	uint32_t fps = 0;
	double lastTime = pPlatform->Time.GetElapsedTime();
	double fpsTimeCounter = 0.0;
	double updateTimer = 1.0;
	float frameTime = 1.0/60.0;

	while( !pWindow->IsClosed()) {
		//Timer
		double currentTime = pPlatform->Time.GetElapsedTime();
		double deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		fpsTimeCounter += deltaTime;
		updateTimer    += deltaTime;

		if(fpsTimeCounter >= 1.0)
		{
			double msPerFrame = 1000.0/(double)fps;
			std::cout << "fps: " << fps << ", " << msPerFrame << "ms" << "\n";
			fpsTimeCounter = 0;
			fps = 0;
		}

		bool shouldRender = false;
		while(updateTimer >= frameTime)
		{
			//Input
			pEvtMgr->Update();

			//Systems
			pEcsManager->UpdateSystems( mainSystems, frameTime );

			updateTimer -= frameTime;
			shouldRender = true;
		}

		if(shouldRender)
		{
			//Render
			pGLRenderer->Clear();

			pEcsManager->UpdateSystems( renderSystems, frameTime );
			//pGLRenderer->Render( meshComp.mShaderHandle, meshComp.mMeshHandle, &uniforms );

			pWindow->SwapBuffers();
			fps++;
		}
		else
		{
			std::this_thread::sleep_for( std::chrono::milliseconds(1) );
		}
	}

	//controlBehaviour.OnDisable();
	pWindow->DestroyWindow();
}

//Private:
void Application::CreateQuadMesh()
{
	//Create mesh object
	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
			//positions
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
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
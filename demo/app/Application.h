//
// Created by Jip Boesenkool on 04/08/2018.
//

#ifndef Application_H
#define Application_H

#include <reflection/Reflection.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <renderer/renderer/Camera.h>
#include <renderer/ogl_renderer/GLRenderer.h>
#include <core/Controls.h>
#include <glfw/GLFWindow.h>
#include <pattern/event/EventManager.h>
#include <os/Platform.h>
#include <ecs/Ecs.h>

typedef unsigned int TileInstanceHandle;
struct TileComponent : public ecs::Component<TileComponent>
{
	TileInstanceHandle mTileHandle;
};

struct CameraComponent : public ecs::Component<CameraComponent>
{
	Camera* mCamera;
};

struct MeshComponent : public ecs::Component<MeshComponent>
{
	MeshHandle mMeshHandle;
	ShaderHandle mShaderHandle;
};

struct TransformComponent : public ecs::Component<TransformComponent>
{
	glm::vec3 mPos;
};

struct ControlComponent :  public ecs::Component<ControlComponent>
{
	float 	  mSpeed;
	glm::vec3 mMovement;
};

struct ControlBehaviour
{
	ControlComponent* controlComponent;
	void OnEnable()
	{
		if(IEventManager::Get() != nullptr)
		{
			//Input
			EventListenerDelegate delegateFunc = fastdelegate::MakeDelegate( this, &ControlBehaviour::HandleKeyInput );
			IEventManager::Get()->AddListener( "KeyEvent", delegateFunc );
		}
	}
	void OnDisable()
	{
		if(IEventManager::Get() != nullptr)
		{
			// remove the delegates from the event manager
			EventListenerDelegate delegateFunc = fastdelegate::MakeDelegate(this, &ControlBehaviour::HandleKeyInput);
			IEventManager::Get()->RemoveListener("KeyEvent", delegateFunc);
		}
	}
	void HandleKeyInput( IEventPtr pEvent )
	{
		std::shared_ptr<KeyEvent> e = std::static_pointer_cast<KeyEvent>(pEvent);
		if(e->m_action == Action::PRESSED)
		{
			if(e->m_key == Key::KEY_LEFT)
			{
				controlComponent->mMovement.x = -1.0f;
			}
			else if(e->m_key == Key::KEY_RIGHT)
			{
				controlComponent->mMovement.x = 1.0f;
			}
			else if(e->m_key == Key::KEY_UP)
			{
				controlComponent->mMovement.y = 1.0f;
			}
			else if(e->m_key == Key::KEY_DOWN)
			{
				controlComponent->mMovement.y = -1.0f;
			}
		}
	}

};

struct CameraBehaviour
{
	CameraComponent* cameraComponent;
	void OnEnable()
	{
		if(IEventManager::Get() != nullptr)
		{
			//Input
			EventListenerDelegate delegateFunc = fastdelegate::MakeDelegate( this, &CameraBehaviour::HandleMouseMove );
			IEventManager::Get()->AddListener( "MouseMoveEvent", delegateFunc );

			delegateFunc = fastdelegate::MakeDelegate( this, &CameraBehaviour::HandleMouseScroll );
			IEventManager::Get()->AddListener( "MouseScrollEvent", delegateFunc );
		}
	}
	void OnDisable()
	{
		if(IEventManager::Get() != nullptr)
		{
			// remove the delegates from the event manager
			EventListenerDelegate delegateFunc = fastdelegate::MakeDelegate(this, &CameraBehaviour::HandleMouseMove);
			IEventManager::Get()->RemoveListener("MouseMoveEvent", delegateFunc);

			delegateFunc = fastdelegate::MakeDelegate( this, &CameraBehaviour::HandleMouseScroll );
			IEventManager::Get()->RemoveListener( "MouseScrollEvent", delegateFunc );
		}
	}
	void HandleMouseMove( IEventPtr pEvent )
	{
		//std::shared_ptr<MouseMoveEvent> e = std::static_pointer_cast<MouseMoveEvent>(pEvent);
		//cameraComponent->mCamera->ProcessMouseMovement( e->m_xPos, e->m_yPos );
	}

	void HandleMouseScroll( IEventPtr pEvent )
	{
		std::shared_ptr<MouseScrollEvent> e = std::static_pointer_cast<MouseScrollEvent>(pEvent);
		cameraComponent->mCamera->ProcessMouseScroll( e->m_yOffset );
	}
};

struct ColorComponent : public ecs::Component<ColorComponent>
{
	glm::vec4 mColor;
};

class ColorSystem : public ecs::System
{
public:
	ColorSystem() : ecs::System()
	{
		AddComponentType( ColorComponent::sID );
	}

	void UpdateComponents(float delta, ecs::BaseComponent** components) override
	{
		//Get the components
		ColorComponent* colorComponent = (ColorComponent*)components[0];
		colorComponent->mColor.x += 0.01f;
		if( colorComponent->mColor.x >= 1.0f ) colorComponent->mColor.x = 0.0f;
		std::cout << "color:" << colorComponent->mColor.x << ","
				  			  << colorComponent->mColor.y << ","
		            		  << colorComponent->mColor.z << "\n";
	}
};

class MovementSystem : public ecs::System
{
public:
	MovementSystem() : ecs::System()
	{
		AddComponentType( TransformComponent::sID );
		AddComponentType( ControlComponent::sID );
	}

	void UpdateComponents(float delta, ecs::BaseComponent** components) override
	{
		//Get the components
		TransformComponent* transform = (TransformComponent*)components[0];
		ControlComponent* control = (ControlComponent*)components[1];

		//Calculate new position
		glm::vec3 velocity = control->mSpeed * control->mMovement * delta;
		transform->mPos += velocity;

		//Reset movement
		control->mMovement.x = 0.0f;
		control->mMovement.y = 0.0f;
		control->mMovement.z = 0.0f;
	}
};

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

class RenderMeshSystem : public ecs::System
{
public:
	RenderMeshSystem( GLRenderer* pRenderer ) : ecs::System(), mpRenderer(pRenderer)
	{
		bufferIdentityMatrix = glm::mat4(1.0f);

		AddComponentType( TransformComponent::sID );
		AddComponentType( MeshComponent::sID );
	}

	void UpdateComponents(float delta, ecs::BaseComponent** components) override
	{
		//Get the components
		TransformComponent* transform = (TransformComponent*)components[0];
		MeshComponent* mesh = (MeshComponent*)components[1];

		bufferTransformMatrix = glm::translate( bufferIdentityMatrix, transform->mPos );
		mpRenderer->Render(mesh->mShaderHandle, mesh->mMeshHandle, bufferTransformMatrix);
	}
public:
	glm::mat4 vpMatrix;
private:
	GLRenderer* mpRenderer;
	//Buffer
	glm::mat4 bufferTransformMatrix;
	glm::mat4 bufferIdentityMatrix;
};

class CameraSystem : public ecs::System
{
public:
	CameraSystem( GLRenderer* pGLRenderer, int* width, int* height ) : ecs::System(  )
	{
		//Members
		mWidth = width;
		mHeight = height;

		//Initialize uniform buffer
		mUniformList.Push("uProject", &mProjectionMatrix, "glm::mat4");
		mUniformList.Push("uView", &mViewMatrix, "glm::mat4" );
		mMatrixBuffer.Init("Matrices", &mUniformList, pGLRenderer->GetShaders().data(), pGLRenderer->GetShaders().size() );

		//Set required components
		AddComponentType( TransformComponent::sID );
		AddComponentType( CameraComponent::sID );
	}

	void UpdateComponents(float delta, ecs::BaseComponent** components) override
	{
		//Get the components
		TransformComponent* transform = (TransformComponent*)components[0];
		CameraComponent* camera = (CameraComponent*)components[1];

		//Set new position
		camera->mCamera->SetPosition( transform->mPos );
		camera->mCamera->m_position.z += 20.0f;

		//Update matrices
		mProjectionMatrix   = glm::perspective(camera->mCamera->m_zoom, 800.0f / 600.0f, 0.1f, 1000.0f);
		mViewMatrix			= camera->mCamera->GetViewMatrix();

		mMatrixBuffer.Bind();
	}
public:
	UniformList mUniformList;
	GLUniformBuffer mMatrixBuffer;
	glm::mat4 mProjectionMatrix;
	glm::mat4 mViewMatrix;
	int* mWidth;
	int* mHeight;
};

class Application
{
//Members
private:
	Platform* pPlatform;
	EventManager* pEvtMgr;
	GLFWindow* pWindow;
	GLRenderer* pGLRenderer;
	ecs::EcsManager* pEcsManager;
	Camera mCamera;
//Functions
public:
	void Init();
	void Run();

private:
	void CreateQuadMesh();
};


#endif //Application_H

//
// Created by Jip Boesenkool on 04/08/2018.
//

#ifndef Application_H
#define Application_H

#include <glm/vec3.hpp>

#include <reflection/Reflection.h>
#include <renderer/ogl_renderer/GLRenderer.h>
#include <glfw/GLFWindow.h>
#include <pattern/event/EventManager.h>
#include <os/Platform.h>
#include <ecs/Ecs.h>

struct MeshComponent : public ecs::Component<MeshComponent>
{
	MeshHandle mMeshHandle;
	ShaderHandle mShaderHandle;
};

struct TransformComponent : public ecs::Component<TransformComponent>
{
	glm::vec3 mPos;
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
//Functions
public:
	void Init();
	void Run();

private:
	void CreateQuadMesh();
};


#endif //Application_H

//
// Created by Jip Boesenkool on 03/08/2018.
//
#ifndef AGE_OGLRENDERERTEST_H
#define AGE_OGLRENDERERTEST_H

#include <glad/glad.h>
#include <renderer/ogl_renderer/GLUtilities.h>

#include <renderer/ogl_renderer/GLRenderer.h>
#include <glfw/GLFWindow.h>
#include <pattern/event/EventManager.h>

struct Quad
{
	ShaderHandle mShaderHandle;
	MeshHandle mQuadHandle;
	UniformList mUniformList;
};

class oglRendererTest
{
private:
	EventManager* pEvtMgr;
	GLFWindow* pWindow;
	GLRenderer* pGLRenderer;
public:

	Quad quad;
	void InitQuad();
	void RenderQuad();

	void OGLTest();
};

#endif //AGE_OGLRENDERERTEST_H

#include <age.h>
#include "ecs/ecsTest.h"
#include "reflection/reflectionTest.h"
#include "ogl_renderer/oglRendererTest.h"

#include "app/Application.h"
#include <iostream>

void RunTests()
{
	ComponentTest();
	ReflectionTest();

	oglRendererTest oglRenderTest;
	oglRenderTest.OGLTest();
}

int main() {
	std::cout << "Age demo started." << "\n";
#ifdef NDEBUG
	Log("Debug mode.")
#endif

	//RunTests();

	//Run test app
	Application app;
	app.Init();
	app.Run();

	return 0;
}
#include <age.h>
#include "ecs/ecsTest.cpp"
#include "reflection/reflectionTest.cpp"
#include "ogl_renderer/oglRendererTest.cpp"
#include <iostream>

int main() {
	std::cout << "Age demo started." << "\n";
	Log("Debug mode.")

	ComponentTest();
	//ReflectionTest();

	OGLTest();

	return 0;
}
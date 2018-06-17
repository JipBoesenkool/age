//
// Created by Jip Boesenkool on 10/06/2018.
//
#include <ecs/Component.h>

struct TestComponent : public ecs::Component<TestComponent>
{
	float x;
	float y;
};

void ComponentTest()
{
	TestComponent tComp;
	tComp.x = 1.0f;
	tComp.y = 2.0f;
}

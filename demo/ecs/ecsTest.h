//
// Created by Jip Boesenkool on 03/08/2018.
//

#ifndef AGE_ECSTEST_H
#define AGE_ECSTEST_H

#include <ecs/Component.h>
#include <ecs/EcsManager.h>

struct TestComponent : public ecs::Component<TestComponent>
{
	float x;
	float y;
};

struct TestComponentTwo : public ecs::Component<TestComponent>
{
	float x;
	float y;
};

struct TestComponentThree : public ecs::Component<TestComponent>
{
	float x;
	float y;
};

void ComponentTest();

#endif //AGE_ECSTEST_H

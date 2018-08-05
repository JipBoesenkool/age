//
// Created by Jip Boesenkool on 10/06/2018.
//
#include "ecsTest.h"

void ComponentTest()
{
	//Create component
	TestComponent tComp;
	tComp.x = 1.0f;
	tComp.y = 2.0f;

	//Create component
	TestComponentTwo tCompTwo;
	tComp.x = 1.0f;
	tComp.y = 2.0f;

	//Create component
	TestComponentThree tCompThree;
	tComp.x = 1.0f;
	tComp.y = 2.0f;

	//Test create entity
	ecs::EcsManager* pEcsManager = new ecs::EcsManager();
	pEcsManager->CreateEntityByComponents(tComp, tCompTwo, tCompThree);
}

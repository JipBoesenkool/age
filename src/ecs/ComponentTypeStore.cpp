//
// Created by Jip Boesenkool on 07/06/2018.
//
#include "ecs/ComponentTypeStore.h"

namespace ecs
{
	std::vector< ComponentType > ComponentTypeStore::sComponentTypes;

	uint32_t ComponentTypeStore::RegisterComponentType( ComponentCreateFunc createFn, ComponentDeleteFunc deleteFn, size_t size)
	{
		uint32_t componentId = sComponentTypes.size();
		sComponentTypes.push_back(
				ComponentType{createFn, deleteFn, size}
		);
		return componentId;
	}

	ComponentCreateFunc ComponentTypeStore::GetTypeCreateFunction(uint32_t id)
	{
		return sComponentTypes[id].createFn;
	}
	ComponentDeleteFunc ComponentTypeStore::GetTypeDeleteFunction(uint32_t id)
	{
		return sComponentTypes[id].deleteFn;
	}
	size_t ComponentTypeStore::GetTypeSize(uint32_t id)
	{
		return sComponentTypes[id].size;
	}
	bool ComponentTypeStore::IsTypeValid(uint32_t id)
	{
		return ( id < sComponentTypes.size() );
	}
}
//
// Created by Jip Boesenkool on 07/06/2018.
//

#ifndef AGE_COMPONENTSTORE_H
#define AGE_COMPONENTSTORE_H

#include "ComponentType.h"

#include <vector>

namespace ecs
{
	class ComponentTypeStore
	{
	//Members
	private:
		static std::vector<ComponentType> sComponentTypes;
	//Functions
	public:
		static uint32_t RegisterComponentType(
				ComponentCreateFunc createFn,
				ComponentDeleteFunc deleteFn,
				size_t size);
		static ComponentCreateFunc GetTypeCreateFunction(uint32_t id);
		static ComponentDeleteFunc GetTypeDeleteFunction(uint32_t id);
		static size_t GetTypeSize(uint32_t id);
		static bool IsTypeValid(uint32_t id);
	};
}

#endif //AGE_COMPONENTSTORE_H

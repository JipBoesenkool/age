//
// Created by Jip Boesenkool on 07/06/2018.
//

#ifndef AGE_COMPONENTTYPE_H
#define AGE_COMPONENTTYPE_H

#include <vector>

namespace ecs
{
	struct BaseComponent;
	typedef void* EntityHandle;
	typedef uint32_t (*ComponentCreateFunc)(std::vector<uint8_t>& memory, EntityHandle entity, BaseComponent* pComp);
	typedef void (*ComponentDeleteFunc)(BaseComponent* pComp);
	#define NULL_ENTITY_HANDLE nullptr

	struct ComponentType
	{
		ComponentCreateFunc createFn;
		ComponentDeleteFunc deleteFn;
		size_t size;
	};
}

#endif //AGE_COMPONENTTYPE_H

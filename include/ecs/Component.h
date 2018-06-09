//
// Created by Jip Boesenkool on 05/06/2018.
//
#ifndef AGE_COMPONENT_H
#define AGE_COMPONENT_H

#include <vector>

#include "ComponentType.h"
#include "ComponentTypeStore.h"

namespace ecs
{
//Base component has entity handle
	struct BaseComponent
	{
		EntityHandle mEntity = NULL_ENTITY_HANDLE;
	};

//Template component for reflection info
//TODO: replace with reflection system?
	template<typename T>
	struct Component : public BaseComponent
	{
		static const ComponentCreateFunc 	sCreateFunc;
		static const ComponentDeleteFunc 	sDeleteFunc;
		static const uint32_t 				sID;
		static const size_t 				sSize;
	};

//Create function
	template<typename Component>
	uint32_t CreateComponent(std::vector<uint8_t>& memory, EntityHandle entity, ecs::BaseComponent* pComp)
	{
		uint32_t index = memory.size();
		memory.resize(index+Component::sSize);
		Component* pComponent = new(&memory[index])Component(*(Component*)pComp);
		pComponent->mEntity = entity;
		return index;
	}

//Delete function
	template<typename Component>
	void DeleteComponent(ecs::BaseComponent* pComp)
	{
		Component* pComponent = (Component*)pComp;
		pComponent->~Component();
	}

//Reflection functions
	template<typename T>
	const uint32_t Component<T>::sID(
		ComponentTypeStore::RegisterComponentType( CreateComponent<T>, DeleteComponent<T>, sizeof(T) )
	);
	template<typename T>
	const size_t Component<T>::sSize( sizeof( T ) );
	template<typename T>
	const ComponentCreateFunc Component<T>::sCreateFunc( CreateComponent<T> );
	template<typename T>
	const ComponentDeleteFunc Component<T>::sDeleteFunc( DeleteComponent<T> );
}

#endif //AGE_COMPONENT_H

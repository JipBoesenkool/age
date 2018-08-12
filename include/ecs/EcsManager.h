//
// Created by Jip Boesenkool on 05/06/2018.
//

#ifndef AGE_ECSMANAGER_H
#define AGE_ECSMANAGER_H

#include "Component.h"
#include "ComponentTypeStore.h"
#include "Entity.h"
#include "SystemList.h"
#include "System.h"

#include <map>
#include <iostream>

namespace ecs {
	class EcsManager
	{
		//Members
	private:
		std::map< uint32_t, std::vector< uint8_t > > mComponents;
		std::vector< Entity* > mEntities;
		//Functions
	public:
		EcsManager();
		~EcsManager();

		//Entity methods
		EntityHandle CreateEntity( BaseComponent** pComponents, const uint32_t *pComponentTypes, size_t numComponents );
		void RemoveEntity( EntityHandle handle );
		template <class... Component>
		EntityHandle CreateEntityByComponents(Component... componentArgs);

		template<class A, class B>
		EntityHandle CreateEntity(A& c1, B& c2)
		{
			BaseComponent* components[] = { &c1, &c2 };
			uint32_t componentIds[] = {A::sID, B::sID};
			return CreateEntity(components, componentIds, 2);
		};

		template<class A, class B, class C>
		EntityHandle CreateEntity(A& c1, B& c2, C& c3)
		{
			BaseComponent* components[] = { &c1, &c2, &c3 };
			uint32_t componentIds[] = {A::sID, B::sID, C::sID};
			return CreateEntity(components, componentIds, 3);
		};

		template<class A, class B, class C, class D>
		EntityHandle CreateEntity(A& c1, B& c2, C& c3, D& c4)
		{
			BaseComponent* components[] = { &c1, &c2, &c3, &c4 };
			uint32_t componentIds[] = {A::sID, B::sID, C::sID, D::sID};
			return CreateEntity(components, componentIds, 4);
		};

		//Component methods
		template< class ComponentType > void AddComponent( EntityHandle entity, ComponentType *pComponent );
		template< class ComponentType > void RemoveComponent( EntityHandle entity );
		template< class ComponentType > ComponentType* GetComponent( EntityHandle entity );

		//System methods
		void UpdateSystems( ecs::SystemList& systems, float delta );

	private:
		void UpdateSystemWithMultipleComponents(
			uint32_t index, ecs::SystemList& systems,
			float delta, const std::vector<uint32_t>& componentTypes);

		//Internal functions
		BaseComponent* GetComponentInternal(std::vector<CompontentPair>& components, std::vector<uint8_t>& array, uint32_t componentId);
		void AddComponentInternal(EntityHandle handle, std::vector<CompontentPair>& components, uint32_t componentId, BaseComponent* pComponent);
		void RemoveComponentInternal(EntityHandle handle, uint32_t componentId);
		void DeleteComponent(uint32_t componentId, uint32_t index);

		//Utility functions
		Entity* EntityHandleToRawType( EntityHandle handle );
		std::vector< CompontentPair >& EntityHandleToComponents( EntityHandle handle );
		uint32_t EntityHandleToEntityIndex( EntityHandle handle );
		uint32_t FindLeastCommonComponent(const std::vector<uint32_t>& componentTypes, const std::vector<uint32_t>& componentFlags);

		template <class HEAD>
		void AddToVector( std::vector< BaseComponent* >* pComponents, std::vector< uint32_t >* pComponentIDs, HEAD head);
		template <class HEAD, class... TAIL>
		void AddToVector( std::vector< BaseComponent* >* pComponents, std::vector< uint32_t >* pComponentIDs, HEAD head, TAIL... tail);
	};

	template <class... Component>
	EntityHandle EcsManager::CreateEntityByComponents(Component... componentArgs)
	{
		std::vector< BaseComponent* > components;
		std::vector< uint32_t > componentIDs;
		AddToVector( &components, &componentIDs, componentArgs... );

		return CreateEntity( &components[0], &componentIDs[0], components.size() );
	}

	//Component methods
	template< class ComponentType >
	void EcsManager::AddComponent( EntityHandle entity, ComponentType* pComponent ) {
		AddComponentInternal( entity, EntityHandleToComponents( entity ), ComponentType::sID, pComponent );
	}

	template< class ComponentType >
	void EcsManager::RemoveComponent( EntityHandle entity ) {
		RemoveComponentInternal( entity, ComponentType::sID );
	}

	template< class ComponentType >
	ComponentType* EcsManager::GetComponent( EntityHandle entity ){
		return (ComponentType*)GetComponentInternal( EntityHandleToComponents( entity ), mComponents[ComponentType::sID], ComponentType::sID );
	}

	template <class HEAD>
	void EcsManager::AddToVector(
			std::vector< BaseComponent* >* pComponents,
			std::vector< uint32_t >* pComponentIDs,
			HEAD head)
	{
		pComponents->push_back(&head);
		pComponentIDs->push_back( HEAD::sID );
	}

	template <class HEAD, class... TAIL>
	void EcsManager::AddToVector(
			std::vector< BaseComponent* >* pComponents,
			std::vector< uint32_t >* pComponentIDs,
			HEAD head,
			TAIL... tail)
	{
		pComponents->push_back(&head);
		pComponentIDs->push_back( HEAD::sID );

		AddToVector(pComponents, pComponentIDs, tail...);
	}

}

#endif //AGE_ECSMANAGER_H

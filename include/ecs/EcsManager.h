//
// Created by Jip Boesenkool on 05/06/2018.
//

#ifndef AGE_ECSMANAGER_H
#define AGE_ECSMANAGER_H

#include "Component.h"
#include "ComponentTypeStore.h"
#include "Entity.h"
#include "System.h"

#include <map>

namespace ecs {
	class EcsManager
	{
		//Members
	private:
		std::vector< BaseSystem * > mSystems;
		std::map< uint32_t, std::vector< uint8_t > > mComponents;
		std::vector< Entity* > mEntities;
		//Functions
	public:
		EcsManager();
		~EcsManager();

		//Entity methods
		EntityHandle CreateEntity( BaseComponent *pComponents, const uint32_t *pComponentTypes, size_t numComponents );
		void RemoveEntity( EntityHandle handle );

		//Component methods
		template< class ComponentType > void AddComponent( EntityHandle entity, ComponentType *pComponent );
		template< class ComponentType > void RemoveComponent( EntityHandle entity );
		template< class ComponentType > ComponentType* GetCompontent( EntityHandle entity );

		//System methods
		void AddSystem( BaseSystem &system );
		void RemoveSystem( BaseSystem &system );
		void UpdateSystems( float delta );

	private:
		void UpdateSystemWithMultipleComponents(
			uint32_t index, float delta, const std::vector<uint32_t>& componentTypes,
			std::vector<BaseComponent*>& componentParam, std::vector<std::vector<uint8_t>*>& componentVectors);

		//Internal functions
		BaseComponent* GetComponentInternal(std::vector<CompontentPair>& components, std::vector<uint8_t>& array, uint32_t componentId);
		void AddComponentInternal(EntityHandle handle, std::vector<CompontentPair>& components, uint32_t componentId, BaseComponent* pComponent);
		void RemoveComponentInternal(EntityHandle handle, uint32_t componentId);
		void DeleteComponent(uint32_t componentId, uint32_t index);

		//Utility functions
		Entity* EntityHandleToRawType( EntityHandle handle );
		std::vector< CompontentPair >& EntityHandleToComponents( EntityHandle handle );
		uint32_t EntityHandleToEntityIndex( EntityHandle handle );
		uint32_t FindLeastCommonComponent(const std::vector<uint32_t>& componentTypes);
	};

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
	ComponentType* EcsManager::GetCompontent( EntityHandle entity ){
		GetComponentInternal( EntityHandleToComponents( entity ), mComponents[ComponentType::sID], ComponentType::sID );
	}

}

#endif //AGE_ECSMANAGER_H

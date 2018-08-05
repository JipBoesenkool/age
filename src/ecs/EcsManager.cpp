//
// Created by Jip Boesenkool on 07/06/2018.
//

#include "ecs/EcsManager.h"
#include "memory/Memory.h"

#include <algorithm>
#include <iostream>

namespace ecs
{
//Public:
	EcsManager::EcsManager()
	{
		//Empty constructor
	}
	EcsManager::~EcsManager()
	{
		//Delete all the components
		for(auto it = mComponents.begin(); it != mComponents.end(); ++it) {
			size_t typeSize = ComponentTypeStore::GetTypeSize( it->first );
			ComponentDeleteFunc DeleteFn = ComponentTypeStore::GetTypeDeleteFunction(it->first);
			for(uint32_t i = 0; i < it->second.size(); i += typeSize) {
				DeleteFn( (ecs::BaseComponent*)&it->second[i] );
			}
		}

		//Delete all the entities
		for(uint32_t i = 0; i < mEntities.size(); i++) {
			delete mEntities[i];
		}
	}

	//Entity methods
	EntityHandle EcsManager::CreateEntity( BaseComponent** pComponents, const uint32_t* pComponentTypes, size_t numComponents)
	{
		Entity* newEntity = new Entity;
		EntityHandle handle = (EntityHandle)newEntity;
		for(uint32_t i = 0; i < numComponents; i++) {
			if( !ComponentTypeStore::IsTypeValid( pComponentTypes[i] ) ) {
				//DEBUG_LOG("ECS", LOG_ERROR, "'%u' is not a valid component type.", componentIDs[i]);
				delete newEntity;
				return NULL_ENTITY_HANDLE;
			}

			AddComponentInternal(handle, newEntity->mComponents, pComponentTypes[i], pComponents[i]);
		}

		newEntity->mVectorIndex = mEntities.size();
		mEntities.push_back(newEntity);
		return handle;
	}
	void EcsManager::RemoveEntity( EntityHandle handle )
	{
		std::vector<CompontentPair>& components = EntityHandleToComponents( handle );
		for(uint32_t i = 0; i < components.size(); i++) {
			DeleteComponent(components[i].mTypeId, components[i].mIndex);
		}

		//TODO: Move to utility aka swap
		uint32_t destIndex = EntityHandleToEntityIndex(handle);
		uint32_t srcIndex = mEntities.size() - 1;
		delete mEntities[destIndex];
		mEntities[destIndex] = mEntities[srcIndex];
		mEntities.pop_back();
	}


	void EcsManager::UpdateSystems( ecs::SystemList& systems, float delta )
	{
		std::vector<BaseComponent*> componentParam;
		std::vector<std::vector<uint8_t >*> componentArrays;
		for(uint32_t i = 0; i < systems.Size(); i++) {
			const std::vector<uint32_t >& componentTypes = systems[i]->GetComponentTypes();
			if(componentTypes.size() == 1) {
				size_t typeSize = ComponentTypeStore::GetTypeSize( componentTypes[0] );
				std::vector<uint8_t>& array = mComponents[ componentTypes[0] ];
				for(uint32_t j = 0; j < array.size(); j += typeSize) {
					BaseComponent* component = (BaseComponent*)&array[j];
					systems[i]->UpdateComponents(delta, &component);
				}
			} else {
				UpdateSystemWithMultipleComponents(i, systems, delta, componentTypes, componentParam, componentArrays);
			}
		}
	}

//Private:
	void EcsManager::UpdateSystemWithMultipleComponents( uint32_t index, ecs::SystemList& systems, float delta, const std::vector<uint32_t>& componentTypes, std::vector<BaseComponent*>& componentParam, std::vector<std::vector<uint8_t>*>& componentArrays)
	{
		const std::vector< uint32_t >& componentFlags = systems[index]->GetComponentFlags();

		componentParam.resize(std::max(componentParam.size(), componentTypes.size()));
		componentArrays.resize(std::max(componentArrays.size(), componentTypes.size()));

		for(uint32_t i = 0; i < componentTypes.size(); i++) {
			componentArrays[i] = &mComponents[ componentTypes[i] ];
		}
		uint32_t minSizeIndex = FindLeastCommonComponent( componentTypes, componentFlags );

		size_t typeSize = ComponentTypeStore::GetTypeSize( componentTypes[minSizeIndex] );
		std::vector<uint8_t>& array = *componentArrays[minSizeIndex];
		for(uint32_t i = 0; i < array.size(); i += typeSize) {
			componentParam[minSizeIndex] = (BaseComponent*)&array[i];
			std::vector<CompontentPair>& entityComponents = EntityHandleToComponents( componentParam[minSizeIndex]->mEntity );

			bool isValid = true;
			for(uint32_t j = 0; j < componentTypes.size(); j++) {
				if(j == minSizeIndex) {
					continue;
				}

				componentParam[j] = GetComponentInternal(entityComponents, *componentArrays[j], componentTypes[j]);
				if(componentParam[j] == nullptr && (componentFlags[j] & BaseSystem::FLAG_OPTIONAL) == 0 ) {
					isValid = false;
					break;
				}
			}

			if(isValid) {
				systems[index]->UpdateComponents(delta, &componentParam[0]);
			}
		}
	}

	//Internal functions
	BaseComponent* EcsManager::GetComponentInternal(std::vector<CompontentPair>& components, std::vector<uint8_t>& array, uint32_t componentId)
	{
		for(uint32_t i = 0; i < components.size(); i++) {
			if(componentId == components[i].mTypeId) {
				return (BaseComponent*)&array[components[i].mIndex];
			}
		}
		return nullptr;
	}
	void EcsManager::AddComponentInternal(EntityHandle handle, std::vector<CompontentPair>& entityComponents, uint32_t componentId, BaseComponent* pComponent)
	{
		ComponentCreateFunc createfn = ComponentTypeStore::GetTypeCreateFunction(componentId);
		CompontentPair cp;
		cp.mTypeId = componentId;
		cp.mIndex = createfn( mComponents[componentId], handle, pComponent );
		entityComponents.push_back( cp );
	}
	void EcsManager::RemoveComponentInternal(EntityHandle handle, uint32_t componentId)
	{
		std::vector<CompontentPair>& entityComponents = EntityHandleToComponents(handle);
		for(uint32_t i = 0; i < entityComponents.size(); i++) {
			if(componentId == entityComponents[i].mTypeId) {
				DeleteComponent(entityComponents[i].mTypeId, entityComponents[i].mIndex);
				uint32_t srcIndex = entityComponents.size()-1;
				uint32_t destIndex = i;
				entityComponents[destIndex] = entityComponents[srcIndex];
				entityComponents.pop_back();
			}
		}
	}
	void EcsManager::DeleteComponent(uint32_t componentId, uint32_t index)
	{
		//Get component type container
		//TODO: Create component collection?
		std::vector<uint8_t >& compTypeVector = mComponents[componentId];
		//Get meta data
		ComponentDeleteFunc deleteFn = ComponentTypeStore::GetTypeDeleteFunction( componentId );
		size_t typeSize = ComponentTypeStore::GetTypeSize(componentId);

		//prepare swap & delete component
		uint32_t srcIndex = compTypeVector.size() - typeSize;
		BaseComponent* destComponent = (BaseComponent*)&compTypeVector[index];
		BaseComponent* srcComponent = (BaseComponent*)&compTypeVector[srcIndex];
		deleteFn(destComponent);

		//shrink array
		if(index == srcIndex) {
			compTypeVector.resize(srcIndex);
			return;
		}
		//Swap
		Memory::memcpy(destComponent, srcComponent, typeSize);

		//Get component of entity
		std::vector<CompontentPair> srcComponents = EntityHandleToComponents(srcComponent->mEntity);
		for(uint32_t i = 0; i < srcComponents.size(); i++) {
			if(componentId == srcComponents[i].mTypeId && srcIndex == srcComponents[i].mIndex) {
				srcComponents[i].mIndex = index;
				break;
			}
		}

		compTypeVector.resize(srcIndex);
	}

	//Utility functions
	Entity* EcsManager::EntityHandleToRawType( EntityHandle handle )
	{
		return (ecs::Entity*)handle;
	}

	std::vector<CompontentPair>& EcsManager::EntityHandleToComponents( EntityHandle handle )
	{
		return EntityHandleToRawType(handle)->mComponents;
	}

	uint32_t EcsManager::EntityHandleToEntityIndex( EntityHandle handle )
	{
		return EntityHandleToRawType(handle)->mVectorIndex;
	}

	uint32_t EcsManager::FindLeastCommonComponent(const std::vector<uint32_t>& componentTypes, const std::vector<uint32_t>& componentFlags)
	{
		uint32_t minSize = (uint32_t)-1;
		uint32_t minIndex = (uint32_t)-1;
		for(uint32_t i = 0; i < componentTypes.size(); i++) {
			if( (componentFlags[i] & BaseSystem::FLAG_OPTIONAL) != 0 )
			{
				continue;
			}

			size_t typeSize = ComponentTypeStore::GetTypeSize( componentTypes[i] );
			uint32_t size = mComponents[ componentTypes[i] ].size()/typeSize;
			if(size <= minSize) {
				minSize = size;
				minIndex = i;
			}
		}

		if(minIndex == (uint32_t)-1)
		{
			std::cerr << "EcsManager::FindLeastCommonComponent: All component are optional. \n";
		}
		return minIndex;
	}
}


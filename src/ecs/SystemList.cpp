//
// Created by Jip Boesenkool on 03/08/2018.
//
#include "ecs/SystemList.h"

//System methods
bool ecs::SystemList::AddSystem(BaseSystem& system)
{
	if( !system.IsValid() )
	{
		return false;
	}

	mSystems.push_back(&system);
	return true;
}
void ecs::SystemList::RemoveSystem(BaseSystem& system)
{
	for(uint32_t i = 0; i < mSystems.size(); i++) {
		if(&system == mSystems[i]) {
			mSystems.erase(mSystems.begin() + i);
		}
	}
}

bool ecs::SystemList::IsValid()
{
	for( uint32_t i = 0; mComponentFlags.size() < i ; i++ ) {
		if( (mComponentFlags[i] & BaseSystem::FLAG_OPTIONAL) == 0 )
		{
			return true;
		}
	}
	return false;
}



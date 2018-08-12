//
// Created by Jip Boesenkool on 03/08/2018.
//
#include "ecs/SystemList.h"

namespace ecs
{
	//System methods
	bool SystemList::AddSystem(System& system)
	{
		if( !system.IsValid() )
		{
			return false;
		}

		mSystems.push_back(&system);
		return true;
	}
	void SystemList::RemoveSystem(System& system)
	{
		for(uint32_t i = 0; i < mSystems.size(); i++) {
			if(&system == mSystems[i]) {
				mSystems.erase(mSystems.begin() + i);
			}
		}
	}
}

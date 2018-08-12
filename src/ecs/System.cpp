//
// Created by Jip Boesenkool on 07/06/2018.
//
#include "ecs/System.h"

namespace ecs
{
	bool System::IsValid()
	{
		for( uint32_t i = 0; i < mComponentFlags.size() ; i++ ) {
			if( (mComponentFlags[i] & System::FLAG_OPTIONAL) == 0 )
			{
				return true;
			}
		}
		return false;
	}
}

//
// Created by Jip Boesenkool on 03/08/2018.
//
#ifndef AGE_SYSTEMLIST_H
#define AGE_SYSTEMLIST_H
#include "System.h"

namespace ecs
{
	class SystemList
	{
	public:
		bool AddSystem( BaseSystem &system );
		void RemoveSystem( BaseSystem &system );

		bool IsValid();
		inline size_t Size()
		{
			return mSystems.size();
		}
		inline ecs::BaseSystem* operator[](uint32_t index)
		{
			return mSystems[index];
		}
	private:
		std::vector< BaseSystem* > mSystems;
	};
}

#endif //AGE_SYSTEMLIST_H

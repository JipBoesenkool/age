#pragma once

#include <vector>
#include <assert.h>

#include "Component.h"

namespace ecs
{
	class System
	{
	public:
		enum
		{
			FLAG_OPTIONAL = 1,
		};

		System()
		{
			//Empty constructor
		}

		virtual void UpdateComponents(float delta, BaseComponent** components)
		{
			// to be overriden
			assert(false);
		}

		const std::vector<uint32_t>& GetComponentTypes()
		{
			return mComponentTypes;
		}

		const std::vector<uint32_t>& GetComponentFlags()
		{
			return mComponentFlags;
		}
		bool IsValid();

	protected:
		void AddComponentType(uint32_t componentType, uint32_t componentFlag = 0)
		{
			mComponentTypes.push_back(componentType);
			mComponentFlags.push_back(componentFlag);
		}

	private:
		std::vector<uint32_t> mComponentTypes;
		std::vector<uint32_t> mComponentFlags;
	};
}

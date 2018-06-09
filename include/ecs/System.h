#pragma once

#include <vector>

#include "Component.h"

namespace ecs
{
	class BaseSystem
	{
	public:
		BaseSystem(const std::vector<uint32_t>& componentTypesIn) : mComponentTypes(componentTypesIn)
		{
			//Empty constructor
		}

		virtual void UpdateComponents(float delta, BaseComponent** components)
		{
			//Empty fn?
		}

		const std::vector<uint32_t>& getComponentTypes()
		{
			return mComponentTypes;
		}
	private:
		std::vector<uint32_t> mComponentTypes;
	};
}

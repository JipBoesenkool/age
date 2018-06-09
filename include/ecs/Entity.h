//
// Created by Jip Boesenkool on 07/06/2018.
//

#ifndef AGE_ENTITY_H
#define AGE_ENTITY_H

namespace ecs
{
	struct CompontentPair
	{
		uint32_t mTypeId; 							//ComponentType
		uint32_t mIndex;  							//Index in the vector
	};

	struct Entity
	{
		uint32_t mVectorIndex;						//Index in the vector
		std::vector<CompontentPair> mComponents;	//All components this entity has
	};

}

#endif //AGE_ENTITY_H

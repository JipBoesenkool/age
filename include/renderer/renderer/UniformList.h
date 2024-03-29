//
// Created by Jip Boesenkool on 05/08/2018.
//
#ifndef AGE_UNIFORMLIST_H
#define AGE_UNIFORMLIST_H

#include <vector>
#include <string>
#include <reflection/Reflection.h>

#include "Uniform.h"

class UniformImpl
{
public:
	virtual UniformSetFn GetCallback( std::string typeName )
	{
		assert(false);
		return nullptr;
	};
};

class UniformList
{
//Members
public:
	static UniformImpl* spUniformImpl;
protected:
	std::vector<Uniform> mUniforms;
//Functions
public:
	UniformList() {
		//Empty constructor
	};
	template <typename T>
	void Push(std::string name, T* pData )
	{
		//Get function pointer
		TypeDesc& typeDesc = TypeDatabase::Get().GetType<T>();
		std::string typeName = typeDesc.mName;
		Push(name, pData, typeName);
	};
	template <typename T>
	void Push(std::string name, T* pData, std::string typeName )
	{
		//Get function pointer
		UniformSetFn setFn 	= spUniformImpl->GetCallback( typeName );

		//Convert data to void pointer
		std::string typeNameCopy( typeName );
		typeNameCopy.pop_back();

		void* pVoidData 	= nullptr;
		if( typeNameCopy.compare("glm::vec") == 0 )
		{
			pVoidData = (void*)&pData[0];
		}
		else if( typeNameCopy.compare("glm::mat") == 0 )
		{
			pVoidData = (void*)&pData[0][0];
		}
		else
		{
			pVoidData = (void*)pData;
		}

		//Add to vector
		mUniforms.push_back( Uniform{name, typeName, pVoidData, setFn} );
	};
	//Getters
	inline std::vector<Uniform>& GetUniforms() { return mUniforms; };
};

#endif //AGE_UNIFORMLIST_H

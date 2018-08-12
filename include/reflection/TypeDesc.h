//
// Created by Jip Boesenkool on 11/05/2018.
//

#ifndef REFLECTION_TYPEDESC_H
#define REFLECTION_TYPEDESC_H

#include <vector>
#include <string>

template <typename TYPE>
struct GetTypeName {
	static std::string value;
};

class MemberDesc;
class TypeDesc
{
public:
	// Scoped C++ name of the type
	std::string mName;

	// Result of sizeof(type) operation
	size_t mSize;

	// List of members
	std::vector<MemberDesc> mMembers; // Contains all the members described by the type.

	TypeDesc* mParent = nullptr;

	template<typename T>
	static TypeDesc Create(std::string name)
	{
		TypeDesc td;
		td.mName = std::string(name);
		td.mSize = sizeof(T);
		return td;
	}

	template <typename T>
	void Inherits()
	{
		mParent = GetType( GetTypeName<T>::value );
	}

	//Memory allocation
	//TODO: allocator
	//TODO: should this be in here?
	void* New( void ) const;
	void Delete( void *data ) const;

	void Copy( void *dest, const void *src ) const;
	void* NewCopy( const void *src ) const;

	TypeDesc* GetType( std::string name );
};

//#include "../../src/reflection/TypeDesc.inl"

#endif //REFLECTION_TYPEDESC_H

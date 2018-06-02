//
// Created by Jip Boesenkool on 11/05/2018.
//

#ifndef REFLECTION_TYPEDATABASE_H
#define REFLECTION_TYPEDATABASE_H

#include "../../include/reflection/TypeDesc.h"
#include "MemberDesc.h"

#include <iostream>
#include <map>
#include <cassert>

//Avoid linkage to Reflection.h
#define DefineTypeInternal(type) \
	template <> struct GetTypeName<type> { static const char* value; }; \
	const char* GetTypeName<type>::value = #type;

// A big registry of all types in the game with methods to manipulate them
class TypeDatabase
{
public:
	typedef std::map<const char*, TypeDesc> TypeMap;

	TypeDatabase();

	template<typename T>
	TypeDesc& CreateType( )
	{
		//Already created
		const char* name = GetTypeName<T>::value;
		TypeMap::iterator itr = mTypes.find( name );
		if(itr != std::end(mTypes)) {
			return itr->second;
		}

		//Register new
		TypeDesc& retval = mTypes[ name ];
		retval = TypeDesc::Create<T>( name );

		return retval;
	}

	template<typename T>
	TypeDatabase& CreateType( const char* name )
	{
		//Already created
		TypeMap::iterator itr = mTypes.find( name );
		if(itr != std::end(mTypes)) {
			return *this;
		}

		//Register new
		TypeDesc& retval = mTypes[ name ];
		retval = TypeDesc::Create<T>( name );

		return *this;
	}

	template <typename T>
	TypeDesc& GetType()
	{
		return GetType( GetTypeName<T>::value );
	}

	TypeDesc& GetType( const char* name) {
		//Not created
		if( mTypes.find(name) == mTypes.end() ) {
			assert(false);
		}

		return mTypes[name];
	}

	template <typename T>
	TypeDesc* GetTypePtr( ) {
		return GetTypePtr( GetTypeName<T>::value );
	}

	TypeDesc* GetTypePtr( const char* name ) {
		//Not created
		if( mTypes.find(name) == mTypes.end() ) {
			assert(false);
		}

		return &mTypes[name];
	}

	// Registers a new data member to the struct.
	template<typename Struct, typename Member>
	TypeDatabase& AddMember(const char* const name, Member Struct::*memberPtr)
	{
		TypeDesc& td = GetType<Struct>();
		MemberDesc md = MemberDesc::Create(name, memberPtr);
		td.mMembers.push_back(md);
		return *this;
	}

	static TypeDatabase& Get();
	void PrintAll();
private:
	TypeMap mTypes;
};

#endif //REFLECTION_TYPEDATABASE_H

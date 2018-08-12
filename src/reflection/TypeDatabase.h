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
#include <string>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/Matrix.hpp>

//Avoid linkage to Reflection.h
#define DefineTypeInternal(type) \
	template <> struct GetTypeName<type> { static const char* value; }; \
	const char* GetTypeName<type>::value = #type;

// A big registry of all types in the game with methods to manipulate them
class TypeDatabase
{
//Members
public:
	typedef std::map<std::string, TypeDesc> TypeMap;
	TypeMap mTypes;
public:


	TypeDatabase();

	template<typename T>
	TypeDesc& CreateType( )
	{
		//Already created
		std::string name( GetTypeName<T>::value );
		auto itr = mTypes.find( name );
		if( itr != mTypes.end() ) {
			return itr->second;
		}

		//Register new
		TypeDesc& retval = mTypes[ name ];
		retval = TypeDesc::Create<T>( name );

		return retval;
	}

	template<typename T>
	TypeDatabase& CreateType( const std::string& name )
	{
		//Already created
		TypeMap::iterator itr = mTypes.find( name );
		if( itr != mTypes.end() ) {
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

	TypeDesc& GetType( const std::string& name ) {
		//Not created
		if( mTypes.find( name ) == mTypes.end() ) {
			std::cout << "Error::GetType: " << name << " not found.\n";
			assert(false);
		}

		//Print( mTypes[name] );
		return mTypes[name];
	}

	template <typename T>
	TypeDesc* GetTypePtr( ) {
		return GetTypePtr( GetTypeName<T>::value );
	}

	TypeDesc* GetTypePtr( std::string name ) {
		//Not created
		if( mTypes.find(name) == mTypes.end() ) {
			assert(false);
		}

		return &mTypes[name];
	}

	// Registers a new data member to the struct.
	template<typename Struct, typename Member>
	TypeDatabase& AddMember(std::string name, Member Struct::*memberPtr)
	{
		TypeDesc& td = GetType<Struct>();
		MemberDesc md = MemberDesc::Create(name, memberPtr);
		td.mMembers.push_back(md);
		return *this;
	}

	static TypeDatabase& Get();
	void PrintAll();
private:
	void Print(TypeDesc& typeDesc);
};

#endif //REFLECTION_TYPEDATABASE_H

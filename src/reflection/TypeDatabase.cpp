//
// Created by Jip Boesenkool on 11/05/2018.
//
#include "TypeDatabase.h"
#include <reflection/VarBag.h>

static TypeDatabase gTypeDatabase;

//Define base types
DefineTypeInternal( std::string );
DefineTypeInternal( bool );
DefineTypeInternal( char );
DefineTypeInternal( int );
DefineTypeInternal( float );
DefineTypeInternal( double );
DefineTypeInternal( VarBag );

//GLM
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
DefineTypeInternal( glm::vec2 );
DefineTypeInternal( glm::vec3 );
DefineTypeInternal( glm::vec4 );
DefineTypeInternal( glm::mat2 );
DefineTypeInternal( glm::mat3 );
DefineTypeInternal( glm::mat4 );

TypeDatabase::TypeDatabase()
{
	//c++
	CreateType<std::string>();
	CreateType<bool>();
	CreateType<char>();
	CreateType<int>();
	CreateType<float>();
	CreateType<double>();

	//engine
	CreateType<VarBag>();

	//glm
	CreateType<glm::vec2>();
	CreateType<glm::vec3>();
	CreateType<glm::vec4>();
	CreateType<glm::mat2>();
	CreateType<glm::mat3>();
	CreateType<glm::mat4>();
}

TypeDatabase& TypeDatabase::Get(){
	return gTypeDatabase;
}

void TypeDatabase::PrintAll()
{
	for (TypeMap::const_iterator it = mTypes.begin(); it != mTypes.end(); ++it)
	{
		const TypeDesc& td = it->second;
		std::cout << "\nName: " << td.mName << "\n"
				  << "size: " << td.mSize << "\n"
				  << "Members: \n";

		for( int i = 0; i < td.mMembers.size(); ++i ) {
			const MemberDesc md = td.mMembers[i];
			std::cout << "\tName: " << md.mName << "\n"
					  << "\toffset: " << md.mOffset << "\n"
					  << "\t\tName: " << md.mpTypeDesc->mName << "\n"
					  << "\t\tsize: " << md.mpTypeDesc->mSize << "\n";
		}
	}
}


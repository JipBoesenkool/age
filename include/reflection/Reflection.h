//
// Created by Jip Boesenkool on 20/05/2018.
//

#ifndef AGE_REFLECTION_H
#define AGE_REFLECTION_H

#include "../../src/reflection/TypeDatabase.h"
#include "TypeDesc.h"
#include "Var.h"

#define DefineType(type) \
	template <> struct GetTypeName<type> { static const char* value; }; \
	const char* GetTypeName<type>::value = #type;

#define GetTypeByType( TYPE ) \
	TypeDatabase::Get().GetType<TYPE>()

#define GetTypeByString( STRING ) \
	TypeDatabase::Get().GetType<>( STRING )

#define CreateType(type) \
	TypeDatabase::Get().CreateType<type>(#type)

#define AddMember(TStruct, TMember) \
	.AddMember(#TMember, &TStruct::TMember)

#define AddField(Name, Func) \
	.AddMember( #Name, Func )


#endif //AGE_REFLECTION_H

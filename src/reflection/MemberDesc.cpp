//
// Created by Jip Boesenkool on 11/05/2018.
//
#include "MemberDesc.h"
#include "TypeDatabase.h"

TypeDesc* MemberDesc::GetType( )
{
	if( mpTypeDesc == nullptr )
	{
		mpTypeDesc = TypeDatabase::Get().GetTypePtr( mTypeName );
	}

	return mpTypeDesc;
}

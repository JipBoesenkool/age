//
// Created by Jip Boesenkool on 26/05/2018.
//
#include "reflection/VarBag.h"

Var* VarBag::Get( std::string name )
{
	if( mProperties.find(name) != mProperties.end() )
	{
		return &mProperties[name];
	}

	return nullptr;
};

void VarBag::Set( std::string name, Var& data )
{
	auto pair = std::pair<std::string, Var>( name, data );
	mProperties.insert( pair );
};

size_t VarBag::Size()
{
	return mProperties.size();
}

std::map<std::string, Var>* VarBag::GetMap()
{
	return &mProperties;
};


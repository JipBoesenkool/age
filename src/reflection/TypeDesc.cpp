//
// Created by Jip Boesenkool on 11/05/2018.
//

#include "../../include/reflection/TypeDesc.h"
#include "TypeDatabase.h"

TypeDesc* TypeDesc::GetType( std::string name )
{
	return TypeDatabase::Get().GetTypePtr( name );
}

void* TypeDesc::New( void ) const
{
	return new char[mSize];
}

void TypeDesc::Delete( void *data ) const
{
	delete[] reinterpret_cast<char *>(data);
	data = nullptr;
}

void TypeDesc::Copy( void *dest, const void *src ) const
{
	memcpy( dest, src, mSize );
}

void* TypeDesc::NewCopy( const void *src ) const
{
	void *data = new char[mSize];
	memcpy( data, src, mSize );
	return data;
}


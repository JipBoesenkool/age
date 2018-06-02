//
// Created by Jip Boesenkool on 11/05/2018.
//
#ifndef REFLECTION_VAR_H
#define REFLECTION_VAR_H

#include "TypeDesc.h"
#include "../../src/reflection/TypeDatabase.h"
class Var
{
public:
	Var( )
		: mpType( nullptr ), mpData( nullptr )
	{
		//Default constructor
	}

	Var( const TypeDesc* pType, void* pData )
		: mpType( pType ), mpData( pData )
	{
		//Empty constructor
	}

	template <typename T>
	Var( const T& value )
	{
		mpType = TypeDatabase::Get().GetTypePtr< T >();
		mpData = mpType->NewCopy( &value );
	}

	template <typename T>
	T& GetValue( T& var )
	{
		//Assert
		return *reinterpret_cast<T *>(mpData);
	}

	template <typename T>
	T& GetValue( void )
	{
		return *reinterpret_cast<T *>(mpData);
	}

	template <typename T>
	const T& GetValue( void ) const
	{
		return *reinterpret_cast<T *>(mpData);
	}

	const TypeDesc* GetType( void ) const
	{
		return mpType;
	}

	Var& operator=( const Var& rhs )
	{
		if(this == &rhs)
		{
			return *this;
		}

		if(mpType != nullptr)
		{
			if(mpType->mName == rhs.mpType->mName)
			{
				mpType->Copy( mpData, rhs.mpData );
			}
			else
			{
				assert( rhs.mpType != nullptr ); // Cannot make an instance of NULL meta!

				mpType->Delete( mpData );
				mpType = rhs.GetType( );
				// We require a new copy if meta does not match!
				mpData = mpType->NewCopy( &rhs.mpData );
			}
		}

		return *this;
	}

	template <typename T>
	Var& operator=( const T& rhs )
	{
		// We require a new copy if meta does not match!
		TypeDesc* newType = TypeDatabase::Get().GetTypePtr<T>();
		//TODO: equel operator for TypeDesc
		if(mpType != newType )
		{
			mpType->Delete( mpData );
			mpType = newType;
			mpData = mpType->NewCopy( &rhs );
		}
		else
		{
			mpType->Copy( mpData, &rhs );
		}
		return *this;
	}

private:
	const TypeDesc* mpType;
	void* mpData;
};

#endif //REFLECTION_VAR_H

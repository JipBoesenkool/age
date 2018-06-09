//
// Created by Jip Boesenkool on 26/05/2018.
//

#ifndef AGE_VARBAG_H
#define AGE_VARBAG_H

#include "Var.h"
#include <map>

class VarBag
{
//Members
private:
	std::map<std::string, Var> mProperties;
//Functions
public:
	Var* Get( std::string name );

	template <typename T>
	T& GetValue( std::string name, T& var )
	{
		//Assert
		return *reinterpret_cast<T *>( Get(name) );
	}

	template <typename T>
	T& GetValue( std::string name  )
	{
		return *reinterpret_cast<T *>( Get( name ) );
	}
	void Set( std::string name, Var& data );
	size_t Size();
	//TODO: provide iteration through lambdas
	std::map<std::string, Var>* GetMap();

};

#endif //AGE_VARBAG_H

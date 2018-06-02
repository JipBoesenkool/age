//
// Created by Jip Boesenkool on 11/05/2018.
//

#ifndef REFLECTION_MEMBERDESC_H
#define REFLECTION_MEMBERDESC_H

#include "../../include/reflection/TypeDesc.h"

template<typename T, typename M>
constexpr int OffsetOf(M T::*member)
{
	return (int)((char*)&((T*)nullptr->*member) - (char*)nullptr);
}

//class TypeDesc;
class MemberDesc
{
public:
	const char* 	mName;
	unsigned int 	mOffset;
	const char* 	mTypeName;
	TypeDesc* 		mpTypeDesc = nullptr;

	template<typename Class, typename Member>
	static MemberDesc Create(const char* name, Member Class::*memberPtr)
	{
		MemberDesc md;
		md.mName = name;
		md.mOffset = OffsetOf(memberPtr);
		md.mTypeName = GetTypeName<Member>::value;
		md.mpTypeDesc = md.GetType();
		return md;
	}

	TypeDesc* GetType( );
};

#endif //REFLECTION_MEMBERDESC_H

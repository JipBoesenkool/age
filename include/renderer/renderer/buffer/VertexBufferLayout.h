//
// Created by Jip Boesenkool on 10/06/2018.
//

#ifndef AGE_BUFFERLAYOUT_H
#define AGE_BUFFERLAYOUT_H

#include <vector>
#include <string>
#include <assert.h>

struct VertexBufferElement
{
	VertexBufferElement(std::string typeName, unsigned int count)
	{
		mTypeName 	= typeName;
		mCount 		= count;

		mSize		= 0;
		mType		= 0;
		mNormalized	= false;
	};

	std::string mTypeName;
	unsigned int mCount;
	unsigned int mType;
	unsigned int mSize;
	bool mNormalized;
};

class VertexBufferLayoutImpl
{
public:
	virtual unsigned int CalculateStride( std::vector<VertexBufferElement>* elements )
	{
		assert(false);
		return 0;
	};
};

class VertexBufferLayout
{
//Members
protected:
	std::vector<VertexBufferElement> mElements;
//Functions
public:
	VertexBufferLayout() {
		//Empty constructor
	};
	void Push(std::string typeName, unsigned int count )
	{
		mElements.push_back( VertexBufferElement(typeName, count) );
	};
	//Getters
	inline std::vector<VertexBufferElement>& GetElements() { return mElements; };
};

#endif //AGE_BUFFERLAYOUT_H

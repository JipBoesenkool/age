//
// Created by Jip Boesenkool on 12/08/2018.
//

#ifndef AGE_UNIFORMBUFFER_H
#define AGE_UNIFORMBUFFER_H

#include <string>
#include <renderer/renderer/UniformList.h>
#include <renderer/renderer/Shader.h>

class UniformBuffer
{
public:
	UniformBuffer()
	{
		//Empty contructor
	};
	virtual void Init( const std::string& name, UniformList* pUniforms, Shader* shaderBegin, unsigned int shaderCount ) = 0;
	virtual void Bind() = 0;
};

#endif //AGE_UNIFORMBUFFER_H

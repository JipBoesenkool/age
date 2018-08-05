//
// Created by Jip Boesenkool on 04/08/2018.
//

#ifndef AGE_UNIFORM_H
#define AGE_UNIFORM_H

#include <reflection/Reflection.h>
#include <renderer/renderer/Shader.h>

typedef void (*UniformSetFn)(Shader& shader, const std::string &name, void* value);

struct Uniform
{
	std::string  mName;
	void* 		 mpData;
	UniformSetFn mpSetFn;
};

#endif //AGE_UNIFORM_H

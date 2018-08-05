//
// Created by Jip Boesenkool on 05/08/2018.
//

#ifndef AGE_GLUNIFORM_H
#define AGE_GLUNIFORM_H

#include <glad/glad.h>

#include <renderer/renderer/UniformList.h>

#include "renderer/ogl_renderer/GLShader.h"
#include "renderer/ogl_renderer/GLUtilities.h"

class GLUniform : public UniformImpl
{
public:
	UniformSetFn GetCallback( std::string typeName ) override;
	static void SetUniformBool(Shader& shader, const std::string &name, void* value);
	static void SetUniformInt(Shader& shader, const std::string &name, void* value);
	static void SetUniformFloat(Shader& shader, const std::string &name, void* value);
	static void SetUniformVec2(Shader& shader, const std::string &name, void* value);
	static void SetUniformVec3(Shader& shader, const std::string &name, void* value);
	static void SetUniformVec4(Shader& shader, const std::string &name, void* value);
	static void SetUniformMat2(Shader& shader, const std::string &name, void* value);
	static void SetUniformMat3(Shader& shader, const std::string &name, void* value);
	static void SetUniformMat4(Shader& shader, const std::string &name, void* value);
};

#endif //AGE_GLUNIFORM_H

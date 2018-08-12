//
// Created by Jip Boesenkool on 05/08/2018.
//
#include "renderer/ogl_renderer/GLUniform.h"

UniformImpl* UniformList::spUniformImpl = new GLUniform();

UniformSetFn GLUniform::GetCallback( std::string typeName )
{
	UniformSetFn setFn = nullptr;
	if( typeName.compare("int") == 0 )
	{
		setFn = &GLUniform::SetUniformInt;
	}
	else if( typeName.compare("float") == 0 )
	{
		setFn = &GLUniform::SetUniformFloat;
	}
	else if( typeName.compare("bool") == 0 )
	{
		setFn = &GLUniform::SetUniformBool;
	}
	else if( typeName.compare("glm::vec2") == 0 )
	{
		setFn = &GLUniform::SetUniformVec2;
	}
	else if( typeName.compare("glm::vec3") == 0 )
	{
		setFn = &GLUniform::SetUniformVec3;
	}
	else if( typeName.compare("glm::vec4") == 0 )
	{
		setFn = &GLUniform::SetUniformVec4;
	}
	else if( typeName.compare("glm::mat2") == 0 )
	{
		setFn = &GLUniform::SetUniformMat2;
	}
	else if( typeName.compare("glm::mat3") == 0 )
	{
		setFn = &GLUniform::SetUniformMat3;
	}
	else if( typeName.compare("glm::mat4") == 0 )
	{
		setFn = &GLUniform::SetUniformMat4;
	}
	else
	{
		assert(false);
	}

	return setFn;
};

void GLUniform::SetUniformBool(Shader& shader, const std::string &name, void* value)
{
	GLCall( glUniform1i( shader.GetUniformLocation(name), *(bool*)value ) );
}
void GLUniform::SetUniformInt(Shader& shader, const std::string &name, void* value)
{
	GLCall( glUniform1i( shader.GetUniformLocation(name), *(int*)value ) );
}
void GLUniform::SetUniformFloat(Shader& shader, const std::string &name, void* value)
{
	GLCall( glUniform1f( shader.GetUniformLocation(name), *(float*)value ) );
}
void GLUniform::SetUniformVec2(Shader& shader, const std::string &name, void* value)
{
	GLCall( glUniform2fv( shader.GetUniformLocation(name), 1, (float*)value ) );
}
void GLUniform::SetUniformVec3(Shader& shader, const std::string &name, void* value)
{
	GLCall( glUniform3fv( shader.GetUniformLocation(name), 1, (float*)value ) );
}
void GLUniform::SetUniformVec4(Shader& shader, const std::string &name, void* value)
{
	GLCall( glUniform4fv( shader.GetUniformLocation(name), 1, (float*)value ) );
}
void GLUniform::SetUniformMat2(Shader& shader, const std::string &name, void* value)
{
	GLCall( glUniformMatrix2fv( shader.GetUniformLocation(name), 1, GL_FALSE, (float*)value ) );
}
void GLUniform::SetUniformMat3(Shader& shader, const std::string &name, void* value)
{
	GLCall( glUniformMatrix3fv( shader.GetUniformLocation(name), 1, GL_FALSE, (float*)value ) );
}
void GLUniform::SetUniformMat4(Shader& shader, const std::string &name, void* value)
{
	GLCall( glUniformMatrix4fv( shader.GetUniformLocation(name), 1, GL_FALSE, (float*)value ) );
}
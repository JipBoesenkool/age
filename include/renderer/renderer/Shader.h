//
// Created by Jip Boesenkool on 10/06/2018.
//

#ifndef AGE_SHADER_H
#define AGE_SHADER_H

#include "RenderResource.h"

#include <string>
#include <unordered_map>

typedef unsigned int ShaderHandle;

struct ShaderResource
{
	std::string mName;
	std::string mFilepath;
};

enum class ShaderType
{
	NONE = -1,
	VERTEX = 0,
	FRAGMENT = 1,
	GEOMETRY = 2
};

struct ShaderProgramSource
{
	std::string mVertexSource;
	std::string mFragmentSource;
	std::string mGeometrySource;
};

class Shader : public RenderResource
{
protected:
	std::string mName;
	std::unordered_map<std::string, int> mUniformCache;
public:
	Shader(){
		//Empty contructor
	};
	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	//Uniform functions
	virtual int GetUniformLocation(const std::string& uniformName) = 0;
	virtual void SetUniformBool(const std::string &name, bool value) = 0;
	virtual void SetUniformInt(const std::string &name, int value) = 0;
	virtual void SetUniformFloat(const std::string &name, float value) = 0;
	//virtual void SetUniformVec2(const std::string &name, const glm::vec2 &value) = 0;
	virtual void SetUniformVec2(const std::string &name, float x, float y) = 0;
	//virtual void SetUniformVec3(const std::string &name, const glm::vec3 &value) = 0;
	virtual void SetUniformVec3(const std::string &name, float x, float y, float z) = 0;
	//virtual void SetUniformVec4(const std::string &name, const glm::vec4 &value) = 0;
	virtual void SetUniformVec4(const std::string &name, float x, float y, float z, float w) = 0;
	//virtual void SetUniformMat2(const std::string &name, const glm::mat2 &mat) = 0;
	//virtual void SetUniformMat3(const std::string &name, const glm::mat3 &mat) = 0;
	//virtual void SetUniformMat4(const std::string &name, const glm::mat4 &mat) = 0;
};

#endif //AGE_SHADER_H

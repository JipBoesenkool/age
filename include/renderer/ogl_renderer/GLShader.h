//
// Created by Jip Boesenkool on 10/06/2018.
//

#ifndef AGE_GLSHADER_H
#define AGE_GLSHADER_H

#include "renderer/renderer/Shader.h"

class GLShader : public Shader
{
public:
	GLShader( const std::string& shaderPath );
	GLShader( const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath = "" );
	~GLShader();

	GLShader(GLShader&& other); //Move constructor
	GLShader& operator=(GLShader&& other); //Move assignment

	void Bind() const override;
	void Unbind() const override;

	//Uniform functions
	void SetUniformBool(const std::string &name, bool value) override;
	void SetUniformInt(const std::string &name, int value) override;
	void SetUniformFloat(const std::string &name, const void* value);
	void SetUniformFloat(const std::string &name, float value) override;
	//void SetUniformVec2(const std::string &name, const glm::vec2 &value) override;
	void SetUniformVec2(const std::string &name, float x, float y) override;
	//void SetUniformVec3(const std::string &name, const glm::vec3 &value) override;
	void SetUniformVec3(const std::string &name, float x, float y, float z) override;
	//void SetUniformVec4(const std::string &name, const glm::vec4 &value) override;
	void SetUniformVec4(const std::string &name, float x, float y, float z, float w) override;
	//void SetUniformMat2(const std::string &name, const glm::mat2 &mat) override;
	//void SetUniformMat3(const std::string &name, const glm::mat3 &mat) override;
	//void SetUniformMat4(const std::string &name, const glm::mat4 &mat) override;
private:
	int GetUniformLocation(const std::string& uniformName);
	static unsigned int CreateShader( const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath = nullptr );
	static unsigned int CompileShader( unsigned int type, const std::string& source);
	static std::string LoadShader( const std::string& filePath);
	static ShaderProgramSource ParseShader( const std::string& shaderPath );
};

#endif //AGE_GLSHADER_H

//
// Created by Jip Boesenkool on 10/06/2018.
//
#include <glad/glad.h>

#include "renderer/ogl_renderer/GLShader.h"
#include "renderer/ogl_renderer/GLUtilities.h"

#include <sstream>
#include <fstream>

//Public:
GLShader::GLShader( const std::string& shaderPath )
{
	ShaderProgramSource src = ParseShader(shaderPath);
	mRendererId = CreateShader(src.mVertexSource, src.mFragmentSource, src.mGeometrySource);
}
GLShader::GLShader( const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath )
{
	ShaderProgramSource src{
		LoadShader(vertexPath),
		LoadShader(fragmentPath),
		LoadShader(geometryPath)
	};
	mRendererId = CreateShader(vertexPath, src.mFragmentSource, src.mGeometrySource);
}
GLShader::~GLShader()
{
	std::cout << "destructor called! \n";
	GLCall( glDeleteProgram( mRendererId ) );
}

// Move constructor
GLShader::GLShader(GLShader&& other)
{
	mRendererId = other.mRendererId;
	other.mRendererId = 0;
}
GLShader& GLShader::operator=(GLShader&& other)
{
	// Self-assignment detection
	if (&other == this)
		return *this;

	// Transfer ownership of a.m_ptr to m_ptr
	mRendererId = other.mRendererId;
	other.mRendererId = 0;
	return *this;
}

void GLShader::Bind() const
{
	GLCall( glUseProgram(mRendererId) );
}
void GLShader::Unbind() const
{
	GLCall( glUseProgram(0) );
}

//Uniform functions
void GLShader::SetUniformBool(const std::string &name, bool value)
{
	GLCall( glUniform1i( GetUniformLocation(name), (int)value ) );
}
void GLShader::SetUniformInt(const std::string &name, int value)
{
	GLCall( glUniform1i( GetUniformLocation(name), value ) );
}
void GLShader::SetUniformFloat(const std::string &name, float value)
{
	GLCall( glUniform1f( GetUniformLocation(name), value ) );
}
//void GLShader::SetUniformVec2(const std::string &name, const glm::vec2 &value);
void GLShader::SetUniformVec2(const std::string &name, float x, float y)
{
	GLCall( glUniform2f( GetUniformLocation(name), x, y ) );
}
//void GLShader::SetUniformVec3(const std::string &name, const glm::vec3 &value);
void GLShader::SetUniformVec3(const std::string &name, float x, float y, float z)
{
	GLCall( glUniform3f( GetUniformLocation(name), x, y, z ) );
}
//void GLShader::SetUniformVec4(const std::string &name, const glm::vec4 &value);
void GLShader::SetUniformVec4(const std::string &name, float x, float y, float z, float w)
{
	GLCall( glUniform4f( GetUniformLocation(name), x, y, z, w ) );
}
//void GLShader::SetUniformMat2(const std::string &name, const glm::mat2 &mat);
//void GLShader::SetUniformMat3(const std::string &name, const glm::mat3 &mat);
//void GLShader::SetUniformMat4(const std::string &name, const glm::mat4 &mat);

//Private:
int GLShader::GetUniformLocation( const std::string &uniformName )
{
	//Check cache
	if( mUniformCache.find(uniformName) != mUniformCache.end() )
	{
		return mUniformCache[uniformName];
	}

	GLCall( int location = glGetUniformLocation(mRendererId, uniformName.c_str() ) );
	if( location == -1 )
	{
		std::cout << "Warning: uniform " << uniformName << " doesn't exist \n";
	}
	mUniformCache[uniformName] = location;

	return location;
}

unsigned int GLShader::CreateShader( const std::string &vertexShader, const std::string &fragmentShader, const std::string &geometryShader )
{
	GLCall( unsigned int program = glCreateProgram() );
	unsigned int vs = CompileShader( GL_VERTEX_SHADER, vertexShader );
	unsigned int fs = CompileShader( GL_FRAGMENT_SHADER, fragmentShader );
	unsigned int gs = ( geometryShader.empty() ) ? 0 : CompileShader( GL_GEOMETRY_SHADER, geometryShader );

	GLCall( glAttachShader(program, vs) );
	GLCall( glAttachShader(program, fs) );
	if( !geometryShader.empty() )
	{
		GLCall( glAttachShader(program, gs) );
	}

	GLCall( glLinkProgram(program) );
	GLCall( glValidateProgram(program) );

	GLCall( glDeleteShader(vs) );
	GLCall( glDeleteShader(fs) );
	if( !geometryShader.empty() )
	{
		GLCall( glDeleteShader(gs) );
	}

	return program;
}

unsigned int GLShader::CompileShader( unsigned int type, const std::string& source)
{
	GLCall( unsigned int id = glCreateShader(type) );
	const char* src = source.c_str();
	GLCall( glShaderSource(id, 1, &src, nullptr) );
	GLCall( glCompileShader(id) );

	int result;
	GLCall( glGetShaderiv(id, GL_COMPILE_STATUS, &result) );
	if( result == GL_FALSE )
	{
		int length;
		GLCall( glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length) );
		char* msg = (char*)alloca( length * sizeof(char) );
		GLCall( glGetShaderInfoLog(id, length, &length, msg) );
		std::string typeName;
		switch(type)
		{
			case GL_VERTEX_SHADER: typeName = "vertex"; break;
			case GL_FRAGMENT_SHADER: typeName = "fragment"; break;
			case GL_GEOMETRY_SHADER: typeName = "geometry"; break;
		}
		std::cout << "ERROR::GLShader::CompileShader: Failed to compile "
				  << typeName << "\n";
		std::cout << msg << "\n";
		GLCall( glDeleteShader(id) );
		return 0;
	}

	return id;
}

std::string GLShader::LoadShader( const std::string& filePath )
{
	//TODO: check extensions
	std::ifstream stream;
	stream.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	std::stringstream ss;
	try
	{
		stream.open(filePath);
		ss << stream.rdbuf();
		stream.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n";
	}

	return ss.str();
}

ShaderProgramSource GLShader::ParseShader(const std::string& shaderPath)
{
	if( shaderPath.rfind(".glsl") == std::string::npos )
	{
		//TODO: better error checking
		assert( false );
	}

	std::ifstream stream;
	std::string line;
	std::stringstream ss[3];
	ShaderType type = ShaderType::NONE;
	try
	{
		stream.open(shaderPath);
		if (!stream.is_open()) {
			std::cout << "ERROR::GLShader::ParseShader: Could not open file.\n";
			return {"","",""};
		}

		while( getline(stream, line) )
		{
			if(line.find("#shader") != std::string::npos)
			{
				if( line.find("vertex") != std::string::npos )
				{
					type = ShaderType::VERTEX;
				}
				else if( line.find("fragment") != std::string::npos )
				{
					type = ShaderType::FRAGMENT;
				}
				else if( line.find("geometry") != std::string::npos )
				{
					type = ShaderType::GEOMETRY;
				}
			}
			else if(type != ShaderType::NONE)
			{
				ss[(int)type] << line << '\n';
			}
		}
		stream.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << e.code().message() << "\n";
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n";
	}

	return { ss[0].str(), ss[1].str(), ss[2].str() };
}


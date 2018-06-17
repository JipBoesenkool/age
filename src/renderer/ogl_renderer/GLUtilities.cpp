//
// Created by Jip Boesenkool on 16/06/2018.
//
#include <glad/glad.h>
#include <renderer/ogl_renderer/GLUtilities.h>

#ifdef NDEBUG
	void GLUtils::GLClearError()
	{
		//Infin loop
		while( glGetError() != GL_NO_ERROR );
	}

	bool GLUtils::GLLogCall( const char* function, const char* file, int line )
	{
		while( GLenum error = glGetError() )
		{
			std::cout << "[OpenGL Error] (" << error << "(: " << function
					  <<  " " << file << ":" << line << "\n";
			return false;
		}
		return true;
	}
#endif

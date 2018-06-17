//
// Created by Jip Boesenkool on 10/06/2018.
//

#ifndef AGE_GLUTILITIES_H
#define AGE_GLUTILITIES_H

#include <assert.h>
#include <string>
#include <iostream>

#define NDEBUG true
#ifdef NDEBUG
	class GLUtils
	{
	public:
		static void GLClearError();
		static bool GLLogCall( const char* function, const char* file, int line );
	};

	#define GLCall(x) GLUtils::GLClearError(); \
		x; \
		assert( GLUtils::GLLogCall(#x, __FILE__, __LINE__) )
#else
	#define GLCall( x ) x
#endif

#endif //AGE_GLUTILITIES_H

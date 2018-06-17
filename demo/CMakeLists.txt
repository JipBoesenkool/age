cmake_minimum_required(VERSION 3.7)
project(ageDemo)

set(CMAKE_CXX_STANDARD 14)

#For the shared library:
set ( AGE_LIB libage.dylib )
link_directories( ../build )
set ( OGL_RENDERER_LIB libGLRenderer.dylib )
link_directories( ../build/src/renderer/ogl_renderer )

set(SOURCE_FILES
        main.cpp)

add_executable(ageDemo ${SOURCE_FILES})
target_link_libraries(ageDemo ${AGE_LIB} )
target_link_libraries(ageDemo glad )
target_link_libraries(ageDemo ${OGL_RENDERER_LIB} )

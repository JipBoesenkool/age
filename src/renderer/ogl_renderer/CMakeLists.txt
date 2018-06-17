cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 14)

set(NAME "GLRenderer")
project(NAME)
################################################################################
# Libraries
################################################################################
# Look up OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
#GLAD
set(GLAD_BUILD_SOURCE_DIR "../../../build/lib/glad")
include_directories(${GLAD_BUILD_SOURCE_DIR}/include)

#libraries to link
set(LINKED_LIBRARIES
        ${OPENGL_gl_LIBRARY})
################################################################################
# Project settings
################################################################################
include_directories(../../../include/renderer)

set(RENDERER_SOURCE_FILES
        ${GLAD_BUILD_SOURCE_DIR}/src/glad.c
        ${GLAD_BUILD_SOURCE_DIR}/include/glad/glad.h
        GLUtilities.cpp
        GLRenderer.cpp
        buffer/GLVertexBuffer.cpp
        buffer/GLVertexBufferLayoutImpl.cpp
        buffer/GLIndexBuffer.cpp
        buffer/GLVertexArray.cpp
        GLShader.cpp
        GLMesh.cpp)
add_library(${NAME} SHARED ${RENDERER_SOURCE_FILES})
# Make sure the compiler can find include files (incase of direct linking)
target_include_directories (${NAME} PUBLIC ${GLAD_BUILD_SOURCE_DIR}/include)
target_link_libraries(${NAME} age )
target_link_libraries(${NAME} ${LINKED_LIBRARIES})
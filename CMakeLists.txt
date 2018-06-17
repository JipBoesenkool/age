cmake_minimum_required(VERSION 3.7)
project(age)

set(CMAKE_CXX_STANDARD 14)
# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
include(GNUInstallDirs)
################################################################################
# Libraries
################################################################################
#glfw library
set(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE STRING "" FORCE)
set(GLFW_INSTALL        OFF CACHE STRING "" FORCE)
set(GLFW_SOURCE_DIR "${PROJECT_SOURCE_DIR}/lib/glfw")
include_directories(${GLFW_SOURCE_DIR}/include)
add_subdirectory(${GLFW_SOURCE_DIR})

#GLAD
set(GLAD_LIB_SOURCE_DIR "${PROJECT_SOURCE_DIR}/lib/glad")
include_directories(${GLAD_INCLUDE_DIR})
add_subdirectory(${GLAD_LIB_SOURCE_DIR})

#libraries to link
set(LINKED_LIBRARIES
        glfw
        glad)

################################################################################
# Project settings
################################################################################
include_directories(include)

set(SOURCE_FILES
        src/age.cpp)
add_library(age SHARED ${SOURCE_FILES})
target_link_libraries(age ${LINKED_LIBRARIES})

add_subdirectory( src )

install(TARGETS age DESTINATION /usr/lib)
# 'make install' to the correct locations (provided by GNUInstallDirs).
#install(TARGETS lib EXPORT MyLibraryConfig
#        ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
#install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}

#engine playground
add_subdirectory( demo )


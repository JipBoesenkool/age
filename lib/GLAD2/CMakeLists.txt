cmake_minimum_required(VERSION 3.7)
add_definitions(-DBUILD_SHARED_LIBS=ON)
################################################################################
# Project settings
################################################################################
include_directories(include)

set(SOURCE_FILES
        src/glad.c)
add_library(glad SHARED ${SOURCE_FILES})
install(TARGETS glad DESTINATION /usr/lib)


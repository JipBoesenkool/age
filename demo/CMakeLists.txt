cmake_minimum_required(VERSION 3.7)
project(ageDemo)

set(CMAKE_CXX_STANDARD 14)

#For the shared library:
set ( AGE_LIB libage.dylib )
link_directories( ../cmake-build-debug )
include_directories( ../include)

set(SOURCE_FILES
        main.cpp)

add_executable(ageDemo ${SOURCE_FILES})
target_link_libraries(ageDemo ${AGE_LIB} )
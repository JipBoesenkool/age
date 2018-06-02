cmake_minimum_required(VERSION 3.7)
project(age)

set(CMAKE_CXX_STANDARD 14)

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
include(GNUInstallDirs)

include_directories(include)

set(SOURCE_FILES
        src/age.cpp)
add_library(age SHARED ${SOURCE_FILES})

add_subdirectory( src )

install(TARGETS age DESTINATION /usr/lib)
# 'make install' to the correct locations (provided by GNUInstallDirs).
#install(TARGETS lib EXPORT MyLibraryConfig
#        ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
#install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
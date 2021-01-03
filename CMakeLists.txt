cmake_minimum_required(VERSION 3.16)

# set up main pj
project(myPlayGround)

# helper cmake
include(CMakeDependentOption)
include(cmake/helper.cmake)
#
# common setting
#
set(EXECUTABLE_OUTPUT_PATH         ${CMAKE_HOME_DIRECTORY}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)
set(CMAKE_PDB_OUTPUT_DIRECTORY     ${CMAKE_HOME_DIRECTORY}/build)
set(CMAKE_INSTALL_PREFIX           ${CMAKE_HOME_DIRECTORY}/build/install CACHE PATH ".."  FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)
set(CMAKE_CXX_STANDARD             20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_HOME_DIRECTORY}/lib/install")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(NOT cmake_Debug_postfix)
  set(cmake_Debug_postfix d)
endif()

# include(cmake/External_GTest.cmake)
include(cmake/External_Catch2.cmake)



# compile definitions
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_C_FLAGS_RELEASE   "/MD /O2 /Ob2 /DNDEBUG /Oi /Ot /Oy /GT /GL")
set(CMAKE_CXX_FLAGS_RELEASE "/MD /O2 /Ob2 /DNDEBUG /Oi /Ot /Oy /GT /GL")

# add_subdirectory(leetcode)
# add_subdirectory(test-constexpr-everything)
# add_subdirectory(leetcode-vscode)
add_subdirectory(leetcode-with-test)

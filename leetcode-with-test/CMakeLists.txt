cmake_minimum_required(VERSION 3.15)

STRING(REGEX REPLACE ".*/(.*)" "\\1" folder_name ${CMAKE_CURRENT_SOURCE_DIR})

#
# collect dirnames
#
set(curpath ${CMAKE_CURRENT_LIST_DIR})
set(subdirs "")
file(GLOB dirnames RELATIVE ${curpath} ${curpath}/*)
foreach(dirname ${dirnames})
    if(IS_DIRECTORY ${curpath}/${dirname})
      list(APPEND subdirs ${dirname})
    endif()
endforeach()

#
# add target
#
foreach(subdir ${subdirs})
  FILE(GLOB_RECURSE SOURCES ${subdir}/*.h* ${subdir}/*.c*
                            ${subdir}/*.ui ${subdir}/*.qrc
                            ${subdir}/*.qml)
  if(SOURCES)
    # set up project
    project(${subdir})

    # add source to project
    add_executable(${PROJECT_NAME} ${SOURCES})

    # set target properties
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${folder_name})
    set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)



    # set target compie defintions
    target_compile_definitions(${PROJECT_NAME} PRIVATE -D_CRT_SECURE_NO_WARNINGS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -D_WIN32_WINNT=0x0a00)

    #set target include directories
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_INSTALL_PREFIX}/catch2/src/catch2/single_include)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DCATCH_CONFIG_RUNNER)

    # set target precompile headers
    target_precompile_headers(${PROJECT_NAME}
        PRIVATE
        <vector>
        <string>
        <functional>
        <memory>
        <algorithm>
        <unordered_map>
        <utility>
        <thread>
        <list>
        <iostream>
        <array>
    )

  endif()
endforeach()

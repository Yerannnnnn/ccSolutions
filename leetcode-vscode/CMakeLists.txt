cmake_minimum_required(VERSION 3.15)


STRING(REGEX REPLACE ".*/(.*)" "\\1" folder_name ${CMAKE_CURRENT_SOURCE_DIR})
# 单文件生成可执行文件

set(curpath ${CMAKE_CURRENT_LIST_DIR})
set(output "")
file(GLOB all_source_file RELATIVE ${curpath} ${curpath}/*.cc ${curpath}/*.c ${curpath}/*.cpp)

foreach(source_names ${all_source_file})


    # get base name
    STRING(REGEX REPLACE "(.+)\\..*" "\\1" base_name ${source_names})
    # get head file
    file(GLOB source_head ${base_name}.h )
    # fix base name
    STRING(REGEX REPLACE "(.*)\\.(.*)" "\\1" pj_name ${base_name})

    project("${pj_name}")

    # add source to project
    add_executable(${PROJECT_NAME} "${source_names} ${source_head}")

    # set target properties
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${folder_name})
    set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)

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

    # set target compile definitions
    target_compile_definitions(${PROJECT_NAME} PRIVATE -D_CRT_SECURE_NO_WARNINGS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -D_WIN32_WINNT=0x0a00)

    #set target include directories
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_INSTALL_PREFIX}/catch2/src/catch2/single_include)
    # target_compile_definitions(${PROJECT_NAME} PRIVATE -DCATCH_CONFIG_RUNNER)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DCATCH_CONFIG_MAIN)


endforeach()


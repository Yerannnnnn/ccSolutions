cmake_minimum_required(VERSION 3.15)


STRING(REGEX REPLACE ".*/(.*)" "\\1" folder_name ${CMAKE_CURRENT_SOURCE_DIR})
# 单文件生成可执行文件

set(curpath ${CMAKE_CURRENT_LIST_DIR})
set(output "")
file(GLOB all_source_file RELATIVE ${curpath} ${curpath}/*.cc ${curpath}/*.c)

foreach(source_names ${all_source_file})
    # get head file
    file(GLOB source_head ${source}.h )

    # set up project
    STRING(REGEX REPLACE "(.+)\\..*" "\\1" source ${source_names})
    project(${source})

    # add source to project
    add_executable(${PROJECT_NAME} ${source} ${source_head})

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




endforeach()


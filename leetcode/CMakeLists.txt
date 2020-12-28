cmake_minimum_required(VERSION 3.15)

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
    message(STATUS "addpj " ${subdir})
    project(${subdir})

    add_executable(${PROJECT_NAME} ${SOURCES})
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "problems/leetcode")
    set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)
    if (WIN32)
      target_compile_definitions(${subdir} PRIVATE -D_CRT_SECURE_NO_WARNINGS)
      target_compile_definitions(${subdir} PRIVATE -D_WIN32_WINNT=0x0a00)
    endif()
  endif()
endforeach()

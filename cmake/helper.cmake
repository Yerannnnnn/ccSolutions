cmake_minimum_required(VERSION 3.16)

MACRO(group_by_folder sources basedir)
  SET(SOURCE_GROUP_DELIMITER "/")
  SET(last_dir "")
  SET(files "")
  FOREACH(file ${${sources}})
    file(RELATIVE_PATH relative_file "${basedir}" ${file})
    GET_FILENAME_COMPONENT(dir "${relative_file}" PATH)
    IF (NOT "${dir}" STREQUAL "${last_dir}")
      IF (files)
        SOURCE_GROUP("${last_dir}" FILES ${files})
      ENDIF (files)
      SET(files "")
    ENDIF (NOT "${dir}" STREQUAL "${last_dir}")
    SET(files ${files} ${file})
    SET(last_dir "${dir}")
  ENDFOREACH(file)
  IF (files)
    SOURCE_GROUP("${last_dir}" FILES ${files})
  ENDIF (files)
ENDMACRO(group_by_folder)


MACRO(copy_debug_dll pjname from to patten)
    FILE(GLOB copy_file_list RELATIVE ${from} ${from}/${patten})
    FOREACH(copy_file_name ${copy_file_list})
    MESSAGE(STATUS "post_build : will copy debug resources : ${copy_file_name} from ${from}")
        add_custom_command(TARGET ${pjname} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "copy ${copy_file_name} to ${to}/${copy_file_name} ..."
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${from}/${copy_file_name} "${to}/${copy_file_name}"
        )
    ENDFOREACH()
ENDMACRO()




MACRO(get_source_name source_file_name full_name)
  STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" source_file_name ${full_name})
ENDMACRO()

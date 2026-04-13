cmake_minimum_required(VERSION 3.17)
project(task_5 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SUBDIRS LIST_DIRECTORIES true [0-9]*)

foreach(subdir ${SUBDIRS})
    if(IS_DIRECTORY ${subdir})
        get_filename_component(dir_name ${subdir} NAME)
        add_subdirectory(${dir_name})
    endif()
endforeach()
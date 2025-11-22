file(GLOB SUBDIRS LIST_DIRECTORIES true *)

foreach(subdir ${SUBDIRS})
    if(IS_DIRECTORY ${subdir})
        get_filename_component(dir_name ${subdir} NAME)
        add_subdirectory(${dir_name})
    endif()
endforeach()

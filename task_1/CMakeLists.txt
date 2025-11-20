file(GLOB TASK_SOURCES *.cc)

foreach(src_file ${TASK_SOURCES})
    get_filename_component(target_name ${src_file} NAME_WE)
    add_executable(${target_name} ${src_file})
    target_compile_options(${target_name} PRIVATE -Wall -Wextra)
endforeach()

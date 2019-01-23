set(executable_name app)

set(include_dirs ${CMAKE_CURRENT_SOURCE_DIR})

set(source_files)
set(include_files)

foreach(dir ${include_dirs})
    file(GLOB source ${dir}/*.cpp)
    file(GLOB include ${dir}/*.h)
    list(APPEND source_files ${source})
    list(APPEND include_files ${include})
endforeach()

add_executable(${executable_name} ${source_files} ${include_files})
target_link_libraries(${executable_name} appcore)

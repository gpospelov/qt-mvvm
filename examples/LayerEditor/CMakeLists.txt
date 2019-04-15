set(executable_name layer_editor)

# --- source and include files ---
set(include_dirs ${CMAKE_CURRENT_SOURCE_DIR})

set(source_files)
set(include_files)

foreach(dir ${include_dirs})
    file(GLOB source ${dir}/*.cpp)
    file(GLOB include ${dir}/*.h)
    list(APPEND source_files ${source})
    list(APPEND include_files ${include})
endforeach()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_executable(${executable_name} ${source_files} ${include_files})
target_link_libraries(${executable_name} mvvm toyitems Qt5::Core Qt5::Gui Qt5::Widgets)

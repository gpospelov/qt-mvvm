set(library_name dragandmovecore)

set(include_dir ${CMAKE_CURRENT_LIST_DIR})

file(GLOB source_files ${include_dir}/*.cpp)
file(GLOB include_files ${include_dir}/*.h)

add_library(${library_name} STATIC ${source_files} ${include_files})

target_include_directories(${library_name} PUBLIC ${include_dir})
target_link_libraries(${library_name} PUBLIC mvvm Qt5::Core Qt5::Gui Qt5::Widgets)

